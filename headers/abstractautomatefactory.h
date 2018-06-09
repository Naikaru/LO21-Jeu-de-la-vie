#ifndef ABSTRACTAUTOMATEFACTORY_H
#define ABSTRACTAUTOMATEFACTORY_H

#include <cstdio>
#include <string>
#include "fenautomate.h"

class abstractAutomateFactory
{
    std::string nom;
protected:
    abstractAutomateFactory(std::string n):nom(n){}
public:
    virtual ~abstractAutomateFactory();
    virtual fenAutomate* getfenAutomate() = 0;
    std::string getNom() {return nom;}
};

#endif // ABSTRACTAUTOMATEFACTORY_H
