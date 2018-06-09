#ifndef AUTOMATEMAKER_H
#define AUTOMATEMAKER_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include <QFormLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSpinBox>
#include <QString>
#include "headers/simulateur.h"
#include "headers/fenautomate.h"
#include "headers/automate.h"
#include <QMessageBox>
#include "headers/gameoflife.h"
#include "headers/forestfire.h"
#include "headers/fenautomate1d.h"
#include "headers/fenautomate2d.h"
#include "headers/forestfire.h"
#include "headers/automate1d.h"

//   TODO  //
//
// 1/ Ajouter des tests sur les valeurs dans "creatAuto()"
// 2/ Synchroniser numeroAutomate et txtNumeroAutomate
// 3/ Trouver un moyen plus propre de remplir la combobox + mettre à jour les elements (enabled/disabled)
// 4/ Ajuster les valeur min/max des spinBox
//
//   FIN TODO  //

// Classe qui correspond à la petite boite qui crée les automates
class Automatemaker : public QWidget
{
Q_OBJECT
private:
    static Automatemaker* instance; // C'est un sinleton
    Automatemaker(); // Constructeur private
    ~Automatemaker(); // Destructeur private
    void setAutomateList(); // fonction qui initialise la combobox

    // ELEMENTS //
    QComboBox* choixAutomate; // Boite déroulante
    QLineEdit* nomAutomate; // Boite de texte
    QPushButton* btOK; // Bouton créer
    QSpinBox* buffer; // Champ buffer
    QLabel* minVoisinsLabel;
    QSpinBox* minVoisins; // champ nombre min de voisins
    QLabel* maxVoisinsLabel;
    QSpinBox* maxVoisins; // Champ nombre max de voisins
    QLabel* exactVoisinsLabel;
    QSpinBox* exactVoisins; // champ nombre exact de voisins
    QLabel* numeroAutomateLabel;
    QSpinBox* numeroAutomate; // Champ numero automate
    QLabel* txtNumeroAutomateLabel;
    QLineEdit* txtNumeroAutomate; // Champ numero automate (idem qu'avant mais en 00100101)
    QSpinBox* rows; // champ lignes
    QSpinBox* column; // champ colonnes
    QPushButton* btAnnuler; // bouton annuler

public:
    static Automatemaker* getInstance(); // Pour créer ou obtenir l'instance du singleton
    static void release(); // Pour détruire le singleton

public slots:
    void creatAuto(); // Slot qui crée un automate et emit newAuto(fenAutomate*)
    void statusChanged(QString a); // Slot quand la valeur de la QComboBox change (choix du type d'automate)
    void updateMaxVoisins(int n);
    void updateMinVoisins(int n);

signals:
    void newAuto(fenAutomate*);
};

#endif // AUTOMATEMAKER_H
