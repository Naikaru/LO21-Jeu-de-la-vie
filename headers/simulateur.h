#ifndef SIMULATEUR_H
#define SIMULATEUR_H

#include "headers/automate.h"
#include "headers/etat.h"
#include <QMessageBox>

//   TODO  //
//
//
//   FIN TODO  //

// Classe qui correspond aux exceptions de simulateur

/**
 * @brief The SimulateurException class permet de gérer les exceptions liées à la classe Simulateur
 */
class SimulateurException
{
    std::string info;
public:
    SimulateurException(const std::string& message) : info(message) {}
    std::string getInfo() const { return info; }
};


/**
 * @brief The Simulateur class Permet d'appliquer les règles de notre Automate Cellulaire sur différents Etat,
 *          Et ainsi visionner la succession de générations.
 */
class Simulateur
{
    /**
     * @brief ERROR_BUFFER_LENGTH Erreur générique liée à une erreur dans la taille du buffer.
     */
    static std::string ERROR_BUFFER_LENGTH;
    /**
     * @brief ERROR_BAD_START_STATE Erreur générique liée à l'Etat de départ du simulateur.
     */
    static std::string ERROR_BAD_START_STATE;

    static std::string ERROR_NO_INIT;

    /**
     * @brief myAutomat est un pointeur sur la classe Automate. Permet ainsi de mettre en oeuvre le polymorphisme
     *      grâce à la redéfinition des méthodes par les classes filles de Automate, et ainsi n'avoir qu'un
     *      simulateur quel que soit l'Automate Cellulaire choisi.
     */
    Automate* myAutomat;

    /**
     * @brief etats est un tableau de pointeurs sur la classe Etat, permet d'enregistrer jsuqu'à nbMaxEtat.
     */
    Etat** etats;

    /**
     * @brief depart pointeur constant sur Etat permettant d'initialiser le simulateur.
     */
    const Etat* depart;

    /**
     * @brief nbMaxEtats Le nombre d'Etat que l'on peut sauvegarder
     */
    unsigned int nbMaxEtats;

    /**
     * @brief rang L'indice du dernier Etat sauvegardé dans etats
     */
    unsigned int rang;

public:

    Simulateur(/*const*/ Automate* a, const Etat* dep, unsigned int buffer = 2);
    Simulateur(const Simulateur& s);
    Simulateur& operator=(const Simulateur& s);
     ~Simulateur();

    /**
      * @brief build permet de créer l'Etat [c] à partir de l'Etat de depart.
      *         Particulièrement pour l'initialisation de etats
      * @param c l'indice de l'Etat que l'on veut créer
      */
     void build(unsigned int c);

     /**
      * @brief setAlive : l'element dans la case (r,c) est mis en vie en utilisant la définition de "en vie" de l'automate.
      *         Réservé aux automates binaires comme le jeu de la vie
      * @param r indice de ligne
      * @param c indice de colonne
      */
     void setAlive(unsigned int r, unsigned int c){
         if(etats == nullptr || etats[rang%nbMaxEtats]==nullptr) throw SimulateurException("Simulateur::setAlive"+ERROR_NO_INIT);
         myAutomat->setAlive(r,c,getInitialState()); }

     /**
      * @brief setDead : l'element dans la case (r,c) est tué, en utilisant la définition. de l'automate.
      * @param r indice de ligne
      * @param c indice de colonne
      */
     void setDead(unsigned int r, unsigned int c){
         if(etats == nullptr || etats[rang%nbMaxEtats]==nullptr) throw SimulateurException("Simulateur::setDead"+ERROR_NO_INIT);
         myAutomat->setDead(r,c,getInitialState()); }

     /**
      * @brief isAlive renvoie vrai si l'element dans la case (R,C) est en vie, en utilisant la def de l'automate
      * @param r indice de colonne
      * @param c indice de ligne
      * @return myAutomte->isAlive(r,c, Etat)
      */
     bool isAlive(unsigned int r, unsigned int c){
         if(etats == nullptr || etats[rang%nbMaxEtats]==nullptr) throw SimulateurException("Simulateur::isAlive"+ERROR_NO_INIT);
         return myAutomat->isAlive(r,c,getInitialState()); }

     /**
      * @brief changeStatus Permet à l'utilisateur de changer la valeur d'une cellule,
      *         utilisant la redéfinition de la fonction changeStatus de l'automate.
      *         Un changement spontanné de l'etat entraine une réinitialisation du simulateur,
      *         d'où l'action de changeStatus sur depart
      * @param r indice de ligne
      * @param c indice de colonne
      */
     void changeStatus(unsigned int r, unsigned int c) {
         if(etats == nullptr || etats[rang%nbMaxEtats]==nullptr) throw SimulateurException("Simulateur::changeStatus"+ERROR_NO_INIT);
         myAutomat->changeStatus(r,c,getInitialState()); }

     /**
      * @brief addCol Permet à l'utilisateur d'ajouter une colonne à la grille de Etat.
      *        Méthode effectuée sur depart, car chaque changement spontanné de l'utilisateur sur la grille
      *        entraine un reset de la simulation
      */
     void addCol(){
         getInitialState()->addCols(1); // Méthode de Etat
     }

     /**
      * @brief redim Permet à l'utilisateur de choisir les dimensions de la grille de Etat.
      *         Méthode effectuée sur depart, car chaque changement spontanné de l'utilisateur sur la grille
      *        entraine un reset de la simulation
      * @param i le nouveau nombre de lignes de la grille
      * @param j le nouveau nombre de colonnes de la grile
      */
     void redim(unsigned int i, unsigned int j){
         getInitialState()->redimGrid(i,j); // Méthode de Etat
     }

     /**
      * @brief getAutomate Permet un accès en écriture de l'Automate.
      * @return myAutomat, le pointeur sur l'automate cellulaire que l'on manipule
      */
     Automate* getAutomate(){ return myAutomat;}

     /**
      * @brief setEtatDepart Permet d'initialiser l'Etat depart avec e passé en paramètre
      * @param e l'Etat qui sert à l'initialisation de l'attribut depart
      */
     void setEtatDepart(const Etat& e); // Définit l'état de départ sur l'etat passé en param

     /**
      * @brief run génère les n prochaines Etats selon les règles définies par l'automate
      * @param nbSteps Le nombre de génération à passer
      */
     void run(unsigned int nbSteps);

     /**
      * @brief next Génère le prochain Etat selon les règles définies par l'automate
      */
     void next();

     /**
      * @brief stepBack Permet un retour à l'état précédent si cela est possible
      * @return true si le retour est effectué, false sinon
      */
     bool stepBack();

     /**
      * @brief dernier Renvoie le denier etat généré par le simulateur
      * @return une référence constante sur le dernier etat généré : *etats[rang],
      */
     const Etat& dernier() const;

     /**
      * @brief getRangDernier Accesseur en lecture de l'attribut rang :  Permet de connaître à quel rang est le buffer
      * @return Le rang du dernier état généré
      */
     unsigned int getRangDernier() const { return rang; }

     /**
      * @brief getRangDernier Accesseur en écriture de l'attribut rang : Permet de modifier le rang du buffer
      * @return Le rang du dernier état généré
      */
     unsigned int getRangDernier() { return rang; }

     /**
      * @brief reset Permet une réinitialisation du simulateur avec l'Etat depart. (rang revient donc à 0, et on reconstruit etats[0])
      */
     void reset(); // revenir à l'état de départ

     /**
      * @brief getInitialState Accesseur en écriture de l'attribut depart grâce à un const_cast
      * @return Un pointeur sur depart
      */
     Etat* getInitialState(){return const_cast<Etat*>(depart);} // retourne l'etat initial du simulateur (avec possibilité de le modifier)


};
#endif // SIMULATEUR_H
