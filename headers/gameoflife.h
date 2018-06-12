#ifndef GAMEOFLIFE_H
#define GAMEOFLIFE_H

#include <string>
#include <vector>
#include <iostream>
#include "headers/etat.h"
#include "headers/automate.h"
#include "headers/fenautomate.h"
#include "headers/fenautomate2d.h"
#include "headers/abstractautomatefactory.h"

class GameOfLife : public Automate
{

private:
    unsigned short int minNeighbours;
    unsigned short int maxNeighbours;
    unsigned short int exactNeighbours;
    Neighbourhood typeN;

    QWidget* newRules;
    QSpinBox* minVoisins;
    QSpinBox* maxVoisins;
    QSpinBox* exactVoisins;
    QComboBox* voisinage;

public:
    GameOfLife(unsigned short int min=2, unsigned short int max=3, unsigned short int exact=3, Neighbourhood n=Moore); // Constructeur, par défaut c'est un jeu de la vie
    virtual ~GameOfLife()=default;
    GameOfLife(const GameOfLife& a);// Constructeur de recopie
    GameOfLife& operator=(const GameOfLife& a); // operateur d'affectation
    virtual Automate* copy() const;
    unsigned short int getMinNeighbours() const { return minNeighbours; } // Accesseur
    unsigned short int getMaxNeighbours() const { return maxNeighbours; } // Accesseur
    unsigned short int getExactNeighbours() const { return exactNeighbours; } // Accesseur
    unsigned short int getNeighbourhood() const { return typeN; }
    unsigned short int countNeighbours(const Etat& e, unsigned short int row, unsigned short int col) const;// Fonction qui compte les voisis d'une cellule
    virtual void applyTransition(const Etat& depart, Etat &arrivee) const;
    // nb: le test pour savoir si r,c ne sont pas outofbound se fait dans etat
    virtual void changeStatus(unsigned int r, unsigned int c, Etat* e) const;
    virtual const QColor& colorize(int value) const;
    virtual void changeRules();

public slots:
    void slotMinChanged(int value);
    void slotMaxChanged(int value);
    void slotUpdateRules();

};

class GameOfLifeFactory : public abstractAutomateFactory{
public:
    GameOfLifeFactory():abstractAutomateFactory("Jeu de la vie"){}
    virtual fenAutomate* getfenAutomate();
    virtual ~GameOfLifeFactory() = default;

};
#endif // GAMEOFLIFE_H
