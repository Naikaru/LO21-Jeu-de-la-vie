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
    column = new QSpinBox;
    maxVoisins = new QSpinBox;
    minVoisins = new QSpinBox;
    exactVoisins = new QSpinBox;
    numeroAutomate = new QSpinBox;
    txtNumeroAutomate = new QLineEdit;
    buffer = new QSpinBox;
    // FIN INITIALISATION

    rows->setMinimum(0); column->setMinimum(0); // On mets le minimum à 0

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
    myFormLayout->addRow("Automate N° (chiffres) :",numeroAutomate);
    myFormLayout->addRow("Automate N° (lettres):",txtNumeroAutomate);
    myFormLayout->addRow("min Voisins :",minVoisins);
    myFormLayout->addRow("max Voisins :",maxVoisins);
    myFormLayout->addRow("exact Voisins :",exactVoisins);
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



// Slot appellé quand l'utilisateur appuie sur OK
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
       monAutomate = new Automate2D(minVoisins->value(),maxVoisins->value(),exactVoisins->value());
       monEtat = new Etat(rows->value(),column->value());
       monSimu = new Simulateur(monAutomate,monEtat,buffer->value());
       mafenetre = new fenAutomate2D("2D : "+ nomAutomate->text(),monSimu);
      }
    // Si c'est un automate 1D
    else if(choixAutomate->currentText() == "Automate 1D"){
        monAutomate = new Automate1D(numeroAutomate->value());
        monEtat = new Etat(1,column->value());
        monEtat->setAllTabValue(0);
        monSimu = new Simulateur(monAutomate,monEtat,buffer->value());
        mafenetre = new fenAutomate1D("1D : "+ nomAutomate->text(),monSimu);
     }
    else return;
    this->hide(); // On cache la fenêtre de choix
    emit newAuto(mafenetre); // Et on envoie un signal pour créer un nouvel automate
}

// Slot appellé quand l'utilisateur choisit une autre valeur dans la combobox
void Automatemaker::statusChanged(QString a){
            if(a == "Automate 1D"){ // S'il a choisi automate 1D
                // Alors on met à jour les champs utilisables
                maxVoisins->setEnabled(false);
                minVoisins->setEnabled(false);
                buffer->setEnabled(true);
                exactVoisins->setEnabled(false);
                numeroAutomate->setEnabled(true);
                txtNumeroAutomate->setEnabled(true);
                rows->setEnabled(false);
                column->setEnabled(true);
            }else if (a == "Jeu de la vie"){
                maxVoisins->setEnabled(true);
                buffer->setEnabled(true);
                minVoisins->setEnabled(true);
                exactVoisins->setEnabled(true);
                numeroAutomate->setEnabled(false);
                txtNumeroAutomate->setEnabled(false);
                rows->setEnabled(true);
                column->setEnabled(true);
            }
}

// Fonction initialise la combobox
void Automatemaker::setAutomateList(){
    choixAutomate->addItem("Jeu de la vie");
    choixAutomate->addItem("Automate 1D");
}
