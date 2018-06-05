#ifndef AUTOMATE_H
#define AUTOMATE_H
#include <string>
#include <vector>
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

    // Applique la transition sur depart et stocke dans arrivee
    virtual void applyTransition(Etat* depart, Etat* arrivee) const = 0;

    // Renvoie un pointeur vers une copie de l'automate
    virtual Automate* copy() const = 0;

    // Pour une ligne r et une colonne c, dans l'Etat e, renvoie si la cellule est en vie
    virtual bool isAlive(unsigned int r, unsigned int c, Etat* e) const = 0;

    // Pour une ligne r et une colonne c, dans l'Etat e, rends la cellule en vie
    virtual void setAlive(unsigned int r, unsigned int c, Etat* e) const = 0;

    // Pour une ligne r et une colonne c, dans l'Etat e, tue la cellule
    virtual void setDead(unsigned int r, unsigned int c, Etat* e) const = 0;

    virtual ~Automate() = default;
};

class Automate2D : public Automate
{
private:
    unsigned short int minNeighbours;
    unsigned short int maxNeighbours;
    unsigned short int exactNeighbours;
    static unsigned short int countNeighbours(const Etat& e, unsigned short int row, unsigned short int col); // Fonction qui compte les voisis d'une cellule
public:
    Automate2D(unsigned short int min=2, unsigned short int max=3, unsigned short int exact=3); // Constructeur, par défaut c'est un jeu de la vie
    ~Automate2D()=default;
    Automate2D(const Automate2D& a);// Constructeur de recopie
    Automate2D& operator=(const Automate2D& a); // operateur d'affectation
    virtual Automate* copy() const;
    unsigned short int getMinNeighbours() const { return minNeighbours; } // Accesseur
    unsigned short int getMaxNeighbours() const { return maxNeighbours; } // Accesseur
    unsigned short int getExactNeighbours() const { return exactNeighbours; } // Accesseur
    virtual void applyTransition(Etat* depart, Etat* arrivee) const;
    virtual bool isAlive(unsigned int r, unsigned int c, Etat* e) const{ if(e->getCellule(r,c)==0) return false; else return true;}
    virtual void setAlive(unsigned int r, unsigned int c, Etat* e) const{ e->setCellule(r,c,1);}
    virtual void setDead(unsigned int r, unsigned int c, Etat* e) const{ e->setCellule(r,c,0);}
    // nb: le test pour savoir si r,c ne sont pas outofbound se fait dans etat
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
    virtual bool isAlive(unsigned int r, unsigned int c, Etat* e) const{ if(e->getCellule(r,c)==0) return false; else return true;}
    virtual void setAlive(unsigned int r, unsigned int c, Etat* e) const{ e->setCellule(r,c,1);}
    virtual void setDead(unsigned int r, unsigned int c, Etat* e) const{ e->setCellule(r,c,0);}

};

short unsigned int NumBitToNum(const std::string& num); // Transforme les string de 0 et de 1 en int
std::string NumToNumBit(short unsigned int num); // Transforme les int en string de 0 et 1

#endif // AUTOMATE_H
