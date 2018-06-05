#ifndef FENAUTOMATE_H
#define FENAUTOMATE_H
#include <QWidget>
#include <QMainWindow>
#include <QPushButton>
#include "automate.h"
#include "etat.h"
#include "simulateur.h"

#include <QLabel>
#include <QSpinBox>
#include <QLineEdit>
#include <QIntValidator>
#include <QTableView>
#include <QTableWidget>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QTableWidgetItem>
#include <QSize>
#include <QTimer>
#include <QSlider>

//   TODO  //
// Dans fenAutomate
//
//
// Dans fenAutomate2D
// 1/ Fonction qui mets à jour la grille par rapport à l'etat courant dans la simulation (je sais pas très bien à quoi correspond l'etat courant)
// 2/ Fonction pour changer la valeur d'une case (passe de vie à mort ou l'inverse), et mets à jour la simulation ET la grille
// 3/ Fonction qui adapte la grille aux dimensions de l'etat initial dans la simulation (ou de l'état courant ?)
// 4/ Fonction qui modifie la taille de l'état initial (ou courant ?) dans la simulation (avec les valeurs en paramètre)
// 5/ Fonction qui fait avancer d'un pas la simulation et mets à jour la grille (appel fonction 1/)
// 6/ déjà là ...
//
// Dans fenAutomate1D
// TOUT
//   FIN TODO  //

// Classe abstraite correspondant à la fenêtre d'un automate
// Concretement c'est une gridLayout de 100 par 100 (c'est dynamique, mais il faut voir ça comme ça)
// de (0 à 90)*100 on a la grille/autre layout
// de (90 à 100)*100 on a un HBoxLayout pour les boutons
// 3 boutons pour l'instant : BTavancer, BTreculer, BTplay
class fenAutomate : public QMainWindow
{

Q_OBJECT
protected:
   // Elements de la fenêtre
    Simulateur* monSimu;
    QGridLayout* monLayout;
    QPushButton* BTavancer;
    QPushButton* BTreculer;
    QPushButton* BTplay;
    QSlider* mySlider;
    QTimer* myTimer;
    QWidget* myCentralWidget; // Il faut définir un widget pour le centre
   //
     bool playPause;
    void UImaker(); // Fonction qui fait l'interface, pour eviter d'avoir 2x le même morceau de code pour les 2 constructeurs

public:
    fenAutomate(Simulateur* s);
    fenAutomate(QString nom, Simulateur* s);
    virtual void avancer() = 0;
    virtual void reculer() = 0;
    virtual ~fenAutomate(){
        if(monSimu != nullptr)
        delete monSimu;
        delete monLayout;
        delete BTavancer;
        delete BTreculer;
        delete BTplay;
        delete mySlider;
        delete myTimer;
        delete myCentralWidget;
    }

public slots:
    void slotAvancer();
    void slotReculer();
    void slotTimerIntervalChange(int i);
    void slotBtPlayStop();

};



// Classe qui correspond à la fenêtre d'un automate 1D
class fenAutomate1D : public fenAutomate{
Q_OBJECT
    QSpinBox* num; // numéro
    QLineEdit* numeroBit[8]; // un QLineEdit par bit
    QLabel* numl;
    QLabel* numeroBitl[8];
    QVBoxLayout* numc;
    QVBoxLayout* bitc[8];
    QHBoxLayout* numeroc;
    QIntValidator* zeroOneValidator;
    QTableWidget* depart;
    QPushButton* simulation;
    QTableWidget* states = nullptr;

    unsigned int dimension = 20;
    QSpinBox* nbSim; // Nombre de générations
    QHBoxLayout* simLaye;
public:
    fenAutomate1D(QString nom, Simulateur* s);
    virtual ~fenAutomate1D(){}
    virtual void avancer(){ return; }
    virtual void reculer(){ return; }

public slots:
    void synchronizeNumToNumBit(int n);
    void synchronizeNumBitToNum(const QString& n);
    void numberGeneration(int value);

    void simulate();
    void cellActivation(QModelIndex indx);
};



// Classe qui correspond à la fenêtre d'un automate 2D
class fenAutomate2D : public fenAutomate{
Q_OBJECT
    QTableWidget* maGrid; // La grille affichée

public:
    fenAutomate2D(QString nom, Simulateur* s);
    virtual ~fenAutomate2D(){
        delete maGrid;
    }
    void resizeGrid(); // Redimensionne la grille pour que ça soit joli par rapport à la dimension de la fenêtre (uniquement)
    virtual void avancer(); // Fonction qui fait avancer la simulation
    virtual void reculer(); // Fonction qui fait reculer la simulation
    void refreshGrid();
    void cellChange(int i, int j); // Fonction qui change la valeur de la cellule en (i,j) (vie si mort, mort si vie) dans la simu et sur la grille
    void adaptGridSize();

public slots:
    void slotSizeChange(); // Quand la taille de la fenêtre change, on appelle resizeGrid()
    void slotGridClick(QModelIndex j); // Slop appellé quand on clique sur une case, les coordonees sont passés en argument par le signal

};
#endif // FENAUTOMATE_H
