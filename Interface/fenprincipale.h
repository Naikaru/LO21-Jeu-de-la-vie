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
#include "fenautomate.h"

class FenPrincipale : public QMainWindow
{
Q_OBJECT
public:
    FenPrincipale();
    ~FenPrincipale();
public slots:
    void new_Automate();
private:
    // Zone du milieu
    QMdiArea* myMDI;
    QMenu* menuFichier;
    QMenu* menuAutomate;
    QToolBar* leftToolBar;
    QAction *actionNewAutomate;

    void ajouter_automate();
};

#endif // FENPRINCIPALE_H
