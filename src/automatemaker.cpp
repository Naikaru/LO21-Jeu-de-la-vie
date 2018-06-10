#include "headers/automatemaker.h"

Automatemaker* Automatemaker::instance = nullptr;

Automatemaker::Automatemaker()
{
    setWindowIcon(QIcon(":/virus.png")); // Mets une icone
    setWindowTitle("Nouvel Automate"); // Nom de la fenêtre
    setMinimumSize(200,100); // Size choisie au pif

    // DEBUT INITIALISATION DES CHAMPS
    monVerticalLayout = new QVBoxLayout();
    monHorizontalLayout = new QHBoxLayout();

    choixAutomate = new QComboBox();
    monTexte = new QLabel("Choix de l'automate:");
    btOK = new QPushButton("Creer");
    btAnnuler = new QPushButton("Annuler");

    monHorizontalLayout->addWidget(btAnnuler);
    monHorizontalLayout->addWidget(btOK);
    monVerticalLayout->addWidget(monTexte);
    monVerticalLayout->addWidget(choixAutomate);
    monVerticalLayout->addLayout(monHorizontalLayout);
    setAutomateList();
    // S'il click sur annuler on cache la fenêtre
    connect(btAnnuler,SIGNAL(clicked()),this,SLOT(close()));
    connect(btOK,SIGNAL(clicked()),this,SLOT(creatAuto()));
    setLayout(monVerticalLayout);
}

// Destructeur du singleton
Automatemaker::~Automatemaker()
{
    if(instance != nullptr) delete instance;
   instance = nullptr;
   delete monTexte;
   delete choixAutomate;
   delete btOK;
   delete btAnnuler;
   delete monVerticalLayout;
   delete monHorizontalLayout;\
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

// Slot appelé quand l'utilisateur appuie sur OK
void Automatemaker::creatAuto(){
    gestionnaireAutomateFactory* maFactory = gestionnaireAutomateFactory::getInstance();
    emit newAuto(maFactory->getAutomateFactory(choixAutomate->currentText().toStdString())->getfenAutomate());
}

// Fonction initialise la combobox
void Automatemaker::setAutomateList(){
    gestionnaireAutomateFactory* maFactory = gestionnaireAutomateFactory::getInstance();
    std::vector<std::string> tableauDeNoms = maFactory->getNameList();
    for(int i(0);i<tableauDeNoms.size();i++)
        choixAutomate->addItem(QString::fromStdString(tableauDeNoms[i]));
}
