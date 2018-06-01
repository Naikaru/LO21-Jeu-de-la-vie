#include "automate.h"

Etat2D::Etat2D(unsigned short int m, unsigned short int n):
	nbCols(m),
	nbRows(n),
    grid(n, std::vector<int>(m,0))
{}


void Etat2D::setCellule(unsigned short int i, unsigned short int j, unsigned int val) {
	if (i >= nbRows || j >= nbCols) throw AutomateException("Erreur Cellule");
	grid[i][j] = val;
}

unsigned short int Etat2D::getCellule(unsigned short int i, unsigned short int j) const {
	if (i >= nbRows || j >= nbCols) throw AutomateException("Erreur Cellule");
	return grid[i][j];
}

Etat2D::Etat2D(const Etat2D& e):
	nbRows(e.nbRows),
	nbCols(e.nbCols),
    grid(e.nbRows, std::vector<int>(e.nbCols, 0))
{
    for (unsigned int i=0; i<nbRows; ++i)
		for(unsigned int j=0; j<nbCols; ++j)
			grid[i][j] = e.grid[i][j];
}


// operator= : grosse optimisation à faire dessus !
// Ajout / Suppr de ligne ou de colonnes

Etat2D& Etat2D::operator=(const Etat2D& e) {
	if (this != &e) {
        if (nbRows != e.nbRows || nbCols != e.nbCols)
        {
            std::vector< std::vector<int> > newGrid(e.nbRows, std::vector<int>(e.nbCols, 0));
            for (unsigned int i = 0; i < e.nbRows; ++i)
                for (unsigned int j = 0; j < e.nbCols; ++j)
                    newGrid[i][j] = e.grid[i][j];

            //std::vector< std::vector<int> > oldGrid = grid;
            grid = newGrid;
            nbRows = e.nbRows;
            nbCols = e.nbCols;
            // delete oldGrid ? Pas besoin c'est un vecteur ?
        }else
            for (unsigned int i = 0; i < e.nbRows; ++i)
                for (unsigned int j = 0; j < e.nbCols; ++j)
                    grid[i][j] = e.grid[i][j];
	}
	return *this;
}


unsigned short int countNeighbours(const Etat2D& e, unsigned short int row, unsigned short int col)
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


Automate2D::Automate2D(unsigned short int min, unsigned short int max, unsigned short int exact):
	minNeighbours(min),
	maxNeighbours(max),
	exactNeighbours(exact)
{}


void Automate2D::applyTransition(const Etat2D& dep, Etat2D& dest) const
{
    if (dep.getNbRows() != dest.getNbRows() || dep.getNbCols() != dest.getNbCols())
        dest = dep;

    for(unsigned int i(0); i<dep.getNbRows(); ++i)
	{
        for(unsigned int j(0); j<dep.getNbCols(); ++j)
		{
            //std::cout << "On s'occupe de la cellule : (" << i << "," << j << ") : ";
			unsigned short int nbNeighbours = countNeighbours(dep, i, j); 
            //std::cout << nbNeighbours << " voisins." << std::endl;
            if(dep.getCellule(i,j)==1 && (nbNeighbours < minNeighbours || nbNeighbours > maxNeighbours))
                dest.setCellule(i,j,0);
			else
			{
				if(nbNeighbours == exactNeighbours)
                    dest.setCellule(i,j,1);
			}
		}
	}
}





Simulateur2D::Simulateur2D(const Automate2D& a, unsigned int buffer):
    automate(a), 
    etats(nullptr), 
    depart(nullptr), 
    nbMaxEtats(buffer),
    rang(0) 
{
	etats = new Etat2D*[nbMaxEtats];
	for (unsigned int i = 0; i < nbMaxEtats; i++) 
		etats[i] = nullptr;
}


Simulateur2D::Simulateur2D(const Automate2D& a, const Etat2D& dep, unsigned int buffer):
    automate(a), 
    etats(nullptr), 
    depart(&dep), 
    nbMaxEtats(buffer),
    rang(0) 
{
    etats = new Etat2D*[nbMaxEtats];
    for (unsigned int i = 0; i < nbMaxEtats; i++)
        etats[i] = nullptr;
    etats[0] = new Etat2D(dep);
}


void Simulateur2D::build(unsigned int cellule) { 
	if (cellule >= nbMaxEtats) throw AutomateException("erreur taille buffer"); 
    if (etats[cellule] == nullptr) etats[cellule] = new Etat2D;
}



void Simulateur2D::setEtatDepart(const Etat2D& e) {
	depart = &e;
	reset();
}

void Simulateur2D::reset() {
	if (depart==nullptr) throw AutomateException("etat depart indefini");
	build(0); 
	*etats[0] = *depart;
	rang = 0;
}


void Simulateur2D::next() {
	if (depart == nullptr) throw AutomateException("etat depart indefini");
	rang++;
	build(rang%nbMaxEtats);
	automate.applyTransition(*etats[(rang - 1) % nbMaxEtats], *etats[rang%nbMaxEtats]);
}

void Simulateur2D::run(unsigned int nb_steps) {
	for (unsigned int i = 0; i < nb_steps; i++) 
		next();
}

const Etat2D& Simulateur2D::dernier() const {
	return *etats[rang%nbMaxEtats];
}

Simulateur2D::~Simulateur2D() {
	for (unsigned int i = 0; i < nbMaxEtats; i++) delete etats[i];
	delete[] etats;
}
