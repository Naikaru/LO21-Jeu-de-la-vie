#include "automate.h"

std::string Automate1D::ERROR_BAD_ETAT = "L'Etat n'est pas un etat 1D";

// Transforme les string de 0 et de 1 en int
short unsigned int NumBitToNum(const std::string& num) {
    if (num.size() != 8) throw AutomateException("Numero d'automate indefini");
    int puissance = 1;
    short unsigned int numero = 0;
    for (int i = 7; i >= 0; i--) {
        if (num[i] == '1') numero += puissance;
        else if (num[i] != '0') throw AutomateException("Numero d'automate indefini");
        puissance *= 2;
    }
    return numero;
}

// Transforme les int en string de 0 et 1
std::string NumToNumBit(short unsigned int num) {
    std::string numeroBit;
    if (num > 256) throw AutomateException("Numero d'automate indefini");
    unsigned short int p = 128;
    int i = 7;
    while (i >= 0) {
        if (num >= p) {
            numeroBit.push_back('1');
            num -= p;
        }
        else { numeroBit.push_back('0'); }
        i--;
        p = p / 2;
    }
    return numeroBit;
}

// Constructeur de Automate 1D par int
Automate1D::Automate1D(unsigned short int num) :
    numero(num),
    numeroBit(NumToNumBit(num))
{}

// Constructeur de Automate 1D par string
Automate1D::Automate1D(const std::string& num) :
    numero(NumBitToNum(num)),
    numeroBit(num)
{}

// Fonction d'application de la transition de Automate1D
void Automate1D::applyTransition(Etat* depart, Etat* arrivee) const {
    if(depart->getNbRows() != 1) throw AutomateException("Automate1D::applyTransition ->" + ERROR_BAD_ETAT);
    if(arrivee->getNbRows() != 1) throw AutomateException("Automate1D::applyTransition ->" + ERROR_BAD_ETAT);

    if (depart->getNbCols() != arrivee->getNbCols()) arrivee->setCols(depart->getNbCols());

    for (unsigned int i = 0; i < depart->getNbCols(); i++)
    {
        unsigned short int conf(0);
        if (i > 0) conf += depart->getCellule(0, i - 1) * 4;
            conf += depart->getCellule(0, i) * 2;
        if (i < depart->getNbCols()-1) conf += depart->getCellule(0,i + 1);

        arrivee->setCellule(0, i, numeroBit[7-conf]-'0');
    }
}

// Constructeur de recopie de automate1D
Automate1D::Automate1D(const Automate1D& a) : numero(a.numero),numeroBit(a.numeroBit)
{}

// Opérateur d'affectation de automate1D
Automate1D& Automate1D::operator=(const Automate1D& a){
    numero = a.numero;
    numeroBit = a.numeroBit;
    return *this;
}


// Retourne un pointeur sur automate d'un automate1D
Automate* Automate1D::copy() const{
    Automate* temp = new Automate1D(*this);
    return temp;
}


const QColor& Automate1D::colourize(int value)const{
    if (value == 0) return *(new QColor("White"));
    else return *(new QColor("Black"));
}



/**********************************************
 ************       MODE 2D     ***************
 **********************************************/



/*********************************************
**************  Jeu de la vie  ***************
**********************************************/


// Constructeur de GameOfLife
GameOfLife::GameOfLife(unsigned short int min, unsigned short int max, unsigned short int exact)
    :minNeighbours(min),maxNeighbours(max),exactNeighbours(exact){}

// Constructeur par recopie de GameOfLife
GameOfLife::GameOfLife(const GameOfLife &a):minNeighbours(a.minNeighbours),maxNeighbours(a.maxNeighbours),exactNeighbours(a.exactNeighbours){}

// Operateur d'affectation de GameOfLife
GameOfLife& GameOfLife::operator=(const GameOfLife& a){
    minNeighbours = a.minNeighbours;
    maxNeighbours = a.maxNeighbours;
    exactNeighbours = a.exactNeighbours;
    return *this;
}

// Fonction qui compte le nombre de voisins d'une cellule dans une grille 2D
unsigned short int GameOfLife::countNeighbours(const Etat& e, unsigned short int row, unsigned short int col)
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

    if(typeN >= 1){ // Alors voisinage de Moore
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
void GameOfLife::applyTransition(Etat* depart, Etat* arrivee) const {
    if (depart->getNbRows() != arrivee->getNbRows() || depart->getNbCols() != arrivee->getNbCols())
        *depart = *arrivee;

    for(unsigned int i(0); i<depart->getNbRows(); ++i){
        for(unsigned int j(0); j<depart->getNbCols(); ++j){
            unsigned short int nbNeighbours = countNeighbours(*depart, i, j);
            if(depart->getCellule(i,j)==1 && (nbNeighbours < minNeighbours || nbNeighbours > maxNeighbours))
                arrivee->setCellule(i,j,0);
            else
            {
                if(nbNeighbours == exactNeighbours)
                    arrivee->setCellule(i,j,1);
            }
        }
    }
}

// Retourne un pointeur sur automate d'un GameOfLife
Automate* GameOfLife::copy() const{
    Automate* temp = new GameOfLife(*this);
    return temp;
}


 const QColor& GameOfLife::colourize(int value)const {
    if (value == 0) return *(new QColor("White"));
    else return *(new QColor("Black"));
}



/**********************************************
**************   Feu de Forêt   ***************
***********************************************/

// Constructeur de GameOfLife
ForestFire::ForestFire(Neighbourhood n): typeN(n) {}


// Constructeur par recopie de ForestFire
ForestFire::ForestFire(const ForestFire &a):typeN(a.typeN) {}

// Operateur d'affectation de ForestFire
ForestFire& ForestFire::operator=(const ForestFire& a){
    typeN = a.typeN;
    return *this;
}


// Transtion : ici on tient directement compte du voisinage (<> GameOfLife où on délègue à uen fonction countNeighbours() )
void ForestFire::applyTransition(const Etat2D& dep, Etat2D& dest) const
{
    if (dep.getNbRows() != dest.getNbRows() || dep.getNbCols() != dest.getNbCols())
        dest = dep;

    for(unsigned int i(0); i<dep.getNbRows(); ++i)
    {
        for(unsigned int j(0); j<dep.getNbCols(); ++j)
        {
            if(dep.getCellule(i,j) == fire){ 
                if(i-1 >= 0 && dep.getCellule(i-1,j) == tree) 
                    dest.set(i-1,j,2);
                if(i+1 < dep.getNbRows() && dep.getCellule(i+1,j) == tree)
                    dest.set(i+1,j,2);
                if(j-1 >= 0 && dep.getCellule(i,j-1) == tree)
                    dest.set(i,j-1,2);
                if(j+1 < dep.getNbCols() && dep.getCellule(i,j+1) == tree)
                    dest.set(i,j+1,2);
                
                if(typeN >= 1){ // Alors voisinage de Moore
                    // On se contente de checker les 4 cases suivantes correspondant aux coins

                    // superior left cell
                    if(i-1>=0 && j-1>=0 && dep.getCellule(i-1,j-1) == tree)    
                        dest.set(i-1,j-1,2);
                    // inferior left cell
                    if(i-1>=0 && j+1<e.getNbCols() && dep.getCellule(i-1,j+1,) == tree)   
                        dest.set(i-1,j-1,2);
                    // superior left cell
                    if(i+1<e.getNbRows() && j-1>=0 && dep.getCellule(i+1,j-1,) == tree)     
                        dest.set(i-1,j-1,2);
                    // superior left cell
                    if(i+1<e.getNbRows() && j+1<e.getNbCols() && dep.getCellule(i+1,j+1,) == tree) 
                        dest.set(i-1,j-1,2);               
                }

                // From fire you become ashes
                dest.setCellule(i,j,3);
            }
        }
    }
}


