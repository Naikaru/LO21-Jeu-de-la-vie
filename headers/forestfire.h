#ifndef FORESTFIRE_H
#define FORESTFIRE_H

#include <string>
#include <vector>
#include <iostream>
#include "headers/etat.h"
#include "headers/automate.h"
#include "headers/abstractautomatefactory.h"
#include "headers/fenautomate.h"
#include "headers/fenautomate2d.h"

enum stateForest {empty, tree, fire, ashes};

class ForestFire : public Automate
{
   Q_OBJECT

private:
    /**
     * @brief typeN Le type de voisinage (Moore, Von Neumann) déterminant la portée des cellules voisines à considérer pour la transition.
     *          Pour le feu de forêts, c'est le seul attribut modifiable.
     */
    Neighbourhood typeN;

    /**
     * @brief newRules L'interface permettant à l'utilisateur de choisir les règles de transition.
     */
    QWidget* newRules;

    /**
     * @brief voisinage Permet le choix du type de voisinage (VonNeumann ou Moore)
     */
    QComboBox* voisinage;


public:

    ForestFire(Neighbourhood n=Moore);
    virtual ~ForestFire()=default;
    ForestFire(const ForestFire& a);
    ForestFire& operator=(const ForestFire& a);
    virtual Automate* copy() const;

    /**
     * @brief getNeighbourhood Accesseur en lecture de typeN.
     * @return le voisinage sur lequel porte la règle de transition.
     */
    unsigned short int getNeighbourhood() const { return typeN; }

    /**
     * @brief applyTransition Redéfinition de la fonction de Transition.
     *          Pour le feu de forêts, prise en compte du type des voisins (influence de l'etat 'fire' sur l'etat 'tree')
     *          dans un voisinage donné par l'attribut typeN
     * @param depart l'Etat de référence pour la transition
     * @param arrivee Etat résultant de la transition.
     */
    virtual void applyTransition(const Etat& depart, Etat& arrivee) const;

    /**
     * @brief changeStatus Redéfinition du changement d'état après action de l'utilisateur sur une cellule pour lui faire changer d'état
     *           Ici la cellule prend successivement les valeurs empty -> tree -> fire -> ashes
     * @param r row index
     * @param c column index
     * @param e Etat dont provient la cellule.
     */
    virtual void changeStatus(unsigned int r, unsigned int c, Etat* e) const;

    /**
     * @brief colorize : Permet une coloration cohérente de la grille dans l'UI
     * @param value : La valeur de la cellule (empty, tree, fire, ashes)
     * @return La couleur correspondant à valeur
     */
    virtual const QColor& colorize(int value) const;

    /**
     * @brief initRandom Initialise aléatoirement un Etat avec les valeurs empty ou tree.
     *        La rédéfinition de la fonction d'initiation permet au programmateur de déterminer
     *        le nombre d'état que peut prendre une cellule à l'initialisation.
     *        Ici nous aurions pu générer des cellules déjà en feu ou en cendres.
     *        Mais cela nuirait à une véritable cohérence d'un feu de forêt (Simulation).
     * @param e L'Etat à initialiser.
     */
    virtual void initRandom(Etat* e);

    /**
     * @brief initSymetric Initialise aléatoirement mais avec symétrie vertical un Etat avec les valeurs empty ou tree.
     *          Choix du programmateur d'initialiser avec seulement deux valeurs
     *          : mais rendu possible grâce au polymorphisme de la méthode.
     * @param e L'Etat à initialiser.
     */
    virtual void initSymetric(Etat* e);

    /**
     * @brief changeRules La methode permet à l'utilisateur de choisir la règle de transtion via une interface QWidget* newRules
     */
    virtual void changeRules();
    QJsonObject& toJson() const;
    ForestFire(const QJsonObject& myData);

public slots:
    /**
     * @brief slotUpdateRules slot appelé lorsque l'utilisateur confirme le changement de règle.
     *          Il met à jour les paramètres de l'Automate déterminant la règle de transition.
     *          Ici uniquement le voisinage
     */
    void slotUpdateRules();
};

class ForestFireFactory : public abstractAutomateFactory{

public:
    static std::string monNom;
    ForestFireFactory():abstractAutomateFactory(monNom){}
    virtual fenAutomate* getfenAutomate(QJsonObject& monJson);
    virtual fenAutomate* getfenAutomate();
    virtual ~ForestFireFactory() = default;
};
#endif // FORESTFIRE_H
