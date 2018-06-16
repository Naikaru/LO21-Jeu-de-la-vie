#ifndef AUTOMATE1D_H
#define AUTOMATE1D_H

#include <string>
#include <vector>
#include <iostream>
#include "headers/etat.h"
#include "headers/automate.h"
#include "headers/fenautomate.h"
#include "headers/fenautomate1d.h"
#include "headers/abstractautomatefactory.h"

/**
 * @brief The Automate1D class
 *          Classe fille de Automate générant l'automate linéaire vu en TD
 */
class Automate1D : public Automate
{
Q_OBJECT

private:
    /**
     * @brief numero Numéro entier de la règle de transition de Automate1D
     *          à valeur dans [0 ; 255]
     */
    unsigned short int numero;
    /**
     * @brief numeroBit Numéro biniare (sous forme de string) de la règle de transition
     *      Chaque au résultat pour chaque configuration possible (string de 8 charactères)
     */
    std::string numeroBit;

    /**
     * @brief ERROR_BAD_ETAT Erreur générique à utiliser avec AutomateException
     */
    static std::string ERROR_BAD_ETAT;

    /**
     * @brief newRules : QWidget permettant le changement manuel des règles de transition de Automate1D
     */
    QWidget* newRules;

    /**
     * @brief numRule : Correspondant au numéro entier de la règle en tant qu'objet graphique
     *        pour la modification de la règle de l'automate
     */
    QSpinBox* numRule;

    /**
     * @brief numBitRule : Correspond au numéro en "string" binaire de la règle en tant qu'objet graphique
     *        pour la modification de la règle de l'automate
     */
    QLineEdit* numBitRule[8];  // numéro de la règle en "string" binaire

public:
    /**
     * @brief Automate1D Constructeur de la classe
     * @param num règle de transition
     */
    Automate1D(unsigned short int num = 42);
    Automate1D(const std::string& num);
    virtual ~Automate1D()= default;
    /**
     * @brief Automate1D Constructeur de recopie
     * @param a Automate à recopier
     */
    Automate1D(const Automate1D& a);
    /**
     * @brief operator= surcharge de l'operateur = : Constructeur par affectation
     * @param a Automate à affecter
     * @return L'automate initialisé avec a
     */
    Automate1D& operator=(const Automate1D& a);

    virtual Automate* copy() const;

    /**
     * @brief getNumero Accesseur en lecture
     * @return La règle de transition (entière)
     */
    unsigned short int getNumero() const { return numero; }
    /**
     * @brief getNumeroBit Accesseur en lecture
     * @return La règle de transition (string)
     */
    const std::string& getNumeroBit() const { return numeroBit; }

    /**
     * @brief applyTransition Redéfinition de la règle de Transition première en compte le numéro de règle
     * @param depart Etat au temps t servant de support pour la transition
     * @param arrivee Etat au temps t+1 copie de depart, mais ayant subit la transition.
     */
    virtual void applyTransition(const Etat& depart, Etat& arrivee) const;

    /**
     * @brief changeStatus Redéfinition du changement d'état après action de l'utilisateur
     * @param r row index
     * @param c column index
     * @param e state to modify
     */
    virtual void changeStatus(unsigned int r, unsigned int c, Etat* e) const;

    /**
     * @brief colorize Permet une coloration cohérente de la grille dans l'UI
     * @param value La valeur de la cellule (0 ou 1 pour Automate1D)
     * @return La couleur correspondant à valeur
     */
    virtual const QColor& colorize(int value)const;

    /**
     * @brief initRandom Initialise aléatoirement un Etat avec des valeurs 0 ou 1
     * @param e L'Etat a initialiser
     */
    virtual void initRandom(Etat* e);
    /**
     * @brief initSymetric Initialise aléatoirement mais avec symétrie vertical un Etat avec des valeurs 0 ou 1
     * @param e L'Etat à initialiser
     */
    virtual void initSymetric(Etat* e);

    /**
     * @brief changeRules La methode permet à l'utilisateur de choisir la règle de transtion
     */
    virtual void changeRules();

    QJsonObject& toJson() const;

    Automate1D(const QJsonObject& myData);

public slots:
    /**
     * @brief slotUpdateRules slot mettant à jour la regle de transition après validation de l'utilsateur
     *          dans la fenetre générée par changeRules()
     */
    void slotUpdateRules();

    /**
     * @brief slotNumToNumBit slot permettant la cohérence numBitRule (Q_Object) binaire(string) de la règle
     * @param n l'entier à convertir en binaire (string)
     */
    void slotNumToNumBit(int n);

    /**
     * @brief slotNumBitToNum slot permettant la cohérence de numRule (Q_Object) entier de la règle
     * @param n la chaine de caracère à convertir en entier
     */
    void slotNumBitToNum(const QString& n);


};

/**
 * @brief NumBitToNum Transforme les string binaire (de 0 et de 1) en int
 * @param num la chaine de caractère à transformer
 * @return l'equivalent entier du nombre binaire
 */
short unsigned int NumBitToNum(const std::string& num);

/**
 * @brief NumToNumBit Transforme les int en string binaire (de 0 et 1)
 * @param num l'entier à convertir en nombre binaire sous forme de string
 * @return l'equivalent binaire (string) de num
 */
std::string NumToNumBit(short unsigned int num);


class Automate1DFactory : public abstractAutomateFactory{
public:
    static std::string monNom;
    Automate1DFactory():abstractAutomateFactory(monNom){}
    virtual fenAutomate* getfenAutomate(QJsonObject& monJson);
    virtual fenAutomate* getfenAutomate();
    virtual ~Automate1DFactory() = default;
};
#endif // AUTOMATE1D_H
