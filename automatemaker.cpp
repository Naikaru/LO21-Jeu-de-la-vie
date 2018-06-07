#include "automatemaker.h"
Automatemaker* Automatemaker::instance = nullptr;
Automatemaker::Automatemaker()
{
    setWindowIcon(QIcon(":/virus.png")); // Mets une icone
    setWindowTitle("Nouvel Automate"); // Nom de la fenêtre
    setMinimumSize(200,300); // Size choisie au pif

    // DEBUT INITIALISATION DES CHAMPS
    choixAutomate = new QComboBox(this);
    setAutomateList();
    nomAutomate = new QLineEdit(this);
    btOK = new QPushButton("OK", this);
    btAnnuler = new QPushButton("Annuler", this);
    rows = new QSpinBox;
    column = new QSpinBox; column->setValue(10);

    minVoisins = new QSpinBox; minVoisins->setValue(2);
    minVoisins->setMinimum(0);
    minVoisins->setMaximum(3);

    maxVoisins = new QSpinBox; maxVoisins->setValue(3);
    maxVoisins->setMinimum(2);
    maxVoisins->setMaximum(8);

    connect(minVoisins, SIGNAL(valueChanged(int)), this, SLOT(updateMaxVoisins(int)));
    connect(maxVoisins, SIGNAL(valueChanged(int)), this, SLOT(updateMinVoisins(int)));

    exactVoisins = new QSpinBox; exactVoisins->setValue(3);
    exactVoisins->setRange(0,8);

    numeroAutomate = new QSpinBox;
    numeroAutomateLabel = new QLabel("Regle N° (chiffres) :");

    txtNumeroAutomate = new QLineEdit;
    txtNumeroAutomateLabel = new QLabel("Regle N° (lettres) :");

    buffer = new QSpinBox; buffer->setValue(2);
    buffer->setEnabled(true);
    // FIN INITIALISATION

    //rows->setMinimum(0); column->setMinimum(0); // On mets le minimum à 0

    // Lorsque l'utilisateur choisi un automate, on change les elements utilisables
    connect(choixAutomate,SIGNAL(currentIndexChanged(QString)),this,SLOT(statusChanged(QString)));
    // S'il click sur annuler on cache la fenêtre
    connect(btAnnuler,SIGNAL(clicked()),this,SLOT(hide()));

    // Init des layouts
    QVBoxLayout* principal = new QVBoxLayout;
    QFormLayout* myFormLayout= new QFormLayout;
    QHBoxLayout* btLayout= new QHBoxLayout;
    //

    // Config des layouts
    btLayout->addWidget(btAnnuler);
    btLayout->addWidget(btOK);
    myFormLayout->addRow("Nom : ",nomAutomate);
    myFormLayout->addRow("Automate :",choixAutomate);
    myFormLayout->addRow("Hauteur :",rows);
    myFormLayout->addRow("Largeur :",column);
    myFormLayout->addRow("Buffer :",buffer);
    //myFormLayout->addRow("Automate N° (chiffres) :",numeroAutomate);
    //myFormLayout->addRow("Automate N° (lettres):",txtNumeroAutomate);
    myFormLayout->addRow(numeroAutomateLabel,numeroAutomate);
    myFormLayout->addRow(txtNumeroAutomateLabel,txtNumeroAutomate);


    minVoisinsLabel = new QLabel("min Voisins : ");
    //myFormLayout->addRow("min Voisins :",minVoisins);
    myFormLayout->addRow(minVoisinsLabel, minVoisins);
    maxVoisinsLabel = new QLabel("max Voisins : ");
    //myFormLayout->addRow("max Voisins :",maxVoisins);
    myFormLayout->addRow(maxVoisinsLabel, maxVoisins);
    exactVoisinsLabel = new QLabel("exact Voisins : ");
    //myFormLayout->addRow("exact Voisins :",exactVoisins);
    myFormLayout->addRow(exactVoisinsLabel, exactVoisins);

    //

    // On a un un Vertival avec dedans un Form en haut et un horizontal pour les boutons en bas
    principal->addLayout(myFormLayout);
    principal->addLayout(btLayout);
    setLayout(principal);
    // Si on click sur OK, on crée un automate
    connect(btOK,SIGNAL(clicked()),this,SLOT(creatAuto()));

    statusChanged("Jeu de la vie"); // Sinon toutes les valeurs sont utilisables, on mets à jour (vu que c'est le premier elem)
}

// Destructeur du singleton
Automatemaker::~Automatemaker()
{
   release();
}

// Fonction de récupération du singleton
Automatemaker* Automatemaker::getInstance(){
    if(instance == nullptr) instance = new Automatemaker();
    return instance;
}

// Fonction de destruction du singleton
void Automatemaker::release(){
    if(instance==nullptr)return;
    delete instance;
    instance = nullptr;
}

// Slots appelés lorsque l'utilisateur sélectionne le nombre de voisins maximum et minimum dans le cas d'un Jeu de la Vie
void Automatemaker::updateMinVoisins(int n){
    minVoisins->setMaximum(n);
}

void Automatemaker::updateMaxVoisins(int n){
    maxVoisins->setMinimum(n);
}


// Slot appelé quand l'utilisateur appuie sur OK
void Automatemaker::creatAuto(){
    // On créer notre simulateur:
    Automate* monAutomate = nullptr;
    Simulateur* monSimu = nullptr;
    Etat* monEtat = nullptr;
    fenAutomate* mafenetre = nullptr;

    // -> ICI : Faire les tests si c'est ok au niveau des valeurs

    //Test si nom pas trop long
    if(nomAutomate->text().length() > 10){
        QMessageBox::critical(this, "Erreur :/", "Nom trop long (20 car max)");
        return;
    }
    // Si c'est un jeu de la vie
    if(choixAutomate->currentText() == "Jeu de la vie"){
       monAutomate = new GameOfLife(minVoisins->value(),maxVoisins->value(),exactVoisins->value());
       monEtat = new Etat(rows->value(),column->value());
       monSimu = new Simulateur(monAutomate,monEtat,buffer->value());
       mafenetre = new fenAutomate2D("GameOfLife : "+ nomAutomate->text(),monSimu);
      }
    // Si c'est un automate 1D
    else if(choixAutomate->currentText() == "Automate 1D"){
        monAutomate = new Automate1D(numeroAutomate->value());
        monEtat = new Etat(1,column->value());
        //monEtat->setAllTabValue(0);
        monSimu = new Simulateur(monAutomate,monEtat,buffer->value());
        mafenetre = new fenAutomate1D("1D : "+ nomAutomate->text(),monSimu);
     }
    // Si c'est un Feu de Forêts
    else if(choixAutomate->currentText() == "Feu de forêts"){
        monAutomate = new ForestFire();
        monEtat = new Etat(rows->value(),column->value());
        //monEtat->setAllTabValue(1);
        monSimu = new Simulateur(monAutomate, monEtat, buffer->value());
        mafenetre = new fenAutomate2D("ForestFire : "+ nomAutomate->text(),monSimu);
    }
    else return;
    this->hide(); // On cache la fenêtre de choix
    emit newAuto(mafenetre); // Et on envoie un signal pour créer un nouvel automate
}

// Slot appellé quand l'utilisateur choisit une autre valeur dans la combobox
void Automatemaker::statusChanged(QString a){
            if(a == "Automate 1D"){ // S'il a choisi automate 1D
                // Alors on met à jour les champs utilisables
                //minVoisins->setEnabled(false);
                //maxVoisins->setEnabled(false);
                //exactVoisins->setEnabled(false);
                minVoisinsLabel->setVisible(false);
                minVoisins->setVisible(false);
                maxVoisinsLabel->setVisible(false);
                maxVoisins->setVisible(false);
                exactVoisinsLabel->setVisible(false);
                exactVoisins->setVisible(false);
                //buffer->setEnabled(true);
                //numeroAutomate->setEnabled(true);
                //txtNumeroAutomate->setEnabled(true);
                numeroAutomateLabel->setVisible(true);
                numeroAutomate->setVisible(true);
                txtNumeroAutomateLabel->setVisible(true);
                txtNumeroAutomate->setVisible(true);

                rows->setValue(1);
                rows->setEnabled(false);
                column->setEnabled(true);
            }
            else if (a == "Jeu de la vie"){
                minVoisinsLabel->setVisible(true);
                minVoisins->setVisible(true);
                maxVoisinsLabel->setVisible(true);
                maxVoisins->setVisible(true);
                exactVoisinsLabel->setVisible(true);
                exactVoisins->setVisible(true);
                numeroAutomateLabel->setVisible(false);
                numeroAutomate->setVisible(false);
                txtNumeroAutomateLabel->setVisible(false);
                txtNumeroAutomate->setVisible(false);

                //maxVoisins->setEnabled(true);
                //minVoisins->setEnabled(true);
                //exactVoisins->setEnabled(true);
                //buffer->setEnabled(true);
                //numeroAutomate->setEnabled(false);
                //txtNumeroAutomate->setEnabled(false);

                rows->setValue(10);
                rows->setEnabled(true);
                column->setEnabled(true);
            }
            else if (a == "Feu de forêts"){
                minVoisinsLabel->setVisible(false);
                minVoisins->setVisible(false);
                maxVoisinsLabel->setVisible(false);
                maxVoisins->setVisible(false);
                exactVoisinsLabel->setVisible(false);
                exactVoisins->setVisible(false);
                numeroAutomateLabel->setVisible(false);
                numeroAutomate->setVisible(false);
                txtNumeroAutomateLabel->setVisible(false);
                txtNumeroAutomate->setVisible(false);

                rows->setValue(10);
                rows->setEnabled(true);
                column->setEnabled(true);
                column->setEnabled(true);
            }
}

// Fonction initialise la combobox
void Automatemaker::setAutomateList(){
    choixAutomate->addItem("Automate 1D");
    choixAutomate->addItem("Jeu de la vie");
    choixAutomate->addItem("Feu de forêts");
}
