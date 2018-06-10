#include "headers/fenprincipale.h"

FenPrincipale::FenPrincipale():QMainWindow()
{
    setWindowTitle("Automatator");
    setWindowIcon(QIcon(":/img/bacteria.png"));
    myMDI = new QMdiArea;
    // Deux boutons
    QMenu *menuFichier = menuBar()->addMenu("&Fichier");
    QMenu *menuAutomate = menuBar()->addMenu("&Automate");

    // Action de quitter
    QAction *actionQuit = new QAction(QIcon(":/img/error.png"),"Fermer",this);
    menuFichier->addAction(actionQuit);

    // Action d'ajouter un automate
    actionNewAutomate = new QAction(QIcon(":/img/plus.png"),"&Nouvel Automate", this);
    menuAutomate->addAction(actionNewAutomate);

    // Action de ranger les automates
    QAction *actionCascadeAutomate = new QAction(QIcon(":/img/cascad.png"),"Automates en cascade", this);
    menuAutomate->addAction(actionCascadeAutomate);

    // Action de Fermet l'automate courrant
    QAction *actionCloseCurrentAutomate = new QAction(QIcon(":/img/close-one.png"),"Fermer automate courant", this);
    menuAutomate->addAction(actionCloseCurrentAutomate);

    // Action de fermet tous les automates
    QAction *actionCloseAllAutomates = new QAction(QIcon(":/img/close-all.png"),"Fermer tout", this);
    menuAutomate->addAction(actionCloseAllAutomates);

    maker = Automatemaker::getInstance();
    // Connexions
    connect(actionCloseCurrentAutomate,SIGNAL(triggered()),myMDI,SLOT(closeActiveSubWindow()));
    connect(actionCascadeAutomate,SIGNAL(triggered()),myMDI,SLOT(cascadeSubWindows()));
    connect(actionCloseAllAutomates,SIGNAL(triggered()),myMDI,SLOT(closeAllSubWindows()));
    connect(actionNewAutomate,SIGNAL(triggered()),maker,SLOT(show()));
    connect(maker,SIGNAL(newAuto(fenAutomate*)),this,SLOT(new_Automate(fenAutomate*)));
    connect(actionQuit,SIGNAL(triggered()),qApp,SLOT(quit()));

    // On init la toolbar
    leftToolBar = new QToolBar("ToolBarAutomat",this); // Nouvelle toolBar
    leftToolBar->setMovable(false); // Qu'on ne peut pas bouger
    leftToolBar->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);// Elle est flexible
    addToolBar(Qt::LeftToolBarArea,leftToolBar);// On l'ajoute à notre QMainWindow, à gauche
    leftToolBar->addAction(actionNewAutomate); // On lui ajoute une action (définie plus haut);
    leftToolBar->addSeparator();


    // Petits règlages MDI
    myMDI->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    myMDI->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    setCentralWidget(myMDI); // On affiche le MDI
    //->> ICI TOUT MARCHE


}


void FenPrincipale::new_Automate(fenAutomate* newFenAutomate){
   ajouter_automate(newFenAutomate);
}


void FenPrincipale::ajouter_automate(fenAutomate* newFenAutomate){
     maker->hide();
     QMdiSubWindow* newSubWindow = new QMdiSubWindow; // On crée une nouvelle sub window
     newSubWindow->setWidget(newFenAutomate); // on set l'automate sur la window
     newSubWindow->setAttribute(Qt::WA_DeleteOnClose); // On appelle le destructeur si elle est fermée
     myMDI->addSubWindow(newSubWindow); // On accroche cette nouvelle fenêtre au mdi

    // On crée un widget pour mettre les 2 boutons
    QWidget* myWidget = new QWidget(leftToolBar);
    QHBoxLayout* newLayout = new QHBoxLayout(myWidget);// avec un layout pour faire joli

    // Deux nouveaux boutons/actions: pour prendre le focus et pour fermer l'automate
    QPushButton* actionShowAutomate = new QPushButton(newFenAutomate->windowTitle(),myWidget); // On crée une nouvelle action
    QPushButton* actionCloseAutomate = new QPushButton(QIcon(":/img/rubbish-bin.png"),"",myWidget); // On crée une nouvelle action

    newLayout->addWidget(actionCloseAutomate); // On ajoute nos actions au layour
    newLayout->addWidget(actionShowAutomate);

    myWidget->setLayout(newLayout);// On set le layout sur notre widget

    actionCloseAutomate->setFixedWidth(30);// On fait toussa joli
    actionShowAutomate->setFlat(true);
    actionCloseAutomate->setFlat(true);
    //

    leftToolBar->addWidget(myWidget); // On ajoute le widget à la toolbar (la toolbar est un attribut)

    // Et on connecte tout ça pour que:
    connect(actionShowAutomate,SIGNAL(clicked()),newSubWindow,SLOT(setFocus())); // Quand on click sur le nom du widget, on choppe le focus
    connect(actionCloseAutomate,SIGNAL(clicked()),newSubWindow,SLOT(close())); // Quand on click sur la poubelle, ça quitte l'automate
    connect(newSubWindow,SIGNAL(destroyed()),actionShowAutomate,SLOT(deleteLater())); // Quand l'automate est détruit, l'action show
    connect(newSubWindow,SIGNAL(destroyed()),actionCloseAutomate,SLOT(deleteLater())); // l'action delete
    connect(newSubWindow,SIGNAL(destroyed()),newLayout,SLOT(deleteLater())); // le layout
    connect(newSubWindow,SIGNAL(destroyed()),myWidget,SLOT(deleteLater())); // et le widget soient détruits
    newSubWindow->show(); // ON MONTRE notre création

}

// Destructeur
FenPrincipale::~FenPrincipale(){
    delete actionNewAutomate;
    delete leftToolBar;
    delete myMDI;
}

