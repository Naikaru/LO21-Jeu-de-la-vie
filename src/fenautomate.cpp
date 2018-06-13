#include "headers/fenautomate.h"

fenAutomate::fenAutomate(Simulateur* s):monSimu(s)
{
    setWindowTitle("Automate anonyme");
    UImaker();
}


fenAutomate::fenAutomate(QString nom, Simulateur* s): monSimu(s)
{
    setWindowTitle(nom);
    UImaker();
}


void fenAutomate::UImaker(){

    setWindowIcon(QIcon(":/img/virus.png"));
    QMenu *menuSettings = menuBar()->addMenu("&Settings");

    // Dimensionnement de la grille
    QMenu *menuDimensions = menuSettings->addMenu(QIcon(":/img/layout.png"), "Dimensions");

    // Redimensionnement complet
    QAction* actionRedimensionner = new QAction("Redimensionnement",this);
    menuDimensions->addAction(actionRedimensionner);
    connect(actionRedimensionner, SIGNAL(triggered()),this,SLOT(slotRedimensionner()));

    // Ajout d'une colonne
    QAction* actionAjouterColonne = new QAction("Ajouter une colonne",this);
    menuDimensions->addAction(actionAjouterColonne);
    connect(actionAjouterColonne,SIGNAL(triggered()),this,SLOT(slotAjoutColonne()));

    // Modification des règles de transition
    QAction* actionRules = new QAction(QIcon(":/img/rules.png"),"Règles",this);
    menuSettings->addAction(actionRules);
    connect(actionRules,SIGNAL(triggered()),this,SLOT(slotChangeRules()));


    // Configuration des fonctionnalités l'IHM
    playPause = true;
    setMinimumSize(500,500);
    myCentralWidget = new QWidget;

    BTavancer = new QPushButton(QIcon(":/img/fast-forward-2.png"),"", myCentralWidget);
    BTreculer = new QPushButton(QIcon(":/img/backward.png"),"",myCentralWidget);
    BTplay = new QPushButton(QIcon(":/img/play-button.png"),"", myCentralWidget);
    BTinit = new QPushButton(QIcon(":/img/shuffle.png"),"", myCentralWidget);
    choixInit = new QComboBox();
    choixInit->addItem("Random");
    choixInit->addItem("Symetric");
    BTreset = new QPushButton(QIcon(":/img/reset-button.png"),"", myCentralWidget);

    BTplay->setSizePolicy(QSizePolicy::Maximum,QSizePolicy::Maximum);
    BTplay->setFlat(true);
    BTreculer->setFlat(true);
    BTavancer->setFlat(true);
    BTinit->setFlat(true);
    BTreset->setFlat(true);

    myTimer = new QTimer(this);
    mySlider = new QSlider(Qt::Horizontal);
    mySlider->setMinimum(1);mySlider->setMaximum(1000);
    mySlider->setValue(750);
    mySlider->setInvertedAppearance(true);
    mySlider->setStyleSheet("""QSlider::groove:horizontal {border: 2px solid #A0A5B2; border-radius: 2px;height: 4px;background: #E8E8E8;}QSlider::handle:horizontal {background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,stop: 0 #FFFFFF, stop: 0.7 #3975D7,stop: 1.0 #C0C0FF);width: 20px;border-top: 1px solid #FFFFFF; border-left: 1px solid #0000FF; border-right: 1px solid #0000FF;border-bottom: 2px solid #0000CC;border-radius: 2px;margin: -3px 0;}""");
    myTimer->setInterval(mySlider->value());

    connect(myTimer,SIGNAL(timeout()),this,SLOT(slotAvancer()));
    connect(BTplay, SIGNAL(clicked()),this,SLOT(slotBtPlayStop()));
    connect(mySlider,SIGNAL(sliderMoved(int)),this,SLOT(slotTimerIntervalChange(int)));
    connect(BTavancer,SIGNAL(clicked()),this,SLOT(slotAvancer()));
    connect(BTreculer,SIGNAL(clicked()),this,SLOT(slotReculer()));
    connect(BTinit, SIGNAL(clicked()),this,SLOT(slotInit()));
    connect(BTreset, SIGNAL(clicked()),this,SLOT(slotReset()));

    QHBoxLayout* BTLayout = new QHBoxLayout;
    BTLayout->addWidget(BTreculer);
    BTLayout->addWidget(BTplay);
    BTLayout->addWidget(BTavancer);
    BTLayout->addWidget(BTreset);
    BTLayout->addWidget(BTinit);
    BTLayout->addWidget(choixInit);

    monLayout = new QGridLayout;
    monLayout->addLayout(BTLayout,90,0,5,100);
    monLayout->addWidget(mySlider,95,0,5,100);
    setCentralWidget(myCentralWidget);
    myCentralWidget->setLayout(monLayout);
}


void fenAutomate::slotBtPlayStop(){
    if(playPause){
        BTplay->setIcon(QIcon(":/img/pause.png"));
        myTimer->start(mySlider->value());
        playPause = false;
    }else{
        myTimer->stop();
        BTplay->setIcon(QIcon(":/img/play-button.png"));
        playPause = true;
    }
    BTplay->repaint();
}


void fenAutomate::slotAjoutColonne(){
    monSimu->setEtatDepart(monSimu->dernier());
    monSimu->addCol();  // Met l'état de départ du Simu à jour
    monSimu->reset();   // Réset le simu avec l'état de départ
    addCols(1);         // Méthode qui met la grille d'affichage à jour.
}

void fenAutomate::slotRedimensionner(){
    redimensionner();
}

void fenAutomate::slotChangeRules(){
    monSimu->getAutomate()->changeRules();
}

void fenAutomate::slotTimerIntervalChange(int i){
    if(myTimer==nullptr) return;
    myTimer->setInterval(i);
}


void fenAutomate::slotAvancer(){
    avancer();
}


void fenAutomate::slotReculer(){
    reculer();
}

void fenAutomate::slotInit(){
    monSimu->setEtatDepart(monSimu->dernier());
    Etat* e = monSimu->getInitialState();

    if(choixInit->currentText().toStdString() == "Random")
        monSimu->getAutomate()->initRandom(e);
    else if(choixInit->currentText().toStdString() == "Symetric")
        monSimu->getAutomate()->initSymetric(e);

    monSimu->reset();
    // On remet l'état de départ avec les changements.
    refreshGrid();
    // On met les couleurs de la grille à jour conformément à 1D ou 2D
    maGrid->repaint();
}

void fenAutomate::slotReset(){
    monSimu->setEtatDepart(monSimu->dernier());
    Etat* e = monSimu->getInitialState(); // Renvoie l'attribut depart
    e->setAllTabValue(0); // On remet à 0 cet état de départ
    monSimu->reset();   // On réinitialise le simulateur
    // Sorte de DP Adaptateur
    reinitialize();
    // Il s'agit avec reinitialize() de modifier la grille en conséquence, si on est en 1D ou 2D
}

