#include "autocell1D.h"

AutoCell1D::AutoCell1D(QWidget *parent) : QWidget(parent)
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

    //QVBoxLayout *interface = new QVBoxLayout(this);
    interface = new QVBoxLayout(this);
    interface->addLayout(numeroc);

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

    interface->addWidget(depart);

    connect(depart, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(cellActivation(QModelIndex)));

    /******************************/
    //setLayout(interface)

    simulation = new QPushButton("Simulation");
    connect(simulation, SIGNAL(clicked()), this, SLOT(simulate()));

    nbSim = new QSpinBox();
    nbSim->setRange(0,20);
    nbSim->setValue(20);
    nbSim->setAlignment(Qt::AlignCenter);

    connect(nbSim, SIGNAL(valueChanged(int)), this, SLOT(numberGeneration(int)));

    simLaye = new QHBoxLayout();

    simLaye->addWidget(simulation);
    simLaye->addWidget(nbSim);

    interface->addLayout(simLaye);

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

    interface->addWidget(states);
    this->setLayout(interface);
}



void AutoCell1D::synchronizeNumToNumBit(int n)
{
    std::string tmpNumBit = NumToNumBit(n);
    for(unsigned int i(0); i<tmpNumBit.size(); ++i)
    {
        numeroBit[i]->setText(QString(tmpNumBit[i]));
    }
}


void AutoCell1D::synchronizeNumBitToNum(const QString& n)
{
    if(n=="") return;

    std::string str = "";
    for(unsigned int i(0); i<8; ++i)
    {
        str+=numeroBit[i]->text().toLatin1();
    }

    short unsigned int tmpNum = NumBitToNum(str);
    num->setValue(tmpNum);
}


void AutoCell1D::numberGeneration(int value)
{
    nbSim->setValue(value);
}


void AutoCell1D::cellActivation(QModelIndex indx)
{
    unsigned int i = indx.column();
    if(depart->item(0,i)->backgroundColor() == "white")
        depart->item(0,i)->setBackgroundColor("green");
    else
        depart->item(0,i)->setBackgroundColor("white");
}


void AutoCell1D::simulate(){
    unsigned int rule = num->value();
    //const Automate& a = AutomateManager::getAutomateManager().getAutomate(rule);
    Automate1D a(rule);

    Etat1D e(dimension);
    for(unsigned int i(0); i<dimension; ++i)
    {
        if(depart->item(0,i)->backgroundColor() == "white")
            e.setCellule(i, 0);
        else
            e.setCellule(i, 1);
    }

    Simulateur1D s(a, e);
    for(unsigned int i(0); i<dimension; ++i)
    {
        s.next();
        const Etat1D& tmpEtat = s.dernier();
        for(unsigned int j(0); j<dimension; ++j)
        {
            if(tmpEtat.getCellule(j) == 1)
                states->item(i,j)->setBackgroundColor("green");
            else
                states->item(i,j)->setBackgroundColor("white");
        }
    }
}


MainWindow::MainWindow()
{
    /*
    menuFichier =new QMenu(menuBar()->addMenu("&Fichier"));
    menuEdition = new QMenu(menuBar()->addMenu("&Edition"));
    menuAffichage = new QMenu(menuBar()->addMenu("&Affichage"));

    actionQuitter = new QAction("&Quitter", this);
    menuFichier->addAction(actionQuitter);

    fichiersRecents = new QMenu(menuFichier->addMenu("Fichiers &récents"));
    fichiersRecents->addAction("Fichier bidon 1.txt");
    fichiersRecents->addAction("Fichier bidon 2.txt");
    fichiersRecents->addAction("Fichier bidon 3.txt");

    */
    AutoCell1D *appli = new AutoCell1D(this);
    setCentralWidget(appli);
}
