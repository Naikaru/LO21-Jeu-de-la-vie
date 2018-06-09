#include "headers/gestionnaireautomatefactory.h"

gestionnaireAutomateFactory* gestionnaireAutomateFactory::instance = nullptr;
std::string gestionnaireAutomateFactory::ERROR_NOT_FOUND = "L'automate n'a pas ete trouve";
std::string gestionnaireAutomateFactory::ERROR_BAD_INDEX = "Index incorrect";

gestionnaireAutomateFactory::gestionnaireAutomateFactory()
{
    //automateFactoryTab.push_back(new );
}

const gestionnaireAutomateFactory* gestionnaireAutomateFactory::getInstance(){
    if(instance == nullptr) instance = new gestionnaireAutomateFactory;
    return instance;
}

void gestionnaireAutomateFactory::deleteInstance(){
    if(instance != nullptr){
        delete instance;
        instance = nullptr;
    }
}

std::vector<std::string> gestionnaireAutomateFactory::getNameList(){
    std::vector<std::string>* temp = new std::vector<std::string>;
    for (int i(0);i<automateFactoryTab.size(); i++){
        temp->push_back(automateFactoryTab[i]->getNom());
    }
    return *temp;
}

abstractAutomateFactory* gestionnaireAutomateFactory::getAutomateFactory(std::string name){
    for (int i(0);i<automateFactoryTab.size(); i++)
        if(name == automateFactoryTab[i]->getNom())return automateFactoryTab[i];
    throw new gestionnaireAutomateFactoryException("gestionnaireAutomateFactory::getAutomateFactory(std::string name)->"+ERROR_NOT_FOUND);
}
abstractAutomateFactory* gestionnaireAutomateFactory::getAutomateFactory(int index){
    if (index<automateFactoryTab.size()) return automateFactoryTab[index];
    throw new gestionnaireAutomateFactoryException("gestionnaireAutomateFactory::getAutomateFactory(int index)->"+ERROR_BAD_INDEX);
}

gestionnaireAutomateFactory::~gestionnaireAutomateFactory(){
    for (int i(0);i<automateFactoryTab.size(); i++){
        delete automateFactoryTab[i];
    }
}
