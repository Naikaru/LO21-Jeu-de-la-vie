#include "automate.h"


// Classe mère : Etat


// Classe fille : Etat1D

Etat1D::Etat1D(unsigned short int n): 
    nbCols(n),
     // On ajoute une ligne de n colonnes initialisée à 0
    grid(1,std::vector<int>(n, 0))
{
    //grid.push_back(std::vector<int>(n, 0));
}

void Etat1D::setCellule(unsigned short int i, unsigned int val) {
	if (i >= nbCols) throw AutomateException("Erreur Cellule");
	grid[0][i] = val;
}

int Etat1D::getCellule(unsigned short int i) const {
	if (i >= nbCols) throw AutomateException("Erreur Cellule");
	return grid[0][i];
}

Etat1D::Etat1D(const Etat1D& e):
	nbCols(e.nbCols),
    grid(1, std::vector<int>(e.nbCols, 0))
{
    for (unsigned int i=0; i<nbCols; ++i)
		grid[0][i] = e.grid[0][i];
}


Etat1D& Etat1D::operator=(const Etat1D& e) {
	if (this != &e) {
        if (nbCols != e.nbCols) {
            std::vector< std::vector<int> > newGrid(1, std::vector<int>(e.nbCols, 0));
            for (unsigned int i = 0; i < e.nbCols; i++)
				newGrid[0][i] = e.grid[0][i];
            std::vector< std::vector<int> > oldGrid = grid;
			grid = newGrid;
			nbCols = e.nbCols;
            //delete[] oldGrid;
		}else 
            for (unsigned int i = 0; i < e.nbCols; i++)
				grid[0][i] = e.grid[0][i];
	}
	return *this;
}

/*************************************************************/

// Classe mère MainAutomate


//MainAutomate::MainAutomate(){}

// Transition string -> int 

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

// Transition int -> string 

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

Automate1D::Automate1D(unsigned short int num) : 
	numero(num),
	numeroBit(NumToNumBit(num))
{}

Automate1D::Automate1D(const std::string& num) : 
	numero(NumBitToNum(num)),
	numeroBit(num) 
{}


void Automate1D::applyTransition(const Etat1D& dep, Etat1D& dest) const {
    if (dep.getNbCols() != dest.getNbCols())
		dest = dep;
	for (unsigned int i = 0; i < dep.getNbCols(); ++i) 
	{
		unsigned short int conf(0);
		if (i > 0) 
			conf += dep.getCellule(i - 1) * 4;
		conf+=dep.getCellule(i)*2;
		if (i < dep.getNbCols()-1) 
			conf += dep.getCellule(i + 1); 
		dest.setCellule(i, numeroBit[7-conf]-'0');
	}
}



Simulateur1D::Simulateur1D(const Automate1D& a, unsigned int buffer):
    automate(a), etats(nullptr), depart(nullptr), nbMaxEtats(buffer),rang(0) 
{
	etats = new Etat1D*[nbMaxEtats];
	for (unsigned int i = 0; i < nbMaxEtats; i++) 
		etats[i] = nullptr;
}

Simulateur1D::Simulateur1D(const Automate1D& a, const Etat1D& dep, unsigned int buffer):
    automate(a), etats(nullptr), depart(&dep), nbMaxEtats(buffer),rang(0) {
    etats = new Etat1D*[nbMaxEtats];
	for (unsigned int i = 0; i < nbMaxEtats; i++) etats[i] = nullptr;
    etats[0] = new Etat1D(dep);
}

void Simulateur1D::build(unsigned int cellule) { 
	if (cellule >= nbMaxEtats) throw AutomateException("erreur taille buffer"); 
    if (etats[cellule] == nullptr) etats[cellule] = new Etat1D;
}

void Simulateur1D::setEtatDepart(const Etat1D& e) {
	depart = &e;
	reset();
}

void Simulateur1D::reset() {
	if (depart==nullptr) throw AutomateException("etat depart indefini");
	build(0); 
	*etats[0] = *depart;
	rang = 0;
}

void Simulateur1D::next() {
	if (depart == nullptr) throw AutomateException("etat depart indefini");
	rang++;
	build(rang%nbMaxEtats);
	automate.applyTransition(*etats[(rang - 1) % nbMaxEtats], *etats[rang%nbMaxEtats]);
}

void Simulateur1D::run(unsigned int nb_steps) {
	for (unsigned int i = 0; i < nb_steps; i++) 
		next();
}

const Etat1D& Simulateur1D::dernier() const {
	return *etats[rang%nbMaxEtats];
}

Simulateur1D::~Simulateur1D() {
	for (unsigned int i = 0; i < nbMaxEtats; i++) delete etats[i];
	delete[] etats;
}
