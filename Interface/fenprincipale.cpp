#include "fenprincipale.h"

FenPrincipale::FenPrincipale():QMainWindow()
{
    setWindowTitle("Automatator");
    setWindowIcon(QIcon(":/bacteria.png"));
    myMDI = new QMdiArea;
    // Deux boutons
    menuFichier = menuBar()->addMenu("&Fichier");
    menuAutomate = menuBar()->addMenu("&Automate");

    // Action de quitter
    QAction *actionQuit = new QAction(QIcon(":/error.png"),"Fermer",this);
    menuFichier->addAction(actionQuit);

    // Action d'ajouter un automate
    actionNewAutomate = new QAction(QIcon(":/plus.png"),"&Nouvel Automate", this);
    menuAutomate->addAction(actionNewAutomate);

    // Action de ranger les automates
    QAction *actionCascadeAutomate = new QAction(QIcon(":/cascad.png"),"Automates en cascade", this);
    menuAutomate->addAction(actionCascadeAutomate);

    // Action de Fermet l'automate courrant
    QAction *actionCloseCurrentAutomate = new QAction(QIcon(":/close-one.png"),"Fermer automate courant", this);
    menuAutomate->addAction(actionCloseCurrentAutomate);

    // Action de fermet tous les automates
    QAction *actionCloseAllAutomates = new QAction(QIcon(":/close-all.png"),"Fermer tout", this);
    menuAutomate->addAction(actionCloseAllAutomates);


    // Connexions
    connect(actionCloseCurrentAutomate,SIGNAL(triggered()),myMDI,SLOT(closeActiveSubWindow()));
    connect(actionCascadeAutomate,SIGNAL(triggered()),myMDI,SLOT(cascadeSubWindows()));
    connect(actionCloseAllAutomates,SIGNAL(triggered()),myMDI,SLOT(closeAllSubWindows()));
    connect(actionNewAutomate,SIGNAL(triggered()),this,SLOT(new_Automate()));
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

void FenPrincipale::new_Automate(){
   ajouter_automate();
}

void FenPrincipale::ajouter_automate(){
    QString nomAutomate = QInputDialog::getText(this,"Nom Automate","Entrez un nom à cet automate");
    if(nomAutomate=="")return;
    while(nomAutomate.length()>20){
        nomAutomate = QInputDialog::getText(this,"Nom Automate","Nom trop long !");
        if(nomAutomate=="")return;
    }
     fenAutomate* newFenAutomate = new fenAutomate(nomAutomate); // On crée un nouvel automate
     QMdiSubWindow* newSubWindow = new QMdiSubWindow; // On crée une nouvelle sub window
     newSubWindow->setWidget(newFenAutomate); // on set l'automate sur la window
     newSubWindow->setAttribute(Qt::WA_DeleteOnClose); // On appelle le destructeur si elle est fermée
     myMDI->addSubWindow(newSubWindow); // On accroche cette nouvelle fenêtre au mdi

    QWidget* myWidget = new QWidget(leftToolBar);
    QHBoxLayout* newLayout = new QHBoxLayout(myWidget);
    QPushButton* actionShowAutomate = new QPushButton(nomAutomate,myWidget); // On crée une nouvelle action
    QPushButton* actionCloseAutomate = new QPushButton(QIcon(":/rubbish-bin.png"),"",myWidget); // On crée une nouvelle action
    newLayout->addWidget(actionCloseAutomate);
    newLayout->addWidget(actionShowAutomate);
    myWidget->setLayout(newLayout);
    actionCloseAutomate->setFixedWidth(30);
    actionShowAutomate->setFlat(true);
    actionCloseAutomate->setFlat(true);
//    actionCloseAutomate->move(newWidget->pos().x() + actionShowAutomate->width(),newWidget->pos().y());

    leftToolBar->addWidget(myWidget); // On l'ajoute à la toolbar (c'est un attribut)

    connect(actionShowAutomate,SIGNAL(clicked()),newSubWindow,SLOT(setFocus()));
    connect(actionCloseAutomate,SIGNAL(clicked()),newSubWindow,SLOT(close()));
    connect(newSubWindow,SIGNAL(destroyed()),actionShowAutomate,SLOT(deleteLater()));;
    connect(newSubWindow,SIGNAL(destroyed()),newLayout,SLOT(deleteLater()));;
    connect(newSubWindow,SIGNAL(destroyed()),myWidget,SLOT(deleteLater()));;
    newSubWindow->show(); // ON MONTRE

}

FenPrincipale::~FenPrincipale(){
    delete actionNewAutomate;
    delete leftToolBar;
    delete myMDI;
}

