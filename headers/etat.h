#ifndef ETAT_H
#define ETAT_H
#include <QWidget>
#include <string>
#include <vector>
#include <iostream>

//   TODO  //
//
// 1/ Verifier les desctructeurs, j'ai ptet fait de la merde
//
//   FIN TODO  //

// Classe qui correspond aux exceptions pour les Etats (enfin il n'y en a qu'un là)
class EtatException {
    private:
        std::string info;

    public:
        EtatException(const std::string& message) : info(message) {}
        std::string getInfo() const { return info; }
};

// Classe qui correspond à un état d'un automate
class Etat
{

    static std::string ERROR_BAD_INDEX; // juste un code erreur

    std::vector<std::vector<int>> grid;
    // grid[Rows][Cols]
    unsigned short int nbRows;
    unsigned short int nbCols;

public:
    Etat( unsigned short int Rows=1,unsigned short int Cols=10);
    Etat(const Etat& e);
    Etat& operator=(const Etat& e);

    ~Etat() = default;

    unsigned short int getNbRows() const { return nbRows; }
    unsigned short int getNbCols() const { return nbCols; }

    // Mets la valeur val dans la case (i,j)
    void setCellule(unsigned short int i,unsigned short int j,int val);

    //renvoie la valeur de la case (i,j)
    int getCellule(unsigned short int i, unsigned short int j) const;

    void destroyGrid();// remets la grille à 0 (pas certain de ce que ça fait)

    // Redimensionne la grille avec la taille (i,j)
    void redimGrid(unsigned short int i,unsigned short int j);

    void addRows(unsigned int i); // Ajoute i lignes
    void rmRows(unsigned int i); // retire i lignes
    void addCols(unsigned int i, int value = 0); // Ajoute i colonnes, on peut specifier la valeur à donner aux nouvelles cases
    void rmCols(unsigned int i); // retire i colonnes

    void setCols(unsigned int i); // retire/ajoute des colonnes pour arriver à i colonnes
    void setRows(unsigned int i); // retire/ajoute des lignes pour arrives à i lignes
    void setAllTabValue(int v); // mets la valeur v dans toute la grille

};

#endif // ETAT_H
