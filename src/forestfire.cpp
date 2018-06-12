#include "headers/forestfire.h"

// Constructeur de GameOfLife
ForestFire::ForestFire(Neighbourhood n): typeN(n) {}


// Constructeur par recopie de ForestFire
ForestFire::ForestFire(const ForestFire &a): typeN(a.typeN) {}

// Operateur d'affectation de ForestFire
ForestFire& ForestFire::operator=(const ForestFire& a){
    typeN = a.typeN;
    return *this;
}


// Transtion : ici on tient directement compte du voisinage (<> GameOfLife où on délègue à uen fonction countNeighbours() )
void ForestFire::applyTransition(const Etat& depart, Etat& arrivee) const
{
    unsigned int nbRows = depart.getNbRows();
    unsigned int nbCols = depart.getNbCols();

    //if (nbRows != arrivee.getNbRows() || nbCols != arrivee.getNbCols())
    arrivee = depart;

    for(unsigned int i(0); i<nbRows; ++i)
    {
        for(unsigned int j(0); j<nbCols; ++j)
        {
            if(depart.getCellule(i,j) == fire){
                if((i>=1) && (depart.getCellule(i-1,j) == tree))
                    arrivee.setCellule(i-1,j,2);

                if((i+1<nbRows) && (depart.getCellule(i+1,j) == tree))
                    arrivee.setCellule(i+1,j,2);

                if((j>=1) && (depart.getCellule(i,j-1) == tree))
                    arrivee.setCellule(i,j-1,2);

                if((j+1<nbCols) && (depart.getCellule(i,j+1) == tree))
                    arrivee.setCellule(i,j+1,2);

                if(typeN >= 1){ // Alors voisinage de Moore
                    // On se contente de checker les 4 cases suivantes correspondant aux coins

                    // superior left cell
                    if((i>=1) && (j>=1) && (depart.getCellule(i-1,j-1) == tree))
                        arrivee.setCellule(i-1,j-1,2);
                    // superior right cell
                    if((i>=1) && (j+1<nbCols) && (depart.getCellule(i-1,j+1) == tree))
                        arrivee.setCellule(i-1,j+1,2);
                    // inferior left cell
                    if((i+1<nbRows) && (j>=1) && (depart.getCellule(i+1,j-1) == tree))
                        arrivee.setCellule(i+1,j-1,2);
                    // inferior right cell
                    if((i+1<nbRows) && (j+1<nbCols) && (depart.getCellule(i+1,j+1) == tree))
                        arrivee.setCellule(i+1,j+1,2);
                }
                // From fire you become ashes
                arrivee.setCellule(i,j,3);
            }
        }
    }
}


void ForestFire::changeStatus(unsigned int r, unsigned int c, Etat *e) const
{
    unsigned int st = e->getCellule(r,c);
    if(st == empty)
        e->setCellule(r,c,tree);
    else if(st == tree)
        e->setCellule(r,c,fire);
    else if(st == fire)
        e->setCellule(r,c,ashes);
    else if(st == ashes)
        e->setCellule(r,c,empty);
}


// Retourne un pointeur sur Automate (polymoprhisme)
Automate* ForestFire::copy() const{
    Automate* temp = new ForestFire(*this);
    return temp;
}


const QColor& ForestFire::colorize(int value) const
{
    switch(value){
        case(0): return *(new QColor("White")); break;
        case(1): return *(new QColor("Green")); break;
        case(2): return *(new QColor("Red")); break;
        case(3): return *(new QColor("Grey")); break;
    default: return *(new QColor("Black")); break;
    }

}


void ForestFire::changeRules(){
    newRules = new QWidget();

    newRules->setWindowTitle("Règles de transitions"); // Nom de la fenêtre
    newRules->setMinimumSize(200,50); // Size choisie au pif

    // DEBUT INITIALISATION DES CHAMPS
    QFormLayout* monVerticalLayout = new QFormLayout();
    QHBoxLayout* monHorizontalLayout = new QHBoxLayout();

    voisinage = new QComboBox(newRules);
    voisinage->addItem("Moore");
    voisinage->addItem("Von Neumann");
    monVerticalLayout->addRow("Type de voisinage :", voisinage);

    QPushButton* btOK = new QPushButton("Changer", newRules);
    connect(btOK,SIGNAL(clicked()),this,SLOT(slotUpdateRules()));

    QPushButton* btAnnuler = new QPushButton("Annuler", newRules);
    connect(btAnnuler,SIGNAL(clicked()),newRules,SLOT(close()));

    monHorizontalLayout->addWidget(btOK);
    monHorizontalLayout->addWidget(btAnnuler);

    monVerticalLayout->addRow(monHorizontalLayout);

    newRules->setLayout(monVerticalLayout);
    newRules->show();
}


 // Redéfinition des règles de transition
void ForestFire::slotUpdateRules(){
    if(voisinage->currentText().toStdString() == "Von Neumann")
        typeN = VonNeumann;
    else if(voisinage->currentText().toStdString() == "Moore")
        typeN = Moore;
    QMessageBox::information(newRules, "Transition Rules Modifications", "Les règles de transitions ont bien été modifiées (<strong>FAUX</strong>)");
    // emit reinitialize(); ?
}



fenAutomate* ForestFireFactory::getfenAutomate(){
    Automate* monAutomate = new ForestFire();
    Etat* monEtat = new Etat();
    Simulateur* monSimu = new Simulateur(monAutomate, monEtat);
    fenAutomate* mafenetre = new fenAutomate2D("ForestFire : Nouvel Automate",monSimu);
    return mafenetre;
}
