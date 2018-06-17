#ifndef AUTOMATEMAKER_H
#define AUTOMATEMAKER_H

#include <QWidget>
#include <QLabel>
#include <QComboBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "headers/gestionnaireautomatefactory.h"
#include "headers/fenautomate.h"
#include "headers/abstractautomatefactory.h"
#include <vector>
#include <string>


/**
 * @brief The Automatemaker class
 *              Récupère le choix de l'utilisateur et crée la fenAutomate correspondant
 */
class Automatemaker : public QWidget
{
Q_OBJECT
private:
    /**
     * @brief instance singleton de AutomateMaker
     */
    static Automatemaker* instance; // C'est un singleton
    /**
     * @brief Automatemaker Constructeur (privé) de la classe
     */
    Automatemaker(); // Constructeur private

    ~Automatemaker(); // Destructeur private
    /**
     * @brief setAutomateList Fonction qui initialise la QComboBox (relative au choix de l'Automate)
     */
    void setAutomateList(); // fonction qui initialise la combobox

    // ELEMENTS //
    QLabel* monTexte;
    QVBoxLayout* monVerticalLayout;
    QHBoxLayout* monHorizontalLayout;
    QComboBox* choixAutomate; // Boite déroulante
    QPushButton* btOK; // Bouton créer
    QPushButton* btAnnuler; // bouton annuler

public:
    /**
     * @brief getInstance Fonction statique qui renvoie l'instance de AutomateMaker si elle existe, ou en crée une sinon
     * @return Instance de automatemaker
     */
    static Automatemaker* getInstance(); // Pour créer ou obtenir l'instance du singleton
    /**
     * @brief release détruit l'instance de automatemaker si elle existe
    */
    static void release(); // Pour détruire le singleton

public slots:
    /**
     * @brief creatAuto Crée un automate en fonction de la valeur de la combobox, et envoie le signal "newAuto"
     */
    void creatAuto(); // Slot qui crée un automate et emit newAuto(fenAutomate*)

signals:
    /**
     * @brief newAuto Signal émis lorsque l'utilisateur a cliqué sur le bouton pour créer un nouvel automate
     */
    void newAuto(fenAutomate*);
};

#endif // AUTOMATEMAKER_H
