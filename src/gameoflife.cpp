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
