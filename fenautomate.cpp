#include "fenautomate.h"

fenAutomate::fenAutomate(Simulateur* s):monSimu(s)
{
    setWindowTitle("Automate anonyme");
    UImaker();
}


fenAutomate::fenAutomate(QString nom, Simulateur* s)
{
    monSimu = s;
    setWindowTitle(nom);
    UImaker();
}


void fenAutomate::UImaker(){

    setWindowIcon(QIcon(":/virus.png"));
    playPause = true;
    setMinimumSize(500,500);
    myCentralWidget = new QWidget;

    BTavancer = new QPushButton("Avancer", myCentralWidget);
    BTreculer = new QPushButton("Reculer",myCentralWidget);
    BTplay = new QPushButton(QIcon(":/play-button.png"),"", myCentralWidget);
    BTplay->setSizePolicy(QSizePolicy::Maximum,QSizePolicy::Maximum);
    BTplay->setFlat(true);
    BTinit = new QPushButton("Initialiser", myCentralWidget);

    myTimer = new QTimer(this);
    mySlider = new QSlider(Qt::Horizontal);
    mySlider->setMinimum(1);mySlider->setMaximum(10000);
    mySlider->setValue(1000);
    myTimer->setInterval(mySlider->value());

    connect(myTimer,SIGNAL(timeout()),this,SLOT(slotAvancer()));
    connect(BTplay, SIGNAL(clicked()),this,SLOT(slotBtPlayStop()));
    connect(mySlider,SIGNAL(sliderMoved(int)),this,SLOT(slotTimerIntervalChange(int)));
    connect(BTavancer,SIGNAL(clicked()),this,SLOT(slotAvancer()));
    connect(BTreculer,SIGNAL(clicked()),this,SLOT(slotReculer()));
    //connect(BTinit, SIGNAL(clicked()), this, SLOT(initialize()));

    QHBoxLayout* BTLayout = new QHBoxLayout;
    BTLayout->addWidget(BTreculer);
    BTLayout->addWidget(BTplay);
    BTLayout->addWidget(BTavancer);

    monLayout = new QGridLayout;
    monLayout->addLayout(BTLayout,90,0,5,100);
    monLayout->addWidget(mySlider,95,0,5,100);
    setCentralWidget(myCentralWidget);
    myCentralWidget->setLayout(monLayout);
}


void fenAutomate::slotBtPlayStop(){
    if(playPause){
        BTplay->setIcon(QIcon(":/pause.png"));
        myTimer->start(mySlider->value());
        playPause = false;
    }else{
        myTimer->stop();
        BTplay->setIcon(QIcon(":/play-button.png"));
        playPause = true;
    }
    BTplay->repaint();
}


void fenAutomate::slotTimerIntervalChange(int i){
    if(myTimer==nullptr) return;
    myTimer->setInterval(i);
}


void fenAutomate::slotAvancer(){
    avancer();
}


void fenAutomate::slotReculer(){
    reculer();
}


void fenAutomate::slotBtInit(){
/*
    std::srand(std::time(NULL));
    const Automate* monAuto = &monSimu->getAutomate();
    for(unsigned int i(0); i < maGrid->rowCount(); ++i)
        for(unsigned int j(0); j < maGrid->columnCount(); ++j)
            if(probability >= std::rand()%100)
                maGrid->item(i,j)->setBackgroundColor(monAuto->colorize(1));
*/
}





/****************************************         FENETRE AUTOMATE 1D         ********************************************************/



fenAutomate1D::fenAutomate1D(QString nom, Simulateur *s):
    fenAutomate(nom, s)
{
    numl = new QLabel("Numéro");
    numl->setAlignment(Qt::AlignCenter);

    num = new QSpinBox();
    num->setRange(0,255);
    num->setAlignment(Qt::AlignCenter);

    numeroc = new QHBoxLayout();

    numc = new QVBoxLayout();
    numc->addWidget(numl);
    numc->addWidget(num);

    numeroc->addLayout(numc);

    zeroOneValidator = new QIntValidator();
    zeroOneValidator->setRange(0,1);

    for (unsigned int i(0); i<8; ++i){
        std::string tmpNumBit = NumToNumBit(7-i);

        bitc[i] = new QVBoxLayout();
        numeroBitl[i] = new QLabel(tmpNumBit.substr(5).c_str(),this);

        numeroBit[i] = new QLineEdit();
        numeroBit[i]->setText("0");
        numeroBit[i]->setAlignment(Qt::AlignCenter);
        numeroBit[i]->setFixedWidth(25);
        numeroBit[i]->setValidator(zeroOneValidator);

        bitc[i]->addWidget(numeroBitl[i]);
        bitc[i]->addWidget(numeroBit[i]);

        numeroc->addLayout(bitc[i]);
    }

    connect(num, SIGNAL(valueChanged(int)), this, SLOT(synchronizeNumToNumBit(int)));
    for(unsigned int i(0); i<8; ++i)
    {
        connect(numeroBit[i], SIGNAL(textChanged(QString)), this, SLOT(synchronizeNumBitToNum(QString)));
    }

    monLayout->addLayout(numeroc,0,0,10,100);

    /********************************/

    unsigned int taille = 20;

    depart = new QTableWidget(1, dimension, this);
    depart->setFixedSize(dimension*taille, taille);

    for (unsigned int i(0); i<dimension; ++i)
    {
        depart->setColumnWidth(i, taille);
        depart->setItem(0,i,new QTableWidgetItem(""));
        depart->item(0,i)->setBackgroundColor("white");
        depart->item(0,i)->setFlags(Qt::ItemIsEnabled);
    }

    depart->verticalHeader()->setVisible(false);
    depart->horizontalHeader()->setVisible(false);
    depart->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    depart->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    monLayout->addWidget(depart,10,0,5,100);

    connect(depart, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(cellActivation(QModelIndex)));

    /******************************/
    //setLayout(interface)

    simulation = new QPushButton("Simulation");
    connect(simulation, SIGNAL(clicked()), this, SLOT(simulate()));

    monLayout->addWidget(simulation, 15, 0, 5, 100);

    states = new QTableWidget(dimension, dimension, this);
    states->setFixedSize(dimension*taille, dimension*taille);

    for(unsigned int i(0); i<dimension; ++i)
    {
        states->setRowHeight(i, taille);
        for(unsigned int j(0); j<dimension; ++j)
        {
            if(i==0)
                states->setColumnWidth(j, taille);

            states->setItem(i,j,new QTableWidgetItem(""));
            states->item(i,j)->setBackgroundColor("white");
            states->item(i,j)->setFlags(Qt::ItemIsEnabled);
        }
    }

    states->verticalHeader()->setVisible(false);
    states->horizontalHeader()->setVisible(false);
    states->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    states->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    //interface->addWidget(states);
    monLayout->addWidget(states, 20, 0, 70, 100);
}


void fenAutomate1D::synchronizeNumToNumBit(int n)
{
    std::string tmpNumBit = NumToNumBit(n);
    for(unsigned int i(0); i<tmpNumBit.size(); ++i)
    {
        numeroBit[i]->setText(QString(tmpNumBit[i]));
    }
}


void fenAutomate1D::synchronizeNumBitToNum(const QString& n)
{
    if(n=="") return;

    QString str = "";
    for(unsigned int i(0); i<8; ++i)
    {
        str = str + numeroBit[i]->text();
    }

    short unsigned int tmpNum = NumBitToNum(str.toStdString());
    num->setValue(tmpNum);
}


void fenAutomate1D::cellActivation(QModelIndex indx)
{
    unsigned int i = indx.column();
    if(depart->item(0,i)->backgroundColor() == "white")
        depart->item(0,i)->setBackgroundColor("green");
    else
        depart->item(0,i)->setBackgroundColor("white");
}


void fenAutomate1D::simulate(){
    unsigned int rule = num->value();
    Automate* a = new Automate1D(rule);

    Etat* e = new Etat(1,dimension);
    for(unsigned int i(0); i<dimension; ++i)
    {
        if(depart->item(0,i)->backgroundColor() == "white")
            e->setCellule(0, i, 0);
        else
            e->setCellule(0, i, 1);
    }
    delete monSimu;
    monSimu = new Simulateur(a, e);
    //monSimu->reset();

    for(unsigned int i(0); i<dimension; ++i)
    {
        monSimu->next();
        const Etat& tmpEtat = monSimu->dernier();
        for(unsigned int j(0); j<dimension; ++j)
        {
            if(tmpEtat.getCellule(0,j) == 1)
                states->item(i,j)->setBackgroundColor("green");
            else
                states->item(i,j)->setBackgroundColor("white");
        }
    }
}






/************************************************** FENETRE AUTOMATE 2D *******************************************************/



fenAutomate2D::fenAutomate2D(QString nom, Simulateur* s):fenAutomate(nom,s), probability(60) {
    maGrid = new QTableWidget(s->getInitialState()->getNbRows(),s->getInitialState()->getNbCols());
    monLayout->addWidget(maGrid,0,0,90,100);
    maGrid->horizontalHeader()->hide();
    maGrid->verticalHeader()->hide();

    unsigned int cols = monSimu->dernier().getNbCols();
    unsigned int rows = monSimu->dernier().getNbRows();

    for(unsigned int i(0);i<rows;i++){
        for(unsigned int j(0);j<cols;j++){
          maGrid->setItem(i,j,new QTableWidgetItem(""));
        }
    }
    initialize();
    resizeGrid();
    connect(maGrid,SIGNAL(clicked(QModelIndex)),this,SLOT(slotGridClick(QModelIndex)));
    //monSimu->reset();
}


void fenAutomate2D::resizeGrid(){
    int size;
    unsigned int cols = monSimu->dernier().getNbCols();
    unsigned int rows = monSimu->dernier().getNbRows();
    adaptGridSize();
    if(maGrid->size().width()/rows < maGrid->size().height()/cols)
        size = (int) maGrid->size().height()/cols;
    else
        size = (int) maGrid->size().width()/rows;
    size = (size<1)? 1:size;
    for(unsigned int i(0);i<rows;i++){
       maGrid->setRowHeight(i,size);
    }
    for(unsigned int j(0);j<cols;j++){
      maGrid->setColumnWidth(j,size);
    }
}

void fenAutomate2D::cellChange(int i, int j){
    monSimu->setEtatDepart(monSimu->dernier());
    /*
    if(monSimu->isAlive(i,j))
        monSimu->setDead(i,j);
    else
        monSimu->setAlive(i,j);
    */
    monSimu->changeStatus(i,j);

    // On prends l'item de la grille cliqué, on récupère la valeur correspondante dans l'etat initial, et on affiche
    // la couleur correspondante via la fonction dédiée dans l'automate
    maGrid->item(i,j)->setBackgroundColor(monSimu->getAutomate().colorize(monSimu->getInitialState()->getCellule(i,j)));
    monSimu->reset();
}


void fenAutomate2D::adaptGridSize(){
    unsigned int cols = monSimu->dernier().getNbCols();
    unsigned int rows = monSimu->dernier().getNbRows();
    if ((maGrid->columnCount() != cols) || (maGrid->rowCount() != rows)){
        if(maGrid->columnCount() < cols){
            for(unsigned int i(maGrid->columnCount());i<cols;i++){
                for(unsigned int j(0);j<maGrid->rowCount();j++){
                  maGrid->setItem(j,i,new QTableWidgetItem(""));
                  maGrid->item(j,i)->setFlags(Qt::ItemIsEnabled);
                }
            }
        }else{
            for(unsigned int i(maGrid->columnCount()-1);i<cols;i--){
                maGrid->removeColumn(i);
            }
        }
        if(maGrid->rowCount() < rows){
            for(unsigned int i(maGrid->rowCount());i<rows;i++){
                for(unsigned int j(0);j<maGrid->columnCount();j++){
                  maGrid->setItem(i,j,new QTableWidgetItem(""));
                  maGrid->item(i,j)->setFlags(Qt::ItemIsEnabled);
                }
            }
        }else{
            for(unsigned int i(maGrid->rowCount()-1);i<rows;i--){
                maGrid->removeRow(i);
            }
        }
    }
}
void fenAutomate2D::refreshGrid(){
    const Etat& dernier = monSimu->dernier();
    int cols = (int) dernier.getNbCols();
    int rows = (int) dernier.getNbRows();
    const Automate* monauto = &monSimu->getAutomate();
    adaptGridSize();
    for(int i(0);i<rows;i++){
        for(int j(0);j<cols;j++){
            maGrid->item(i,j)->setBackgroundColor(monauto->colorize(dernier.getCellule(i,j)));
        }
    }
}

void fenAutomate2D::avancer(){
    monSimu->next();
    refreshGrid();
    maGrid->repaint();
}


void fenAutomate2D::reculer(){
    //monSimu->next();
    refreshGrid();
    maGrid->repaint();
}


void fenAutomate2D::slotSizeChange(){
    resizeGrid();
}


void fenAutomate2D::slotGridClick(QModelIndex j){
    cellChange(j.row(),j.column());

}

void fenAutomate2D::initialize(){
    std::srand(std::time(NULL));
    const Automate* monAuto = &monSimu->getAutomate();
    for(unsigned int i(0); i < maGrid->rowCount(); ++i)
        for(unsigned int j(0); j < maGrid->columnCount(); ++j)
            if(probability >= std::rand()%100)
                maGrid->item(i,j)->setBackgroundColor(monAuto->colorize(1));
}
