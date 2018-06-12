#include "headers/etat.h"

std::string Etat::ERROR_BAD_INDEX = "Index passe en argument incorrect";

Etat::Etat(unsigned short int Rows, unsigned short int Cols):
    nbRows(Rows),nbCols(Cols), grid(Rows, std::vector<int>(Cols, 0))
{
//    unsigned short int i;
//    grid.resize(nbRows);
//    for(i=0; i<nbRows; i++) grid[i].resize(nbCols);
}

int Etat::getCellule(unsigned short int i, unsigned short int j) const{
    if( (i>=nbRows) || (j>= nbCols)) throw EtatException("Etat::getCellule -> " + ERROR_BAD_INDEX);
    return grid[i][j];
}

void Etat::setCellule(unsigned short int i,unsigned short int j, int val){
    if( (i>=nbRows) || (j>= nbCols)) throw EtatException("Etat::setCellule -> " + ERROR_BAD_INDEX);
    grid[i][j] = val;
}

Etat::Etat(const Etat &e):nbRows(e.nbRows),nbCols(e.nbCols), grid(e.nbRows, std::vector<int>(e.nbCols,0))
{
    for(unsigned int i=0;i<e.nbRows;i++)
        for(unsigned int j=0;j<e.nbCols;j++)
            grid[i][j] = e.grid[i][j];
}

Etat& Etat::operator=(const Etat& e){

    nbCols = e.nbCols;
    nbRows = e.nbRows;

    unsigned short int i,j;
    grid.resize(nbRows);
    for(i=0; i<nbRows; i++) grid[i].resize(nbCols);

    for(i=0;i<e.nbRows;i++)
        for(j=0;j<e.nbCols;j++)
            grid[i][j] = e.grid[i][j];

    return *this;
}

void Etat::destroyGrid(){
    int i;
    for(i=0; i<nbRows; i++) grid[i].clear();
    grid.clear();
}

// redim(nbLignes,nbColonnes)
void Etat::redimGrid(unsigned short int i,unsigned short int j){
    if(nbRows < i){ // Si on doit ajouter des lignes
        if(nbCols<j){ // On commence par mettre à jour le nombre de colonnes
            addCols(j-nbCols);
        }else{
            rmCols(nbCols-j);
        }
        addRows(i-nbRows);
    }else{ // Si on doit enlever des lignes
        rmRows(nbRows-i); // On les enlève
        if(nbCols<j){ // et ensuite on mets à jour le nombre de colonnes
            addCols(j-nbCols);
        }else{
            rmCols(nbCols-j);
        }
    }
}

void Etat::addRows(unsigned int i){
    if (i==0) return; // Au cas où, pour eviter les comportement anormaux
    unsigned int k;
    for(k=0;k<i; k++){
        grid.push_back(std::vector<int>(nbCols));
    }
    nbRows = nbRows + i;
}
void Etat::rmRows(unsigned int i){
    if (i==0) return; // Au cas où, pour eviter les comportement anormaux
     grid.erase(grid.begin()+(nbRows-i)-1,grid.begin()+nbRows-1);
     nbRows = nbRows - i;
}
void Etat::addCols(unsigned int i, int value){
    if (i==0) return; // Au cas où, pour eviter les comportement anormaux
    unsigned int k,r;
    for(k=0;k<nbRows;k++){
        for(r=0;r<i;r++) grid[k].push_back(value);
    }
    nbCols = nbCols + i;
}
void Etat::rmCols(unsigned int i){
    if (i==0) return; // Au cas où, pour eviter les comportement anormaux
    unsigned int k;
    for(k=0;k<nbRows;k++){
        grid[k].erase(grid[k].begin()+(nbCols - i)-1,grid[k].begin()+nbCols-1);
    }
    nbCols = nbCols - i;
}

void Etat::setAllTabValue(unsigned int v){
    for(unsigned int i(0); i<nbRows ; ++i){
        for(unsigned int j(0); j<nbCols; ++j)
                setCellule(i,j,v);
    }
}
void Etat::setCols(unsigned int i){
    if(nbCols<i){
        addCols(i-nbCols);
    }else{
        rmCols(nbCols-i);
    }
}
void Etat::setRows(unsigned int i){
    if(nbRows < i){
        addRows(i-nbRows);
    }else{
        rmRows(nbRows-i);
    }
}
