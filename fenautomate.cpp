#include "fenautomate.h"

fenAutomate::fenAutomate(Simulateur* s)
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

    setMinimumSize(500,500);
    myCentralWidget = new QWidget;
    BTavancer = new QPushButton("Avancer", myCentralWidget);
    BTreculer = new QPushButton("Reculer",myCentralWidget);
    BTplay = new QPushButton("Play",myCentralWidget);
    myTimer = new QTimer();
    mySlider = new QSlider(Qt::Horizontal);
    mySlider->setMinimum(1);mySlider->setMaximum(10000);
    myTimer->setInterval(mySlider->value());

    connect(myTimer,SIGNAL(timeout()),this,SLOT(slotAvancer()));
    connect(BTplay, SIGNAL(clicked()),this,SLOT(slotBtPlayStop()));
    connect(mySlider,SIGNAL(sliderMoved(int)),this,SLOT(slotTimerIntervalChange(int)));
    connect(BTavancer,SIGNAL(clicked()),this,SLOT(slotAvancer()));
    connect(BTreculer,SIGNAL(clicked()),this,SLOT(slotReculer()));

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
    if(BTplay->text() == "Play"){
        BTplay->setText("Stop");
        myTimer->start();
    }else{
        BTplay->setText("Play");
        myTimer->stop();
    }
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





fenAutomate2D::fenAutomate2D(QString nom, Simulateur* s):fenAutomate(nom,s){
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
    resizeGrid();
    connect(maGrid,SIGNAL(itemDoubleClicked(QTableWidgetItem*)),this,SLOT(slotGridClick(int,int)));
    monSimu->reset();
}


void fenAutomate2D::resizeGrid(){
    int size;
    unsigned int cols = monSimu->dernier().getNbCols();
    unsigned int rows = monSimu->dernier().getNbRows();
    if(maGrid->size().width()/rows < maGrid->size().height()/cols)
        size = (int) this->size().height()/cols-10;
    else
        size = (int) this->size().width()/rows -10;

    for(unsigned int i(0);i<rows;i++){
       maGrid->setRowHeight(i,size);
    }
    for(unsigned int j(0);j<cols;j++){
      maGrid->setColumnWidth(j,size);
    }
}

void fenAutomate2D::cellChange(int i, int j){
    if(monSimu->isAlive(i,j)){
        monSimu->setDead(i,j);
        maGrid->itemAt(i,j)->setBackgroundColor("White");
    }else{
        monSimu->setAlive(i,j);
        maGrid->itemAt(i,j)->setBackgroundColor("Black");
    }
}


void fenAutomate2D::adaptGridSize(){
    unsigned int cols = monSimu->dernier().getNbCols();
    unsigned int rows = monSimu->dernier().getNbRows();
    if ((maGrid->columnCount() != cols) || (maGrid->rowCount() != rows)){
        if(maGrid->columnCount() < cols){
            for(unsigned int i(maGrid->columnCount());i<cols;i++){
                for(unsigned int j(0);j<maGrid->rowCount();j++){
                  maGrid->setItem(j,i,new QTableWidgetItem(""));
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
    unsigned int cols = monSimu->dernier().getNbCols();
    unsigned int rows = monSimu->dernier().getNbRows();
    adaptGridSize();
    for(unsigned int i(0);i<rows;i++){
        for(unsigned int j(0);j<cols;j++){
            if(monSimu->isAlive(i,j)){
                maGrid->itemAt(i,j)->setBackgroundColor("Black");
            }else{
                maGrid->itemAt(i,j)->setBackgroundColor("White");
            }
        }
    }
}

void fenAutomate2D::avancer(){
    monSimu->next();
    refreshGrid();
}


void fenAutomate2D::reculer(){
    //monSimu->next();
    refreshGrid();
}


void fenAutomate2D::slotSizeChange(){
    resizeGrid();
}


void fenAutomate2D::slotGridClick(int i, int j){
    maGrid->itemAt(i,j)->setBackgroundColor("Black");
    //cellChange(i,j);
}



