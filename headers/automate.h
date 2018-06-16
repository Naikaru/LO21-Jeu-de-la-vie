#ifndef AUTOMATE_H
#define AUTOMATE_H

#include <iostream>
#include <string>
#include <vector>
#include "headers/etat.h"
#include <cstdlib>
#include <ctime>

#include <QObject>
#include <QWidget>
#include <QColor>

#include <QFormLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>

#include <QSpinBox>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include <QIntValidator>
#include <QMessageBox>
#include <QString>

/**
 * @brief The AutomateException class
 *          Classe qui gère les exceptions des automates
*/
class AutomateException {
    private:
        std::string info;

    public:
        AutomateException(const std::string& message) : info(message) {}
        std::string getInfo() const { return info; }
};

/**
 * @brief The Automate class
 *          Classe abstraite automate / interface automate
 */
class Automate : public QObject
{
Q_OBJECT

public:
    Automate() = default;
    virtual ~Automate() = default;

     /**
     * @brief applyTransition  Applique la règle de transition correspondant à l'automate (virtuel pur)
     *        sur depart et stocke dans arrivee
     * @param depart etat t
     * @param arrivee etat t+1
     */
    virtual void applyTransition(const Etat& depart, Etat& arrivee) const = 0;

    /**
     * @brief copy Design Pattern
     * @return Renvoie un pointeur vers une copie de l'automate
     */
    virtual Automate* copy() const = 0;

    /**
     * @brief isAlive Renvoie true si la cellule est de valeur 1.
     *        A n'utiliser que pour les automates binaires comme le jeu de la vie
     * @param r : row index
     * @param c : column index
     * @param e : state to check
     * @return
     */
    virtual bool isAlive(unsigned int r, unsigned int c, Etat* e) const{ if(e->getCellule(r,c)==0) return false; else return true; }

    /**
     * @brief setAlive Pour une ligne r et une colonne c, dans l'Etat e, rends la cellule en vie
     *        à n'utiliser que pour les automates binaires (sinon utiliser setCellule)
     * @param r row index
     * @param c column index
     * @param e state to modify
     */
    virtual void setAlive(unsigned int r, unsigned int c, Etat* e) const{ e->setCellule(r,c,1);}

    /**
     * @brief setDead Pour une ligne r et une colonne c, dans l'Etat e, tue la cellule
     *          à n'utiliser que pour les automates binaires sinon utiliser setCellule
     * @param r row index
     * @param c column index
     * @param e state to modify
     */
    virtual void setDead(unsigned int r, unsigned int c, Etat* e) const{ e->setCellule(r,c,0);}

    /**
     * @brief changeStatus Pour changer le contenu d'une case après click de l'utilisateur
     *        Ce changement est propre à chaque automates (transitions différentes selon le nbr d'états etc.)
     * @param r row index
     * @param c column index
     * @param e state to modify
     */
    virtual void changeStatus(unsigned int r, unsigned int c, Etat* e) const = 0;

    /**
     * @brief colorize Permet le renvoie d'une couleur associé à une état (symbolisé par une valeur entière)
     *          Définie pour chaque automate fils, nombre d'état différents
     * @param value Généralement, la valeur de la cellule.
     * @return La couleur associée à value
     */
    virtual const QColor& colorize(int value) const = 0;

    /**
     * @brief changeRules Permet de changer les règles de transtions (par polymorphisme)
     *          à l'aide d'une interface graphique définie dans la fonction.
     *          Redéfinie pour chaque Automate.
     */
    virtual void changeRules() = 0;

    /**
     * @brief initRandom Genere un Etat aléatoirement (probabilité d'appariation aléatoire également).
     *          Redéfini pour chaque Automate fils,
     *          car le nombre de valeurs prises par les cellules peut différe
     * @param e state to initiate
     */
    virtual void initRandom(Etat* e) = 0; // De manière aléatoire
    /**
     * @brief initSymetric Genere un Etat aléatoirement avec symetrie par rapport à l'axe vertical.
     *          Redéfini pour chaque Automate fils,
     *          car le nombre de valeurs prises par les cellules peut différe
     * @param e
     */
    virtual void initSymetric(Etat* e) = 0; // De manière symétrique (pas rapport à l'axe des ordonnées
    virtual QJsonObject& toJson() const = 0;
};


/**
 * @brief The Neighbourhood enum Le type de voisinage possible :
 *          Von Neumann considère les 4 premières cellules entourant la cellule
 *          Moore d'ordre 1 considère les 8 première cellules entourant la cellule.
 */
enum Neighbourhood { VonNeumann=0, Moore=1 };

#endif // AUTOMATE_H
