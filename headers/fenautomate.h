#ifndef FENAUTOMATE_H
#define FENAUTOMATE_H
#include "automate.h"
#include "headers/etat.h"
#include "headers/simulateur.h"

#include <QWidget>
#include <QMainWindow>
#include <QPushButton>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <cstdlib>
#include <ctime>
#include <QLabel>
#include <QSpinBox>
#include <QLineEdit>
#include <QIntValidator>
#include <QTableView>
#include <QTableWidget>
#include <QGridLayout>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QTableWidgetItem>
#include <QSize>
#include <QTimer>
#include <QSlider>
#include <QComboBox>
#include <QSizePolicy>

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
    QPushButton* BTinit;
    QComboBox* choixInit;
    QSlider* mySlider;
    QTimer* myTimer;
    QWidget* myCentralWidget; // Il faut définir un widget pour le centre

    QTableWidget* maGrid; // La grille affichée.
   //
    bool playPause;
    void UImaker(); // Fonction qui fait l'interface, pour eviter d'avoir 2x le même morceau de code pour les 2 constructeurs

public:
    fenAutomate(Simulateur* s);
    fenAutomate(QString nom, Simulateur* s);

    virtual ~fenAutomate(){
        if(monSimu != nullptr)
        delete monSimu;
        delete monLayout;
        delete BTavancer;
        delete BTreculer;
        delete BTplay;
        delete BTinit;
        delete choixInit;
        delete mySlider;
        delete myTimer;
        delete myCentralWidget;
    }

    virtual void avancer() = 0;
    virtual void reculer() = 0;
    virtual void initialize() = 0;
    virtual void resizeGrid() = 0;
    virtual void refreshGrid() = 0;
    virtual void addCols(unsigned int c=1) = 0;
    virtual void redimensionner() = 0;

public slots:
    void slotRedimensionner();
    void slotAjoutColonne();
    void slotChangeRules();

    void slotAvancer();
    void slotReculer();
    void slotInit();
    void slotTimerIntervalChange(int i);
    void slotBtPlayStop();

    virtual void cellChange(unsigned int i, unsigned int j) = 0;

};

#endif // FENAUTOMATE_H
