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


/**
 * @brief The fenAutomate1D class
 *              Gère l'affichage d'une simulation d'automate 2D
 */
class fenAutomate2D : public fenAutomate{
Q_OBJECT
    QSpinBox* dimRows;
    QSpinBox* dimCols;

public:
    /**
     * @brief fenAutomate2D Constructeur de fenAutomate2D
     * @param nom Nom de la fenetre
     * @param s Simulateur traîté
     */
    fenAutomate2D(QString nom, Simulateur* s);
    /**
     * @brief ~fenAutomate2D destructeur de fenAutomate2D
     */
    virtual ~fenAutomate2D(){
        delete maGrid;
    }
    /**
     * @brief avancer Fais avancer la simulation d'un pas
     */
    virtual void avancer(); // Fonction qui fait avancer la simulation
    /**
     * @brief reculer Fais reculer la simulation d'un pas
     */
    virtual void reculer(); // Fonction qui fait reculer la simulation
    /**
     * @brief reinitialize Reinitialise la simulation
     */
    virtual void reinitialize(); // Remise à 0 de la grille (et du Simu mais géré par la classe mère).
    /**
     * @brief resizeGrid Redimentionne les cellules de la grille
     */
    virtual void resizeGrid(); // Redimensionne la grille pour que ça soit joli par rapport à la dimension de la fenêtre (uniquement)
    /**
     * @brief refreshGrid Mets à jour la grille par rapport à la simulation en cours
     */
    virtual void refreshGrid();
    /**
     * @brief addCols Ajoute des colonnes à la grille
     * @param c nombre de colonnes à ajouter
     */
    virtual void addCols(unsigned int c=1);
    /**
     * @brief addRows Ajoute des lignes à la grille
     * @param r Nombre de lignes à ajouter
     */
    void addRows(unsigned int r=1);
    /**
     * @brief saveThisState sauvegarde l'état courant de la fenêtre
     * @return l'objet Json qui contient toutes les valeurs de la simulation
     */
    virtual void redimensionner();
    /**
     * @brief cellChange Applique une modification à la cellule dont les coordonnées sont passées en paramètre (ex. après un click de l'utilisateur).
     * @param i Numero de la ligne
     * @param j Numero de la colonne
     */
    virtual void cellChange(unsigned int i, unsigned int j); // Fonction qui change la valeur de la cellule en (i,j) (vie si mort, mort si vie) dans la simu et sur la grille

public slots:
    /**
     * @brief slotSizeChange Slot appellé lorsque la taille de la fenêtre change
     */
    void slotSizeChange(); // Quand la taille de la fenêtre change, on appelle resizeGrid()
    /**
     * @brief slotGridClick Applique un changement sur l'element cliqué
     * @param j element cliqué
     */
    void slotGridClick(QModelIndex j); // Slop appellé quand on clique sur une case, les coordonees sont passés en argument par le signal
    /**
     * @brief slotUpdateDimensions Met à jour les dimensions des cellules
     */
    void slotUpdateDimensions();
};

#endif // FENAUTOMATE2D_H
