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

//   TODO  //
//
// 1/ Verifier le destructeur, j'ai ptet fait de la merde
//
//   FIN TODO  //

// Classe qui correspond à la fenêtre principale du programme
class FenPrincipale : public QMainWindow
{
Q_OBJECT
public:
    FenPrincipale();
    ~FenPrincipale();
public slots:
    // Slot qui ajoute l'automate passé en paramètre dans la MDI area
    // En utilisant la fonction "ajouter_automate"
    void new_Automate(fenAutomate* newFenAutomate);
private:
    // Zone du milieu
    Automatemaker* maker; // Singleton qui créer des automates
    QMdiArea* myMDI; // Zone du milieu
    QToolBar* leftToolBar; // Barre du côté
    QAction *actionNewAutomate; // Action importante

    // Ajouter l'automate passé en param dans la MDI area
    void ajouter_automate(fenAutomate* newFenAutomate);
};

#endif // FENPRINCIPALE_H
