#ifndef SIMULATEUR_H
#define SIMULATEUR_H

#include "headers/automate.h"
#include "headers/etat.h"

//   TODO  //
//
//
//   FIN TODO  //

// Classe qui correspond aux exceptions de simulateur

class SimulateurException
{
    std::string info;
public:
    SimulateurException(const std::string& message) : info(message) {}
    std::string getInfo() const { return info; }
};


class Simulateur
{
    // Codes d'exception
    static std::string ERROR_BUFFER_LENGTH;
    static std::string ERROR_BAD_START_STATE;
    static std::string ERROR_NO_INIT;
    const Automate* myAutomat;
    Etat** etats;
    const Etat* depart;
    unsigned int nbMaxEtats;
    unsigned int rang;

public:

    Simulateur(const Automate* a, const Etat* dep, unsigned int buffer = 2);
    Simulateur(const Simulateur& s);
    Simulateur& operator=(const Simulateur& s);
     ~Simulateur();

     void build(unsigned int c); // Crée l'etat c a partir de l'etat de depart

     // l'element dans la case (R,C) est mis en vie en utilisant la définition de "en vie" de l'automate
     void setAlive(unsigned int r, unsigned int c){
         if(etats == nullptr || etats[rang%nbMaxEtats]==nullptr) throw SimulateurException("Simulateur::setAlive"+ERROR_NO_INIT);
         myAutomat->setAlive(r,c,getInitialState()); }

     // l'element dans la case (R,C) est tué, en utilisant la def. de l'automate
     void setDead(unsigned int r, unsigned int c){
         if(etats == nullptr || etats[rang%nbMaxEtats]==nullptr) throw SimulateurException("Simulateur::setDead"+ERROR_NO_INIT);
         myAutomat->setDead(r,c,getInitialState()); }

     // renvoie vrai si l'element dans la case (R,C) est en vie, en utilisant la def de l'automate
     bool isAlive(unsigned int r, unsigned int c){
         if(etats == nullptr || etats[rang%nbMaxEtats]==nullptr) throw SimulateurException("Simulateur::isAlive"+ERROR_NO_INIT);
         return myAutomat->isAlive(r,c,getInitialState()); }

     void changeStatus(unsigned int r, unsigned int c) {
         if(etats == nullptr || etats[rang%nbMaxEtats]==nullptr) throw SimulateurException("Simulateur::changeStatus"+ERROR_NO_INIT);
         myAutomat->changeStatus(r,c,getInitialState()); }

     void addCol(){
         getInitialState()->addCols(1); // Méthode de Etat
     }

     void redim(unsigned int i, unsigned int j){
         getInitialState()->redimGrid(i,j); // Méthode de Etat
     }

     const Automate& getAutomate(){ return *myAutomat;}
     void setEtatDepart(const Etat& e); // Définit l'état de départ sur l'etat passé en param
     void run(unsigned int nbSteps); // génère les n prochains états
     void next(); // génère le prochain état
     const Etat& dernier() const; // renvoie le dernier etat généré
     unsigned int getRangDernier() const { return rang; } // retourne le rang du dernier
     void reset(); // revenir à l'état de départ
     Etat* getInitialState(){return const_cast<Etat*>(depart);} // retourne l'etat initial du simulateur (avec possibilité de le modifier)
};

#endif // SIMULATEUR_H
