#ifndef ABSTRACTAUTOMATEFACTORY_H
#define ABSTRACTAUTOMATEFACTORY_H

#include <cstdio>
#include <string>
#include <QJsonObject>
#include "fenautomate.h"

class abstractAutomateFactory
{
    /**
     * @brief nom de la factory, qui permettra ensuite de distinguer toutes les factory dans le gestionnaire de factory
     */
    std::string nom;
protected:
    /**
     * @brief abstractAutomateFactory Constructeur de abstract factory
     * @param n nom de la factory
     */
    abstractAutomateFactory(std::string n):nom(n){}
public:
    virtual ~abstractAutomateFactory() = default;
    /**
     * @brief getfenAutomate Fonction permettant de récupérer une fenAutomate bien construite, prête à l'utilisation
     * @param monJson Json contenant les valeurs de attributs des elements de la simulation
     * @return fenAutomate prete à l'utilisation
     */
    virtual fenAutomate* getfenAutomate(QJsonObject& monJson) = 0;
    /**
     * @brief getfenAutomate Fonction permettant de récupérer une fenAutomate bien construite, prête à l'utilisation
     * @return fenAutomate prete à l'utilisation
     */
    virtual fenAutomate* getfenAutomate() = 0;
    /**
     * @brief getNom Accesseur de la variable nom
     * @return nom de la factory
     */
    std::string getNom() {return nom;}
};

#endif // ABSTRACTAUTOMATEFACTORY_H
