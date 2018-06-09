#ifndef FORESTFIRE_H
#define FORESTFIRE_H

#include <string>
#include <vector>
#include <QColor>
#include <iostream>
#include "headers/etat.h"
#include "automate.h"

enum stateForest {empty, tree, fire, ashes};

class ForestFire : public Automate
{
private:
    Neighbourhood typeN;
public:
    ForestFire(Neighbourhood n=Moore);
    virtual ~ForestFire()=default;
    ForestFire(const ForestFire& a);
    ForestFire& operator=(const ForestFire& a);
    virtual Automate* copy() const;
    unsigned short int getNeighbourhood() const { return typeN; }
    virtual void applyTransition(const Etat& depart, Etat& arrivee) const;
    virtual void changeStatus(unsigned int r, unsigned int c, Etat* e) const;
    virtual const QColor& colorize(int value) const;
};

#endif // FORESTFIRE_H
