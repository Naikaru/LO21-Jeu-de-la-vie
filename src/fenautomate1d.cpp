#include "headers/fenautomate1d.h"

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


void fenAutomate1D::initialize()
{
    std::srand(std::time(NULL));
    for(unsigned int i(0); i<dimension; ++i)
    {
        if(probability >= std::rand()%100)
            depart->item(0,i)->setBackgroundColor("green");
        else
            depart->item(0,i)->setBackgroundColor("white");
    }
/*
    Etat* e = monSimu->getInitialState();
    const Automate* monAuto = &monSimu->getAutomate();
    for(unsigned int i(0); i < maGrid->rowCount(); ++i)
        for(unsigned int j(0); j < maGrid->columnCount(); ++j)
                //maGrid->item(i,j)->setBackgroundColor(monAuto->colorize(1));
    monSimu->reset();
    refreshGrid();
*/
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
