#ifndef GESTIONNAIREAUTOMATEFACTORY_H
#define GESTIONNAIREAUTOMATEFACTORY_H

#include "headers/abstractautomatefactory.h"
#include <vector>
#include <cstdio>
#include "automate1d.h"
#include "forestfire.h"
#include "gameoflife.h"

class gestionnaireAutomateFactoryException{
    std::string error;
public:
    gestionnaireAutomateFactoryException(const std::string& err):error(err){}
    const std::string getInfo() const{return error;}
};

class gestionnaireAutomateFactory
{
    static std::string ERROR_NOT_FOUND;
    static std::string ERROR_BAD_INDEX;
    static gestionnaireAutomateFactory* instance;
    std::vector<abstractAutomateFactory*> automateFactoryTab;
    gestionnaireAutomateFactory();
    ~gestionnaireAutomateFactory();
public:
    static gestionnaireAutomateFactory* getInstance();
    static void deleteInstance();
    std::vector<std::string> getNameList();
    abstractAutomateFactory* getAutomateFactory(std::string name);
    abstractAutomateFactory* getAutomateFactory(int index);
};

#endif // GESTIONNAIREAUTOMATEFACTORY_H
