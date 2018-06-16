#ifndef GESTIONNAIREAUTOMATEFACTORY_H
#define GESTIONNAIREAUTOMATEFACTORY_H

#include "headers/abstractautomatefactory.h"
#include <vector>
#include <cstdio>
#include "automate1d.h"
#include "forestfire.h"
#include "gameoflife.h"
/**
 * @brief The gestionnaireAutomateFactoryException class
 *                  Classe qui gère les exceptions du gestionnaireAutomateFactory
 */
class gestionnaireAutomateFactoryException{
    std::string error;
public:
    gestionnaireAutomateFactoryException(const std::string& err):error(err){}
    const std::string getInfo() const{return error;}
};

/**
 * @brief The gestionnaireAutomateFactory class
 *              Singleton qui permet de stocker des instances de factory et de les retrouver avec leur nom
 */
class gestionnaireAutomateFactory
{
    static std::string ERROR_NOT_FOUND;
    static std::string ERROR_BAD_INDEX;
    /**
     * @brief instance Instance de la classe gestionnaireAutomateFactory
     */
    static gestionnaireAutomateFactory* instance;
    /**
     * @brief automateFactoryTab Vecteur d'abstractAutomateFactory, toutes les factory dans ce tableau pourront être choisies
     * par l'utilisateur lors de la génération d'un automate
     */
    std::vector<abstractAutomateFactory*> automateFactoryTab;
    gestionnaireAutomateFactory();
    ~gestionnaireAutomateFactory();
public:
    static gestionnaireAutomateFactory* getInstance();
    static void deleteInstance();
    /**
     * @brief getNameList Renvoie la liste des noms des factory présentes dans le tableau de factory
     * @return liste de noms de factory
     */
    std::vector<std::string> getNameList();
    /**
     * @brief getAutomateFactory permet de récupérer une factory en connaissant son nom/celui de son automate
     * @param name nom de la factory
     * @return la première factory qui a ce nom
     */
    abstractAutomateFactory* getAutomateFactory(std::string name);
    /**
     * @brief getAutomateFactory permet de récupérer la factory présente à cet index
     * @param index index de la factory souhaitée
     * @return factory présente à l'index passé en paramètre
     */
    abstractAutomateFactory* getAutomateFactory(unsigned int index);
};

#endif // GESTIONNAIREAUTOMATEFACTORY_H
