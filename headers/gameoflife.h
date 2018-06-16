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
    Q_OBJECT

private:
    /**
     * @brief minNeighbours La borne inférieure de l'intervalle telle que la cellule survive.
     */
    unsigned short int minNeighbours;
    /**
     * @brief maxNeighbours La borne supérieure de l'intervalle telle que la cellule survive.
     */
    unsigned short int maxNeighbours;
    /**
     * @brief exactNeighbours Le nombre exacte de cellule dans le voisinage telle qu'il y ait naissance d'une cellule vivante.
     */
    unsigned short int exactNeighbours;
    /**
     * @brief typeN Le type de voisinage (ici restreint à VonNeumann ou Moore).
     */
    Neighbourhood typeN;

    /**
     * @brief newRules L'interface permettant à l'utilisateur de choisir les règles de transition.
     */
    QWidget* newRules;
    /**
     * @brief minVoisins La QSpinBox permettant à l'utilisateur de choisir la valeur de la borne inférieure.
     */
    QSpinBox* minVoisins;
    /**
     * @brief maxVoisins La QSpinBox permettant à l'utilisateur de choisir la valeur de la borne supérieure.
     */
    QSpinBox* maxVoisins;
    /**
     * @brief exactVoisins La QSpinBox permettant à l'utilisateur de choisir le nombre de voisins pour une naissance.
     */
    QSpinBox* exactVoisins;
    /**
     * @brief voisinage Permet le choix du type de voisinage (VonNeumann ou Moore)
     */
    QComboBox* voisinage;

public:
    GameOfLife(unsigned short int min=2, unsigned short int max=3, unsigned short int exact=3, Neighbourhood n=Moore); // Constructeur, par défaut c'est un jeu de la vie
    virtual ~GameOfLife()=default;
    GameOfLife(const GameOfLife& a);// Constructeur de recopie
    GameOfLife& operator=(const GameOfLife& a); // operateur d'affectation
    virtual Automate* copy() const;

    /**
     * @brief getMinNeighbours Accesseur en lecture de minNeighbours.
     * @return la valeur de la borne inférieure minNeighbours.
     */
    unsigned short int getMinNeighbours() const { return minNeighbours; }

    /**
     * @brief getMaxNeighbours Accesseur en lecture de maxNeighbours.
     * @return la valeur de la borne supérieure maxNeighbours.
     */
    unsigned short int getMaxNeighbours() const { return maxNeighbours; }

    /**
     * @brief getExactNeighbours Accesseur en lecture de exactNeighbours.
     * @return le nombre exact de voisins pour une naissance exactNeighbours.
     */
    unsigned short int getExactNeighbours() const { return exactNeighbours; }

    /**
     * @brief getNeighbourhood Accesseur en lecture de typeN.
     * @return le voisinage sur lequel porte la règle de transition.
     */
    unsigned short int getNeighbourhood() const { return typeN; }

    /**
     * @brief countNeighbours Fonction permettant de dénombrer le nombre de voisins entourant une cellule selon son voisinage.
     * @param e L'Etat actuel de la simulation, sur lequel se trouve la cellule à analyser.
     * @param row index de ligne
     * @param col index de colonne
     * @return Le nombre de voisin entourant e(row, col)
     */
    unsigned short int countNeighbours(const Etat& e, unsigned short int row, unsigned short int col) const;// Fonction qui compte les voisis d'une cellule

    /**
     * @brief applyTransition Redéfinition de la fonction de Transition.
     *          Pour le jeu de la vie, prise en compte du nombre de voisins (cellule dont la valeur = 1) déterminé par la fonction countNeighbours
     * @param depart l'Etat de référence pour la transition
     * @param arrivee Etat résultant de la transition.
     */
    virtual void applyTransition(const Etat& depart, Etat &arrivee) const;
    // nb: le test pour savoir si r,c ne sont pas outofbound se fait dans etat

    /**
     * @brief changeStatus Redéfinition du changement d'état après action de l'utilisateur sur une cellule pour lui faire changer d'état
     * @param r row index
     * @param c column index
     * @param e Etat dont provient la cellule.
     */
    virtual void changeStatus(unsigned int r, unsigned int c, Etat* e) const;
    /**
     * @brief colorize : Permet une coloration cohérente de la grille dans l'UI
     * @param value : La valeur de la cellule (0 ou 1 pour GameOfLife classique)
     * @return La couleur correspondant à valeur
     */
    virtual const QColor& colorize(int value) const;

    /**
     * @brief initRandom Initialise aléatoirement un Etat avec les valeurs 0 ou 1.
     * @param e L'Etat à initialiser.
     */
    virtual void initRandom(Etat* e);

    /**
     * @brief initSymetric Initialise aléatoirement mais avec symétrie vertical un Etat avec les valeurs 0 ou 1.
     * @param e L'Etat à initialiser.
     */
    virtual void initSymetric(Etat* e);

    /**
     * @brief changeRules La methode permet à l'utilisateur de choisir la règle de transtion via une interface QWidget* newRules
     */
    virtual void changeRules();
    QJsonObject& toJson() const;
    GameOfLife(const QJsonObject& myData);
public slots:
    /**
     * @brief slotMinChanged slot permettant la cohérence entre la borne maximum et minimum (On empêche le croisement)
     *        mise à jour de la valeur minimale prenable par maxNeighburs
     * @param value : la nouvelle valeur prise par minNeighbours devient la borne inférieure de maxNeighbours.
     */
    void slotMinChanged(int value);

    /**
     * @brief slotMaxChanged slot permettant la cohérence entre la borne maximum et minimum (On empêche le croisement)
     *        mise à jour de la valeur maximale prenable par minNeighburs
     * @param value : la nouvelle valeur prise par maxNeighbours devient la borne supérieure de minNeighbours.
     */
    void slotMaxChanged(int value);

    /**
     * @brief slotUpdateRules slot appelé lorsque l'utilisateur confirme le changement de règle.
     *          Il met à jour les paramètres de l'Automate déterminant la règle de transition.
     */
    void slotUpdateRules();


};

class GameOfLifeFactory : public abstractAutomateFactory{
public:
    static std::string monNom;
    GameOfLifeFactory():abstractAutomateFactory(monNom){}
    virtual fenAutomate* getfenAutomate();
    virtual fenAutomate* getfenAutomate(QJsonObject& monJson);
    virtual ~GameOfLifeFactory() = default;

};
#endif // GAMEOFLIFE_H
