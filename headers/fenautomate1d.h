#ifndef FENAUTOMATE1D_H
#define FENAUTOMATE1D_H

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
#include "headers/fenautomate.h"
#include "headers/automate1d.h"


/**
 * @brief The fenAutomate1D class
 *              Gère l'affichage d'une simulation d'automate 1D
 */
class fenAutomate1D : public fenAutomate{
Q_OBJECT
    QSpinBox* dimCols;
public:
    /**
     * @brief fenAutomate1D Constructeur de la fenetre
     * @param nom nom de la fenetre
     * @param s simulateur affiché
     */
    fenAutomate1D(QString nom, Simulateur* s);
    /**
     * @brief ~fenAutomate1D Destructeur de la fenetre1D
     */
    virtual ~fenAutomate1D(){}
    /**
     * @brief avancer Fais avancer la simulation d'un pas
     */
    virtual void avancer();
    /**
     * @brief reculer Fais reculer la simulation d'un pas
     */
    virtual void reculer();
    /**
     * @brief addCols Ajoute des colonnes à la grille
     * @param c nombre de colonnes à ajouter
     */
    virtual void addCols(unsigned int c=1);
    /**
     * @brief saveThisState sauvegarde l'état courant de la fenêtre
     * @return l'objet Json qui contient toutes les valeurs de la simulation
     */
    virtual void redimensionner();
    /**
     * @brief reinitialize Reinitialise la simulation
     */
    virtual void reinitialize();
    /**
     * @brief resizeGrid Redimentionne les cellules de la grille
     */
    virtual void resizeGrid();
    /**
     * @brief refreshGrid Mets à jour la grille par rapport à la simulation en cours
     */
    virtual void refreshGrid();
    /**
     * @brief addStep Ajoute une etape à la simulation
     */
    void addStep();

    /**
     * @brief cellChange Applique une modification à la cellule dont les coordonnées sont passées en paramètre (ex. après un click de l'utilisateur).
     * @param i Numero de la ligne
     * @param j Numero de la colonne
     */
    virtual void cellChange(unsigned int i, unsigned int j);
public slots:
    /**
     * @brief slotUpdateDimensions mets à jour les dimensions de la drille
     */
    void slotUpdateDimensions();
    /**
     * @brief slotGridClick Mets à jour l'enlement cliqué de la grille
     * @param j element de la grille qui doit être mis à jour
     */
    void slotGridClick(QModelIndex j); // Slop appellé quand on clique sur une case, les coordonees sont passés en argument par le signal
};



#endif // FENAUTOMATE1D_H
