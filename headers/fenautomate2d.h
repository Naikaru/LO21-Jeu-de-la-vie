#ifndef FENAUTOMATE2D_H
#define FENAUTOMATE2D_H
#include <QWidget>
#include <QMainWindow>
#include <QPushButton>
#include "automate.h"
#include "headers/etat.h"
#include "headers/simulateur.h"
#include <cstdlib>
#include <ctime>
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
#include "fenautomate.h"


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
    virtual void initialize(); // test d'initialisation, à passer en slot : initialisation aléatoire ou symétrique
    void refreshGrid();
    void cellChange(int i, int j); // Fonction qui change la valeur de la cellule en (i,j) (vie si mort, mort si vie) dans la simu et sur la grille
    void adaptGridSize();

public slots:
    void slotSizeChange(); // Quand la taille de la fenêtre change, on appelle resizeGrid()
    void slotGridClick(QModelIndex j); // Slop appellé quand on clique sur une case, les coordonees sont passés en argument par le signal
};

#endif // FENAUTOMATE2D_H