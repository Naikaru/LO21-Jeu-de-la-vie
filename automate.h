#ifndef AUTOMATE_H
#define AUTOMATE_H

#include <string>
#include <vector>
#include <QColor>
#include <iostream>
#include "etat.h"

// Classe qui gère les exceptions des automates
class AutomateException {
    private:
        std::string info;

    public:
        AutomateException(const std::string& message) : info(message) {}
        std::string getInfo() const { return info; }
};

// Classe abstraite automate / interface automate
class Automate
{
public:
    Automate() = default;
    virtual ~Automate() = default;

    // Applique la transition sur depart et stocke dans arrivee
    virtual void applyTransition(Etat* depart, Etat* arrivee) const = 0;

    // Renvoie un pointeur vers une copie de l'automate
    virtual Automate* copy() const = 0;

    // Pour une ligne r et une colonne c, dans l'Etat e, renvoie si la cellule est en vie
    virtual bool isAlive(unsigned int r, unsigned int c, Etat* e) const{ if(e->getCellule(r,c)==0) return false; else return true; }

    // Pour une ligne r et une colonne c, dans l'Etat e, rends la cellule en vie
    virtual void setAlive(unsigned int r, unsigned int c, Etat* e) const{ e->setCellule(r,c,1);}

    // Pour une ligne r et une colonne c, dans l'Etat e, tue la cellule
    virtual void setDead(unsigned int r, unsigned int c, Etat* e) const{ e->setCellule(r,c,0);}

    //
    virtual const QColor& colourize(int value) const = 0;
};


class Automate1D : public Automate
{
private:
    unsigned short int numero;
    std::string numeroBit;
    static std::string ERROR_BAD_ETAT;

public:
    Automate1D(unsigned short int num);
    Automate1D(const std::string& num);
    ~Automate1D()= default;
    Automate1D(const Automate1D& a);
    Automate1D& operator=(const Automate1D& a);
    virtual Automate* copy() const;
    unsigned short int getNumero() const { return numero; }
    const std::string& getNumeroBit() const { return numeroBit; }

    virtual void applyTransition(Etat* depart, Etat* arrivee) const;
    virtual const QColor& colourize(int value)const;
};

short unsigned int NumBitToNum(const std::string& num); // Transforme les string de 0 et de 1 en int
std::string NumToNumBit(short unsigned int num); // Transforme les int en string de 0 et 1

/**********************************************
 ************       MODE 2D     ***************
 **********************************************/

// Définition du voisinage : Moore 8 voisins, VonNeumann : 4  voisins
enum Neighbourhood { Moore, VonNeumann };

/***** Jeu de la vie *****/

class GameOfLife : public Automate
{
private:
    unsigned short int minNeighbours;
    unsigned short int maxNeighbours;
    unsigned short int exactNeighbours;
    Neighbourhood typeN;
public:
    GameOfLife(unsigned short int min=2, unsigned short int max=3, unsigned short int exact=3, Neighbourhood n=VonNeumann); // Constructeur, par défaut c'est un jeu de la vie
    ~GameOfLife()=default;
    GameOfLife(const GameOfLife& a);// Constructeur de recopie
    GameOfLife& operator=(const GameOfLife& a); // operateur d'affectation
    virtual Automate* copy() const;
    unsigned short int getMinNeighbours() const { return minNeighbours; } // Accesseur
    unsigned short int getMaxNeighbours() const { return maxNeighbours; } // Accesseur
    unsigned short int getExactNeighbours() const { return exactNeighbours; } // Accesseur
    unsigned short int getNeighbourhood() const { return typeN; }
    unsigned short int countNeighbours(const Etat& e, unsigned short int row, unsigned short int col) const;// Fonction qui compte les voisis d'une cellule
    virtual void applyTransition(Etat* depart, Etat* arrivee) const;
    // nb: le test pour savoir si r,c ne sont pas outofbound se fait dans etat
    virtual const QColor& colourize(int value) const;
};


/***** Feu de Forêt *****/

enum stateForest {empty, tree, fire, ashes};

class ForestFire : public Automate
{
private:
    Neighbourhood typeN;
public:
    ForestFire(Neighbourhood n=VonNeumann);
    virtual ~ForestFire();
    ForestFire(const ForestFire& a);
    ForestFire& operator=(const ForestFire& a);
    virtual Automate* copy() const;
    unsigned short int getNeighbourhood() const { return typeN; }
    virtual void applyTransition(const Etat* dep, Etat* dest) const;
};


#endif // AUTOMATE_H
