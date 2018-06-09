#ifndef AUTOMATE_H
#define AUTOMATE_H

#include <string>
#include <vector>
#include <QColor>
#include <iostream>
#include "headers/etat.h"

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
    virtual void applyTransition(const Etat& depart, Etat& arrivee) const = 0;

    // Renvoie un pointeur vers une copie de l'automate
    virtual Automate* copy() const = 0;

    // Pour une ligne r et une colonne c, dans l'Etat e, renvoie si la cellule est en vie
    virtual bool isAlive(unsigned int r, unsigned int c, Etat* e) const{ if(e->getCellule(r,c)==0) return false; else return true; }

    // Pour une ligne r et une colonne c, dans l'Etat e, rends la cellule en vie
    virtual void setAlive(unsigned int r, unsigned int c, Etat* e) const{ e->setCellule(r,c,1);}

    // Pour une ligne r et une colonne c, dans l'Etat e, tue la cellule
    virtual void setDead(unsigned int r, unsigned int c, Etat* e) const{ e->setCellule(r,c,0);}

    // Pour changer le contenu d'une case après click de l'utilisateur
    virtual void changeStatus(unsigned int r, unsigned int c, Etat* e) const = 0;

    //
    virtual const QColor& colorize(int value) const = 0;
};


enum Neighbourhood { VonNeumann=0, Moore=1 };


#endif // AUTOMATE_H
