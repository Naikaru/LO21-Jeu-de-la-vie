#ifndef ABSTRACTAUTOMATEFACTORY_H
#define ABSTRACTAUTOMATEFACTORY_H

#include <cstdio>
#include <string>
#include <QJsonObject>
#include "fenautomate.h"

class abstractAutomateFactory
{
    std::string nom;
protected:
    abstractAutomateFactory(std::string n):nom(n){}
public:
    virtual ~abstractAutomateFactory() = default;
    virtual fenAutomate* getfenAutomate(QJsonObject& monJson) = 0;
    virtual fenAutomate* getfenAutomate() = 0;
    std::string getNom() {return nom;}
};

#endif // ABSTRACTAUTOMATEFACTORY_H
