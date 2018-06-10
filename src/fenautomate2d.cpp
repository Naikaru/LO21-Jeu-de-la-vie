#include "headers/fenautomate2d.h"



fenAutomate2D::fenAutomate2D(QString nom, Simulateur* s):fenAutomate(nom,s) {
    maGrid = new QTableWidget(s->getInitialState()->getNbRows(),s->getInitialState()->getNbCols());
    monLayout->addWidget(maGrid,0,0,90,100);
    maGrid->horizontalHeader()->hide();
    maGrid->verticalHeader()->hide();

    unsigned int cols = monSimu->dernier().getNbCols();
    unsigned int rows = monSimu->dernier().getNbRows();

    for(unsigned int i(0);i<rows;i++){
        for(unsigned int j(0);j<cols;j++){
          maGrid->setItem(i,j,new QTableWidgetItem(""));
          maGrid->item(i,j)->setFlags(Qt::ItemIsEnabled);
        }
    }
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

void fenAutomate2D::cellChange(unsigned int i, unsigned int j){
    // Changement direct de l'utilisateur => Réinitialisation
    monSimu->setEtatDepart(monSimu->dernier());
    // Changement d'état déterminé par la méthode Automate->changeStatus (polymorphisme)
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
    const Automate* monAuto = &monSimu->getAutomate();
    adaptGridSize();
    for(int i(0);i<rows;i++){
        for(int j(0);j<cols;j++){
            maGrid->item(i,j)->setBackgroundColor(monAuto->colorize(dernier.getCellule(i,j)));
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
    unsigned short int probability = std::rand()%100;
    Etat* e = monSimu->getInitialState();
    if(choixInit->currentText().toStdString() == "Random"){
        for(unsigned int i(0); i < maGrid->rowCount(); ++i)
            for(unsigned int j(0); j < maGrid->columnCount(); ++j){
                if(probability >= std::rand()%100)
                    e->setCellule(i,j,1);
                else
                    e->setCellule(i,j,0);
            }
    }
    else if(choixInit->currentText().toStdString() == "Symetric") {
        unsigned short int boundary = (maGrid->rowCount() <= maGrid->colorCount())? maGrid->rowCount():maGrid->colorCount();
        // La symétrie n'est possible que sur la partie carrée de la matrice.
        for(unsigned int i(0); i < boundary; ++i){
            for (unsigned int j(i); j < boundary; ++j){
                if(probability >= std::rand()%100){
                    e->setCellule(i,j,1);
                    e->setCellule(j,i,1);
                }
                else{
                    e->setCellule(i,j,0);
                    e->setCellule(j,i,0);
                }
            }
        }
    }
    monSimu->reset();
    // On remet l'état de départ avec les changements.
    refreshGrid();
    // On met les couleurs de la grille à jour.
}
