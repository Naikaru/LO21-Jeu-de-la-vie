#ifndef FENPRINCIPALE_H
#define FENPRINCIPALE_H
#include <QApplication>
#include <QMainWindow>
#include <QMdiArea>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QMdiSubWindow>
#include <QToolBar>
#include <QInputDialog>
#include <QHBoxLayout>
#include <QPushButton>
#include <QWidget>
#include <QPoint>
#include <Qicon>
#include <QString>
#include <QIODevice>
#include <QJsonDocument>
#include <QJsonObject>
#include "headers/fenautomate.h"
#include "headers/automatemaker.h"


/**
 * @brief The FenPrincipale class
 *                  Correspond à la fenêtre principale, qui contient les autres fenêtres
 */
class FenPrincipale : public QMainWindow
{
Q_OBJECT
public:
    /**
     * @brief FenPrincipale Constructeur de la fenetre principale
     */
    FenPrincipale();
    ~FenPrincipale();
public slots:
    // Slot qui ajoute l'automate passé en paramètre dans la MDI area
    // En utilisant la fonction "ajouter_automate"
    /**
     * @brief new_Automate ajoute l'automate passé en paramètre dans la MDI area en utilisant la fonction ajouter_automate
     * @param newFenAutomate
     */
    void new_Automate(fenAutomate* newFenAutomate);
    /**
     * @brief loadAutomat charge un automate dans la MDI area a partir d'un fichier
     */
    void loadAutomat();
private:
    // Zone du milieu
    /**
     * @brief maker instance de automateMaker, qui permets de récupérer des fenAutomate à ajouter
     */
    Automatemaker* maker;
    /**
     * @brief myMDI Zone du milieu, contenant des fenêtres
     */
    QMdiArea* myMDI; // Zone du milieu
    /**
     * @brief leftToolBar Barre de gauche, contenant la liste des automates lancés
     */
    QToolBar* leftToolBar; // Barre du côté
    /**
     * @brief actionNewAutomate Action de créer un automate (bouton vert & element dans le Qmenu)
     */
    QAction *actionNewAutomate; // Action importante

    // Ajouter l'automate passé en param dans la MDI area
    /**
     * @brief ajouter_automate Ajoute un automate à la MDI area
     * @param newFenAutomate fenêtre à ajouter à la MDI area
     */
    void ajouter_automate(fenAutomate* newFenAutomate);
};

#endif // FENPRINCIPALE_H
