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
    static Automatemaker* instance; // C'est un singleton
    Automatemaker(); // Constructeur private
    ~Automatemaker(); // Destructeur private
    void setAutomateList(); // fonction qui initialise la combobox

    // ELEMENTS //
    QLabel* monTexte;
    QVBoxLayout* monVerticalLayout;
    QHBoxLayout* monHorizontalLayout;
    QComboBox* choixAutomate; // Boite déroulante
    QPushButton* btOK; // Bouton créer
    QPushButton* btAnnuler; // bouton annuler

public:
    static Automatemaker* getInstance(); // Pour créer ou obtenir l'instance du singleton
    static void release(); // Pour détruire le singleton

public slots:
    void creatAuto(); // Slot qui crée un automate et emit newAuto(fenAutomate*)

signals:
    void newAuto(fenAutomate*);
};

#endif // AUTOMATEMAKER_H
