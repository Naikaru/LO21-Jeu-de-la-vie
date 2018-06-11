#include "headers/gameoflife.h"

// Constructeur de GameOfLife
GameOfLife::GameOfLife(unsigned short int min, unsigned short int max, unsigned short int exact, Neighbourhood n)
    :minNeighbours(min),maxNeighbours(max),exactNeighbours(exact), typeN(n) {}

// Constructeur par recopie de GameOfLife
GameOfLife::GameOfLife(const GameOfLife &a):minNeighbours(a.minNeighbours),maxNeighbours(a.maxNeighbours),exactNeighbours(a.exactNeighbours){}

// Operateur d'affectation de GameOfLife
GameOfLife& GameOfLife::operator=(const GameOfLife& a){
    minNeighbours = a.minNeighbours;
    maxNeighbours = a.maxNeighbours;
    exactNeighbours = a.exactNeighbours;
    typeN = a.typeN;
    return *this;
}

// Fonction qui compte le nombre de voisins d'une cellule dans une grille 2D
unsigned short int GameOfLife::countNeighbours(const Etat& e, unsigned short int row, unsigned short int col) const
{
    unsigned short int total = 0;
    if(row-1 >= 0)              // superior cell
        total += e.getCellule(row-1,col);
    if(row+1 < e.getNbRows())   // inferior cell
        total += e.getCellule(row+1,col);
    if(col-1 >= 0)              // left cell
        total += e.getCellule(row,col-1);
    if(col+1 < e.getNbCols())   // right cell
        total += e.getCellule(row,col+1);

    if(typeN == Moore){ // Alors voisinage de Moore
        // On se contente de checker les 4 cases suivantes correspondant aux coins

        if(row-1>=0 && col-1>=0)                // superior left cell
            total += e.getCellule(row-1,col-1);
        if(row-1>=0 && col+1 < e.getNbCols())   // superior right cell
            total += e.getCellule(row-1,col+1);
        if(row+1<e.getNbRows() && col-1>=0)     // inferior left cell
            total += e.getCellule(row+1,col-1);
        if(row+1<e.getNbRows() && col+1<e.getNbCols()) // inferior right cell
            total += e.getCellule(row+1,col+1);
    }

    // Plus un voisinage est important, plus on va chercher les voisins loins
    // Facile d'ajouter le voisinage de Moore d'ordre 2 (les 24 voisins)
    // Il suffit de rajouter if(typeN >=2)

    // Mais la solution avec la boucle pour compter est plus badass

/*
        // Détermination des cas limites.
        unsigned short int upRow;
        unsigned short int downRow;
        unsigned short int leftCol;
        unsigned short int rightCol;

        if(row==0)
            upRow = row;
        else
            upRow = row-1;

        if(row==e.getNbRows()-1)
            downRow = row;
        else
            downRow = row+1;

        if(col==0)
            leftCol = col;
        else
            leftCol = col-1;

        if(col==e.getNbCols()-1)
            rightCol = col;
        else
            rightCol = col+1;

        for(unsigned int i(upRow); i<=(downRow); ++i)
            for(unsigned int j(leftCol); j<=(rightCol); ++j) // vérifier les domaines
                     total += e.getCellule(i,j); // On considère d'abord que grid ne contient que 1 ou 0

        total -= e.getCellule(row, col); // On retire 1 si il a été comme voisin
*/
    return total;
}


// Fonction qui applique la transition de GameOfLife
void GameOfLife::applyTransition(const Etat& depart, Etat& arrivee) const {
    if (depart.getNbRows() != arrivee.getNbRows() || depart.getNbCols() != arrivee.getNbCols())
        arrivee = depart;

    for(unsigned int i(0); i<depart.getNbRows(); ++i){
        for(unsigned int j(0); j<depart.getNbCols(); ++j){
            unsigned short int nbNeighbours = countNeighbours(depart, i, j);
            if(depart.getCellule(i,j)==1){
                if(nbNeighbours < minNeighbours || nbNeighbours > maxNeighbours)
                    arrivee.setCellule(i,j,0);
                else
                    arrivee.setCellule(i,j,1);
            }
            else{
                if(nbNeighbours == exactNeighbours){
                    arrivee.setCellule(i,j,1);
                }
            }
        }
    }
}


void GameOfLife::changeStatus(unsigned int r, unsigned int c, Etat *e) const
{
    if(e->getCellule(r,c) == 0)
        e->setCellule(r,c,1);
    else
        e->setCellule(r,c,0);
}


// Retourne un pointeur sur automate d'un GameOfLife
Automate* GameOfLife::copy() const{
    Automate* temp = new GameOfLife(*this);
    return temp;
}


const QColor& GameOfLife::colorize(int value)const {
    if (value == 0) return *(new QColor("White"));
    else return *(new QColor("Black"));
}

QWidget* GameOfLife::changeRules() const {
    QWidget* newRules = new QWidget();

    newRules->setWindowTitle("Règles de transitions"); // Nom de la fenêtre
    newRules->setMinimumSize(200,100); // Size choisie au pif

    // DEBUT INITIALISATION DES CHAMPS
    QFormLayout* monVerticalLayout = new QFormLayout();
    QHBoxLayout* monHorizontalLayout = new QHBoxLayout();

    // Nombre de voisins minimum pour la survie d'une cellule :
    QSpinBox* minVoisins = new QSpinBox(newRules);
    minVoisins->setValue(2);
    minVoisins->setMinimum(0);
    minVoisins->setMaximum(3); // Car maxVoisins par défaut sur 3
    minVoisins->size().setWidth(25);
    minVoisins->setAlignment(Qt::AlignCenter);
    //connect(minVoisins, SIGNAL(valueChanged(int)), newRules, SLOT(slotMinChanged()));

    // Nombre de voisins minimum pour la survie d'une cellule :
    QSpinBox* maxVoisins = new QSpinBox(newRules);
    maxVoisins->setValue(3);
    maxVoisins->setMinimum(2); // Car minVoisins par défaut sur 2
    maxVoisins->setMaximum(8);
    maxVoisins->size().setWidth(25);
    maxVoisins->setAlignment(Qt::AlignCenter);
    //connect(minVoisins, SIGNAL(valueChanged(int)), newRules, SLOT(slotMaxChanged()));

    // Nombre de voisins pour la naissance spontannée d'une cellule
    QSpinBox* exactVoisins = new QSpinBox(newRules);
    exactVoisins->setValue(3);
    exactVoisins->setRange(0,8);
    exactVoisins->size().setWidth(25);
    exactVoisins->setAlignment(Qt::AlignCenter);

    QComboBox* voisinage = new QComboBox(newRules);
    voisinage->addItem("Moore", QVariant());
    voisinage->addItem("Von Neumann");
    //connect(voisinage,SIGNAL(currentTextChanged(QString)),newRules,SLOT(slotChoixVoisinage()));

    QPushButton* btOK = new QPushButton("Changer", newRules);
    QPushButton* btAnnuler = new QPushButton("Annuler", newRules);
    //S'il click sur annuler on cache la fenêtre
    //connect(btOK,SIGNAL(clicked()),newRules,SLOT(makeRulesChange()));
    //connect(btAnnuler,SIGNAL(clicked()),newRules,SLOT(close()));

    monHorizontalLayout->addWidget(btOK);
    monHorizontalLayout->addWidget(btAnnuler);

    monVerticalLayout->addRow("Nombre de voisins minimum : ", minVoisins);
    monVerticalLayout->addRow("Nombre de voisins maximum : ", maxVoisins);
    monVerticalLayout->addRow("Nombre exact de voisins : ", exactVoisins);
    monVerticalLayout->addRow("Type de voisinage :", voisinage);
    monVerticalLayout->addRow(monHorizontalLayout);

    newRules->setLayout(monVerticalLayout);

    return newRules;
}


//void GameOfLife::makeRulesChange(){
//    /*
//    minNeighbours = minVoisins->value();
//    maxNeighbours = maxVoisins->value();
//    exactNeighbours = exactVoisins->value();
//    typeN = voisinage->currentIndex();
//    */
//}

// // Mise à jour des contraintes sur maxVoisins
//void GameOfLife::slotMinChanged(int value){
//    //maxVoisins->setMinimum(value);
//}

//void GameOfLife::slotMaxChanged(int value){
//    //minVoisins->setMaximum(value);
//}


fenAutomate* GameOfLifeFactory::getfenAutomate(){
    Automate* monAutomate = new GameOfLife();
    Etat* monEtat = new Etat();
    Simulateur* monSimu = new Simulateur(monAutomate,monEtat);
    fenAutomate* mafenetre = new fenAutomate2D("GameOfLife : Nouvel Automate",monSimu);
    return mafenetre;
}

