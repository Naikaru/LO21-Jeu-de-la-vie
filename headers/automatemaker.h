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


// Classe qui correspond à la petite boite qui crée les automates
class Automatemaker : public QWidget
{
Q_OBJECT
private:
    /**
     * @brief instance singleton de AutomateMaker
     */
    static Automatemaker* instance; // C'est un singleton
    /**
     * @brief Automatemaker Constructeur privé (DP Singleton)
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
     * @brief getInstance Fonction pour créer ou obtenir l'instance du singleton
     * @return l'instance du singleton
     */
    static Automatemaker* getInstance(); // Pour créer ou obtenir l'instance du singleton
    /**
     * @brief release Permet de détruire le singleton
     */
    static void release(); // Pour détruire le singleton

public slots:
    /**
     * @brief creatAuto Slot qui crée un automate et emit newAuto(fenAutomate*)
     */
    void creatAuto();

signals:
    /**
     * @brief newAuto Signal envoyé avec emit pour la création (réception dans fenPrincpale)
     */
    void newAuto(fenAutomate*);
};

#endif // AUTOMATEMAKER_H
