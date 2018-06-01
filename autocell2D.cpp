#include "autocell2D.h"

AutoCell2D::AutoCell2D(QWidget *parent) : QWidget(parent)
{
    labelMinNeighbours = new QLabel("Nombre de voisins minimum");
    labelMinNeighbours->setAlignment(Qt::AlignCenter);
    numMinNeighbours = new QSpinBox();
    numMinNeighbours->setRange(0,9);
    numMinNeighbours->setAlignment(Qt::AlignCenter);

    labelMaxNeighbours = new QLabel("Nombre de voisins maximum");
    labelMaxNeighbours->setAlignment(Qt::AlignCenter);  
    numMaxNeighbours = new QSpinBox();
    numMaxNeighbours->setRange(0,9);

    labelExactNeighbours = new QLabel("Nombre de voisins exact");
    labelExactNeighbours->setAlignment(Qt::AlignCenter);
    numExactNeighbours = new QSpinBox();
    numExactNeighbours->setRange(0,9);


    labelDimensions = new QLabel("Dimensions");
    labelDimensions->setAlignment(Qt::AlignCenter);
    
    labelRows = new QLabel("Lignes");
    labelRows->setAlignment(Qt::AlignCenter);
    numRows = new QLineEdit();
    numRows->setText("20");
    numRows->setAlignment(Qt::AlignCenter);
    numRows->setFixedWidth(25);


    labelCols = new QLabel("Colonnes");
    labelCols->setAlignment(Qt::AlignCenter);
    numCols = new QLineEdit();
    numCols->setText("20");
    numCols->setAlignment(Qt::AlignCenter);
    numCols->setFixedWidth(25);


    for (unsigned int i(0); i<4; ++i)
    {
        mainVLayout[i] = new QVBoxLayout();
    }
    mainVLayout[0]->addWidget(labelMinNeighbours);
    mainVLayout[0]->addWidget(numMinNeighbours);

    mainVLayout[1]->addWidget(labelMaxNeighbours);
    mainVLayout[1]->addWidget(numMaxNeighbours);

    mainVLayout[2]->addWidget(labelExactNeighbours);
    mainVLayout[2]->addWidget(numExactNeighbours);

    mainVLayout[3]->addWidget(labelDimensions);
    
    for (unsigned int i(0); i<2; ++i)
    {
        subVLayout[i] = new QVBoxLayout();
    }
    subVLayout[0]->addWidget(labelRows);
    subVLayout[0]->addWidget(numRows);
    subVLayout[1]->addWidget(labelCols);
    subVLayout[1]->addWidget(numCols);

    subHLayout = new QHBoxLayout();
    subHLayout->addLayout(subVLayout[0]);
    subHLayout->addLayout(subVLayout[1]);

    mainVLayout[3]->addLayout(subHLayout);

    mainHLayout = new QHBoxLayout();
    for (unsigned int i(0); i<4; ++i)
    {
        mainHLayout->addLayout(mainVLayout[i]);
    }


    interface2D = new QVBoxLayout(this);
    interface2D->addLayout(mainHLayout);


/********************************************************************
********************************************************************

                    DEFINITION DE LA SIMULATION

********************************************************************
********************************************************************/


    simulation = new QPushButton("New Simulation 2D");
    connect(simulation, SIGNAL(clicked()), this, SLOT(simulate2D()));

    nextGeneration = new QPushButton("Next Generation");
    connect(simulation, SIGNAL(clicked()), this, SLOT(generate2D()));

    interface2D->addWidget(simulation);

    unsigned int nbRows = numRows->text().toInt();
    unsigned int nbCols = numCols->text().toInt();


    states= new QTableWidget(nbRows, nbCols, this);
    states->setFixedSize(nbRows*nbCols, nbRows*nbCols);

    for(unsigned int i(0); i<nbRows; ++i)
    {
        states->setRowHeight(i, nbRows);
        for(unsigned int j(0); j<nbCols; ++j)
        {
            if(i==0)
                states->setColumnWidth(j, nbCols);

            states->setItem(i,j,new QTableWidgetItem(""));
            states->item(i,j)->setBackgroundColor("white");
            states->item(i,j)->setFlags(Qt::ItemIsEnabled);
        }
    }

    states->verticalHeader()->setVisible(false);
    states->horizontalHeader()->setVisible(false);
    states->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    states->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    interface2D->addWidget(states);
    connect(states, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(cellActivation2D(QModelIndex)));

    this->setLayout(interface2D);

    continueGenerate = new bool;
    *continueGenerate = false;
}



void AutoCell2D::cellActivation2D(QModelIndex indx)
{
    unsigned int i = indx.row();
    unsigned int j = indx.column();
    if(states->item(i,j)->backgroundColor() == "white")
        states->item(i,j)->setBackgroundColor("green");
    else
        states->item(i,j)->setBackgroundColor("white");
}


void AutoCell2D::simulate2D(){

    unsigned int nbRows = numRows->text().toInt();
    unsigned int nbCols = numCols->text().toInt();
    
    unsigned int nbMin = numMinNeighbours->value();
    unsigned int nbMax = numMaxNeighbours->value();
    unsigned int nbExact = numExactNeighbours->value();

    Automate2D a(nbMin, nbMax, nbExact);

    Etat2D e(nbRows, nbCols);

    for(unsigned int i(0); i<nbRows; ++i)
    {
        for(unsigned int j(0); j<nbCols; ++j){
            if(states->item(i,j)->backgroundColor() == "white")
                e.setCellule(i, j, 0);
            else
                e.setCellule(i, j, 1);                        
        }
    }

    Simulateur2D s(a, e);

//    for (unsigned int k(0); k<20; ++k)
  //  {
        s.next();
        const Etat2D& tmpEtat = s.dernier();

        for (unsigned int i(0); i<nbRows; ++i)
        {
            for (unsigned int j(0); j<nbCols; ++j)
            {
                if(tmpEtat.getCellule(i,j) == 1)
                    states->item(i,j)->setBackgroundColor("green");
                else
                    states->item(i,j)->setBackgroundColor("white");
            }
        }
        Sleep(500);
    //}
//*/

}

void AutoCell2D::generate2D()
{

}

SecondMainWindow::SecondMainWindow()
{
    /*
    menuFichier =new QMenu(menuBar()->addMenu("&Fichier"));
    menuEdition = new QMenu(menuBar()->addMenu("&Edition"));
    menuAffichage = new QMenu(menuBar()->addMenu("&Affichage"));

    actionQuitter = new QAction("&Quitter", this);
    menuFichier->addAction(actionQuitr);

    fichiersRecents = new QMenu(menuFichier->addMenu("Fichiers &récents"));
    fichiersRecents->addAction("Fic

    hier bidon 1.txt");
    fichiersRecents->addAction("Fichier bidon 2.txt");
    fichiersRecents->addAction("Fichier bidon 3.txt");

    */
    AutoCell2D *appli = new AutoCell2D(this);
    setCentralWidget(appli);
}
