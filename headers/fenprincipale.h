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
#include "headers/fenautomate.h"
#include "headers/automatemaker.h"


/**
 * @brief The FenPrincipale class correspond à la fenêtre principale du programme
 */
class FenPrincipale : public QMainWindow
{
Q_OBJECT
public:
    FenPrincipale();
    ~FenPrincipale();
public slots:
    /**
     * @brief new_Automate Slot qui ajoute l'automate passé en paramètre dans la MDI area
     *        En utilisant la fonction "ajouter_automate()"
     * @param newFenAutomate La fenêtre à laquelle associer l'automate cellulaire
     */
    void new_Automate(fenAutomate* newFenAutomate);
private:
    /**
     * @brief maker Permet la création d'automates
     */
    Automatemaker* maker;

    /**
     * @brief myMDI correspond à la zone du milieu de la fenêtre (à laquelle on peut ajouter d'autres fenêtres)
     */
    QMdiArea* myMDI;

    /**
     * @brief leftToolBar la zone d'option latérale permettant création/suppression/selection d'un des automates
     */
    QToolBar* leftToolBar;

    /**
     * @brief actionNewAutomate QAction permettant la génération de l'automate
     */
    QAction *actionNewAutomate; // Action importante

    /**
     * @brief ajouter_automate Ajouter la fenêtre passée en param dans la MDI area
     * @param newFenAutomate La fenêtre initialisée avec le bon automate
     */
    void ajouter_automate(fenAutomate* newFenAutomate);
};

#endif // FENPRINCIPALE_H
