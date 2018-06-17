#ifndef ETAT_H
#define ETAT_H
#include <QWidget>
#include <string>
#include <vector>
#include <QJsonArray>
#include <QJsonObject>
#include <iostream>

/**
 * \file etat.h
 * \brief Header contenant la classe Etat.
 */


/**
 * @brief The EtatException class permet de gérer les exceptions liées à la classe Etat
 */
class EtatException {
    private:
        std::string info;

    public:
        EtatException(const std::string& message) : info(message) {}
        std::string getInfo() const { return info; }
};


/**
 * @brief The Etat class correspond à un état d'un automate cellulaire (une génération)
 */
class Etat
{
    /**
     * @brief ERROR_BAD_INDEX est un code erreur générique pour la classe Etat
     */
    static std::string ERROR_BAD_INDEX;

    /**
     * @brief grid est une matrice d'entier, permettant de gérer les valeurs prises par chaque cellules
     */
    std::vector<std::vector<int>> grid;
    // grid[Rows][Cols]

    /**
     * @brief nbRows Le nombre de lignes de la grille
     */
    unsigned short int nbRows;
    /**
     * @brief nbCols Le nombre de colonnes de la grille
     */
    unsigned short int nbCols;

public:
    Etat(unsigned short int Rows=10,unsigned short int Cols=10);
    Etat(const Etat& e);
    Etat& operator=(const Etat& e);

    ~Etat() = default;

    /**
     * @brief getNbRows Accesseur en lecture pour obtenir le nombre de lignes.
     * @return l'attribut nbRows
     */
    unsigned short int getNbRows() const { return nbRows; }

    /**
     * @brief getNbCols Accesseur en lecture pour obtenir le nombre de colonnes
     * @return l'attribut nbCols
     */
    unsigned short int getNbCols() const { return nbCols; }

    /**
     * @brief setCellule Permet la mise à jour de la cellule d'indice (i,j)
     * @param i row index
     * @param j column index
     * @param val la nouvelle valeur prise par la cellule
     */
    void setCellule(unsigned short int i,unsigned short int j,int val);

    /**
     * @brief getCellule renvoie la valeur de la cellule d'indice (i,j)
     * @param i row index
     * @param j column index
     * @return La valeur de grid[i][j]
     */
    int getCellule(unsigned short int i, unsigned short int j) const;

    /**
     * @brief destroyGrid permet de réinitialiser la grille avec la valeur 0.
     */
    void destroyGrid();

    /**
     * @brief redimGrid Redimensionne la grille avec la taille (i,j)
     * @param i le nouveau nombre de lignes
     * @param j le nouveau nombre de colonnes
     */
    void redimGrid(unsigned short int i,unsigned short int j);

    /**
     * @brief addRows Permet l'ajout de lignes à l'attribut grid
     * @param i le nombre de lignes à ajouter
     */
    void addRows(unsigned int i);

    /**
     * @brief rmRows Permet la suppression de lignes à l'attribut grid
     * @param i le nombre de lignes à retirer
     */
    void rmRows(unsigned int i);

    /**
     * @brief addCols Permet l'ajout de colonnes à l'attribut grid
     * @param i le nombre de colonnes à ajouter
     * @param value la valeur des cases qui composent les colonnes ajoutées (0 par défaut).
     */
    void addCols(unsigned int i, int value = 0); // Ajoute i colonnes, on peut specifier la valeur à donner aux nouvelles cases

    /**
     * @brief rmCols Permet la suppression de colonnes à l'attribut grid
     * @param i le nombre de colonnes à retirer
     */
    void rmCols(unsigned int i);

    /**
     * @brief setCols Variante de addCols : réajuste le nombre de colonnes de grid avec une valeur exacte.
     *          retire/ajoute des colonnes pour arriver à i colonnes
     * @param i le nombre de colonnes final de grid
     */
    void setCols(unsigned int i);

    /**
     * @brief setRows Variante de addRows : réajuste le nombre de lignes de grid avec une valeur exacte.
     *          retire/ajoute des lignes pour arriver à i lignes
     * @param i
     */
    void setRows(unsigned int i);

    /**
     * @brief setAllTabValue Permet de donner à la totalité de la grille va valeur v
     * @param v La valeur à insérer dans chaque cellule
     */
    void setAllTabValue(unsigned int v);
    /**
     * @brief toJson Renvoie un QJsonObject qui contient la valeur des attributs de l'etat au format JSON
     * @return Valeur des attributs de l'objet au format Json
     */
    QJsonObject& toJson() const;
    /**
     * @brief Etat Constructeur à partir d'une structure JSON
     * @param eJson Structure contenant les paramètres de Etat
     */
    Etat(const QJsonObject& eJson);
};

#endif // ETAT_H
