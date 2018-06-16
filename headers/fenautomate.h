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
#include <QJsonObject>
#include <QFile>
#include <QFileDialog>
#include <QJsonDocument>

/**
 * @brief The fenAutomate class
 *               Classe mere permettant de generer une interface pour visualiser une simulation
 */
class fenAutomate : public QMainWindow
{
Q_OBJECT

protected:
   // Elements de la fenêtre
    /**
     * @brief monSimu Simulateur traîté par la fenêtre
     */
    Simulateur* monSimu;
    /**
     * @brief monLayout Layout principal
     */
    QGridLayout* monLayout;
    /**
     * @brief BTavancer Bouton pour faire avancer la simulation
     */
    QPushButton* BTavancer;
    /**
     * @brief BTreculer Bouton pour faire reculer la simulation
     */
    QPushButton* BTreculer;
    /**
     * @brief BTplay Bouton qui fait avancer la simulation tant que l'utilisateur ne re-click pas dessus
     */
    QPushButton* BTplay;
    /**
     * @brief BTinit Bouton qui initialise la simulation
     */
    QPushButton* BTinit;
    /**
     * @brief BTreset Bouton qui remets la simulation à 0
     */
    QPushButton* BTreset;
    /**
     * @brief choixInit Combobox pour choisir quelle initialisation faire (aléatoire, symetrique, etc..)
     */
    QComboBox* choixInit;
    /**
     * @brief mySlider Slider pour choisir l'interval de temps entre 2 avances automatique, lorsque l'automate avance tout seul
     */
    QSlider* mySlider;
    /**
     * @brief myTimer Timer qui permet l'avance automatique de la simulation
     */
    QTimer* myTimer;
    /**
     * @brief myCentralWidget Widget central, qui contient tous les élèments de l'interface
     */
    QWidget* myCentralWidget; // Il faut définir un widget pour le centre
    /**
     * @brief maGrid Grille qui affiche l'etat de la simulation à un instant T
     */
    QTableWidget* maGrid; // La grille affichée.
   //
    bool playPause;
    /**
     * @brief sauvegarde Sauvegarde la simulation en cours, appelle une boite de dialogue pour obtenir le chemin
     * @return 1 si la sauvegarde a fonctionné, 0 sinon
     */
    bool sauvegarde();
    /**
     * @brief sauvegarde Sauvegarde la simulation en cours dans le fichier dont le chemin est passé en argument
     * @return 1 si la sauvegarde a fonctionné, 0 sinon
     */
    bool sauvegarde(QString& path);
    /**
     * @brief UImaker Crée l'interface de la fenêtre
     */
    void UImaker(); // Fonction qui fait l'interface, pour eviter d'avoir 2x le même morceau de code pour les 2 constructeurs
    /**
     * @brief resizeEvent Redéfinition de la fonction resizeEvent de QMainWindow, appellée lorsque l'utilisateur
     * @param event parametre passé par Qt, demandé dans la fonction de base
     */
    void resizeEvent(QResizeEvent* event)
    {
       QMainWindow::resizeEvent(event);
       resizeGrid();
       // Your code here.
    }
public:
    /**
     * @brief fenAutomate Constructeur de la fenêtre
     * @param s simulateur qui doit être affiché par la fenetre
     */
    fenAutomate(Simulateur* s);
    /**
     * @brief fenAutomate Constructeur de la fenêtre
     * @param nom Nom que doit avoir la fenêtre
     * @param s simulateur qui doit être affiché
     */
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

    /**
     * @brief avancer Fais avancer la simulation d'un pas
     */
    virtual void avancer() = 0;
    /**
     * @brief reculer Fais reculer la simulation d'un pas
     */
    virtual void reculer() = 0;
    /**
     * @brief reinitialize Reinitialise la simulation
     */
    virtual void reinitialize() = 0;
    /**
     * @brief resizeGrid Redimentionne les cellules de la grille
     */
    virtual void resizeGrid() = 0;
    /**
     * @brief refreshGrid Mets à jour la grille par rapport à la simulation en cours
     */
    virtual void refreshGrid() = 0;
    /**
     * @brief addCols Ajoute des colonnes à la grille
     * @param c nombre de colonnes à ajouter
     */
    virtual void addCols(unsigned int c=1) = 0;
    /**
     * @brief redimensionner affiche un widget qui permets de redimenssionner la grille
     */
    virtual void redimensionner() = 0;
    /**
     * @brief saveThisState sauvegarde l'état courant de la fenêtre
     * @return l'objet Json qui contient toutes les valeurs de la simulation
     */
    QJsonObject* saveThisState();
    /**
     * @brief cellChange Applique une modification à la cellule dont les coordonnées sont passées en paramètre (ex. après un click de l'utilisateur).
     * @param i Numero de la ligne
     * @param j Numero de la colonne
     */
    virtual void cellChange(unsigned int i, unsigned int j) = 0;
public slots:
    /**
     * @brief slotRedimensionner appelle la fonction redimensionner, défini dans les classes filles
     */
    void slotRedimensionner();
    /**
     * @brief slotAjoutColonne ajoute une colonne à la simulation & à la grille
     */
    void slotAjoutColonne();
    /**
     * @brief slotChangeRules slot qui appelle la fonction changeRules de l'automate contenu dans la simulation, qui affiche à l'utilisateur un widget permettant de changer les règles de la simulation
     */
    void slotChangeRules();
    /**
     * @brief slotAvancer Fait avancer la simulation d'un cran
     */
    void slotAvancer();
    /**
     * @brief slotReculer Fait reculer la simulation d'un cran
     */
    void slotReculer();
    /**
     * @brief slotInit Initialise la simulation
     */
    void slotInit();
    /**
     * @brief slotReset Remet à 0 la simulation
     */
    void slotReset();
    /**
     * @brief slotTimerIntervalChange Lorsque l'utilisateur bouge le slider, on met à jour le timer
     * @param i
     */
    void slotTimerIntervalChange(int i);
    /**
     * @brief slotBtPlayStop Active/Desactive la simulation automatique
     */
    void slotBtPlayStop();
    /**
     * @brief slotSauvegarder Appelle la fonction de sauvegarde de l'automate
     */
    void slotSauvegarder();


};

#endif // FENAUTOMATE_H
