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

// Constructeur de automate2D
Automate2D::Automate2D(unsigned short int min, unsigned short int max, unsigned short int exact)
    :minNeighbours(min),maxNeighbours(max),exactNeighbours(exact){}

// Constructeur par recopie de automate2D
Automate2D::Automate2D(const Automate2D &a):minNeighbours(a.minNeighbours),maxNeighbours(a.maxNeighbours),exactNeighbours(a.exactNeighbours){}

// Operateur d'affectation de Automate2D
Automate2D& Automate2D::operator=(const Automate2D& a){
    minNeighbours = a.minNeighbours;
    maxNeighbours = a.maxNeighbours;
    exactNeighbours = a.exactNeighbours;
    return *this;
}

// Fonction qui compte le nombre de voisins d'une cellule dans une grille 2D
unsigned short int Automate2D::countNeighbours(const Etat& e, unsigned short int row, unsigned short int col)
{
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


    unsigned short int total = 0;

    for(unsigned int i(upRow); i<=(downRow); ++i)
        for(unsigned int j(leftCol); j<=(rightCol); ++j) // vérifier les domaines
                 total += e.getCellule(i,j); // On considère d'abord que grid ne contient que 1 ou 0

    total -= e.getCellule(row, col); // On retire 1 si il a été comme voisin
    return total;
}

// Fonction qui applique la transition de Automate2D
void Automate2D::applyTransition(Etat* depart, Etat* arrivee) const {
    if (depart->getNbRows() != arrivee->getNbRows() || depart->getNbCols() != arrivee->getNbCols())
        *depart = *arrivee;

    for(unsigned int i(0); i<depart->getNbRows(); ++i)
    {
        for(unsigned int j(0); j<depart->getNbCols(); ++j)
        {
            //std::cout << "On s'occupe de la cellule : (" << i << "," << j << ") : ";
            unsigned short int nbNeighbours = countNeighbours(*depart, i, j);
            //std::cout << nbNeighbours << " voisins." << std::endl;
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

// Retourne un pointeur sur automate d'un automate2D
Automate* Automate2D::copy() const{
    Automate* temp = new Automate2D(*this);
    return temp;
}

// Retourne un pointeur sur automate d'un automate1D
Automate* Automate1D::copy() const{
    Automate* temp = new Automate1D(*this);
    return temp;
}

