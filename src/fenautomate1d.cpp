#include "headers/fenautomate1d.h"

fenAutomate1D::fenAutomate1D(QString nom, Simulateur *s): fenAutomate(nom,s)
{
    maGrid = new QTableWidget(1, s->getInitialState()->getNbCols(), this);
    monLayout->addWidget(maGrid,0,0,90,100);
    maGrid->horizontalHeader()->hide();
    maGrid->verticalHeader()->hide();
    maGrid->verticalHeader()->setMinimumSectionSize(1);
    maGrid->horizontalHeader()->setMinimumSectionSize(1);
    unsigned int cols = monSimu->dernier().getNbCols();

    for(unsigned int j(0);j<cols;j++){
      maGrid->setItem(0,j,new QTableWidgetItem(""));
      maGrid->item(0,j)->setFlags(Qt::ItemIsEnabled);
    }
    connect(maGrid,SIGNAL(clicked(QModelIndex)),this,SLOT(slotGridClick(QModelIndex)));
    //monSimu->reset();
}



void fenAutomate1D::resizeGrid(){
    unsigned int cols = monSimu->dernier().getNbCols();
    unsigned int rows = maGrid->rowCount();

    //adaptGridSize();
    int size = (int) maGrid->size().width()/cols;

    for(unsigned int i(0);i<rows;i++){
       maGrid->setRowHeight(i,size);
    }

    for(unsigned int j(0);j<cols;j++){
      maGrid->setColumnWidth(j,size);
    }
}




void fenAutomate1D::addStep(){
    const Etat& dernier = monSimu->dernier(); // On récupère le dernier état
    int cols = (int) dernier.getNbCols();  // nb de colonnes de l'état
    const Automate* monAuto = monSimu->getAutomate();
    int row = (int) maGrid->rowCount();

    // On introduit une nouvelle ligne correspondant à la génération suivante
    maGrid->setRowCount(row+1);
    maGrid->setRowHeight(row, (int) maGrid->size().width()/cols);
    for(unsigned int j(0); j<cols; ++j){
        maGrid->setItem(row,j, new QTableWidgetItem(""));
        maGrid->item(row,j)->setFlags(Qt::ItemIsEnabled);
        // Chercher un moyen de rendre inaccessibled les cases maGrid->item(row-1,j)
        maGrid->item(row,j)->setBackgroundColor(monAuto->colorize(dernier.getCellule(0,j)));
        // un état de Automate1D n'a qu'une seule ligne. donc getCellule(0,j)
        maGrid->setColumnWidth(j, (int) maGrid->size().width()/cols);

    }
    maGrid->scrollToBottom();
}


void fenAutomate1D::slotGridClick(QModelIndex j){
    if(j.row() == maGrid->rowCount() - 1)
    cellChange(j.row(),j.column());
}

void fenAutomate1D::cellChange(unsigned int i, unsigned int j)
{
    // Changement direct de l'utilisateur => Réinitialisation
    monSimu->setEtatDepart(monSimu->dernier());
    // Changement d'état déterminé par la méthode Automate->changeStatus (polymorphisme)
    monSimu->changeStatus(0,j);

    // On prends l'item de la grille cliqué, on récupère la valeur correspondante dans l'etat initial, et on affiche
    // la couleur correspondante via la fonction dédiée dans l'automate
    maGrid->item(i,j)->setBackgroundColor(monSimu->getAutomate()->colorize(monSimu->getInitialState()->getCellule(0,j)));
    monSimu->reset();
}

void fenAutomate1D::avancer(){
    monSimu->next();
    addStep();
    maGrid->repaint();
}


void fenAutomate1D::reculer(){
    //monSimu->next();
    //refreshGrid();
    //maGrid->repaint();
}


void fenAutomate1D::reinitialize(){
    for(unsigned int i(maGrid->rowCount()-1); i>0; --i){
        maGrid->removeRow(i);
        // delete toutes les lignes, qui avaient de toute façon uniquement un caractère visuel pour le 1D
    }
    maGrid->repaint();
    for(unsigned int j(0); j<maGrid->columnCount(); ++j){
        maGrid->item(0,j)->setBackgroundColor("white");
        // Le blanc est tout le temps la référence d'une grille vide
        // Sinon
        //maGrid->item(0,j)->setBackgroundColor(monSimu->getAutomate()->colorize(monSimu->dernier().getCellule(0,j)));
    }
    maGrid->repaint();
}

void fenAutomate1D::refreshGrid(){
    const Etat& dernier = monSimu->dernier();
    unsigned int cols = (int) dernier.getNbCols();
    unsigned int row = maGrid->rowCount();
    const Automate* monAuto = monSimu->getAutomate();
    //adaptGridSize();
    for(int j(0);j<cols;j++){
        maGrid->item(row-1,j)->setBackgroundColor(monAuto->colorize(dernier.getCellule(0,j)));
    }
}


void fenAutomate1D::addCols(unsigned int c){
    unsigned int cols = maGrid->columnCount();
    unsigned int row = maGrid->rowCount() - 1;
    maGrid->setColumnCount(cols+c);
    for(unsigned int j(cols); j<cols+c; ++j){
        maGrid->setItem(row,j, new QTableWidgetItem(""));
        maGrid->item(row,j)->setFlags(Qt::ItemIsEnabled);
        maGrid->item(row,j)->setBackgroundColor(monSimu->getAutomate()->colorize(monSimu->dernier().getCellule(0,j)));
    }
    resizeGrid();
}

void fenAutomate1D::redimensionner(){
    QWidget* widgetDimensions = new QWidget();
    QFormLayout* mainLayout = new QFormLayout();

    dimCols = new QSpinBox(widgetDimensions);
    dimCols->setRange(1,100);
    dimCols->setValue(monSimu->dernier().getNbCols());

    QPushButton* BtOk = new QPushButton("Valider");
    connect(BtOk, SIGNAL(clicked()), this, SLOT(slotUpdateDimensions()));

    QPushButton* BtCancel = new QPushButton("Annuler");
    connect(BtCancel, SIGNAL(clicked()), widgetDimensions,SLOT(close()));

    QHBoxLayout* hlayout = new QHBoxLayout();
    hlayout->addWidget(BtOk);
    hlayout->addWidget(BtCancel);

    mainLayout->addRow("Nombres de colonnes :", dimCols);
    mainLayout->addRow(hlayout);

    widgetDimensions->setLayout(mainLayout);
    widgetDimensions->show();
}

void fenAutomate1D::slotUpdateDimensions(){
    monSimu->setEtatDepart(monSimu->dernier());
    unsigned int newDimCols = dimCols->value();

    monSimu->redim(1, newDimCols);  // Met l'état de départ du Simu à jour
    monSimu->reset();   // Réset le simu avec l'état de départ


    if(newDimCols < maGrid->columnCount()){
        for(unsigned int j(maGrid->columnCount()-1); j>=newDimCols; --j)
            maGrid->removeColumn(j);
    }
    else if(newDimCols > maGrid->columnCount())
        addCols(newDimCols - maGrid->columnCount());

    resizeGrid();
}
