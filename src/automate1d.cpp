#include "headers/automate1d.h"

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
void Automate1D::applyTransition(const Etat& depart, Etat& arrivee) const {
    if(depart.getNbRows() != 1) throw AutomateException("Automate1D::applyTransition ->" + ERROR_BAD_ETAT);
    if(arrivee.getNbRows() != 1) throw AutomateException("Automate1D::applyTransition ->" + ERROR_BAD_ETAT);

    if (depart.getNbCols() != arrivee.getNbCols()) arrivee.setCols(depart.getNbCols());

    for (unsigned int i = 0; i < depart.getNbCols(); i++)
    {
        unsigned short int conf(0);
        if (i > 0) conf += depart.getCellule(0, i - 1) * 4;
            conf += depart.getCellule(0, i) * 2;
        if (i < depart.getNbCols()-1) conf += depart.getCellule(0,i + 1);

        arrivee.setCellule(0, i, numeroBit[7-conf]-'0');
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

void Automate1D::changeStatus(unsigned int r, unsigned int c, Etat *e) const
{
    if(e->getCellule(r,c) == 0)
        e->setCellule(r,c,1);
    else
        e->setCellule(r,c,0);
}


// Retourne un pointeur sur automate d'un automate1D
Automate* Automate1D::copy() const{
    Automate* temp = new Automate1D(*this);
    return temp;
}


const QColor& Automate1D::colorize(int value)const{
    if (value == 0) return *(new QColor("White"));
    else return *(new QColor("Black"));
}

fenAutomate* Automate1DFactory::getfenAutomate(){
    Automate* monAutomate = new Automate1D(); // valeurs du constructeur par défaut
    Etat* monEtat = new Etat(1); // 6 Colonnes par défaut
    //monEtat->setAllTabValue(0);
    Simulateur* monSimu = new Simulateur(monAutomate,monEtat); // 4 etats dans le buffer par defaut
    fenAutomate* mafenetre = new fenAutomate1D("1D : Nouvel Automate",monSimu);
    return mafenetre;
}
