#include "simulateur.h"

std::string Simulateur::ERROR_BUFFER_LENGTH = "Erreur taille buffer";
std::string Simulateur::ERROR_BAD_START_STATE = "Erreur etat depart indefini";
std::string Simulateur::ERROR_NO_INIT = "Simulateur non initialisé";


Simulateur::Simulateur(const Automate* a, const Etat* dep, unsigned int buffer):myAutomat(a),depart(dep),nbMaxEtats(buffer)
{
    etats = new Etat*[nbMaxEtats];
    for(unsigned int i(0); i<nbMaxEtats;i++) etats[i] = nullptr;
    rang = 0;
}


Simulateur::~Simulateur(){
    for(unsigned int i(0);i<nbMaxEtats;i++){
        if(etats[i]!=nullptr)
        delete etats[i];
    }
    delete depart;
    if(myAutomat != nullptr) delete myAutomat;
}


Simulateur::Simulateur(const Simulateur& s){
    myAutomat = s.myAutomat->copy();
    nbMaxEtats = s.nbMaxEtats;
    rang = s.rang;
    etats = new Etat*[nbMaxEtats];
    for(unsigned int i(0); i<nbMaxEtats;i++) etats[i] = s.etats[i];
}


Simulateur& Simulateur::operator=(const Simulateur& s){
    myAutomat = s.myAutomat->copy();
    nbMaxEtats = s.nbMaxEtats;
    rang = s.rang;
    etats = new Etat*[nbMaxEtats];
    for(unsigned int i(0); i<nbMaxEtats;i++) etats[i] = s.etats[i];
    return *this;
}


void Simulateur::build(unsigned int c){
    if (c >= nbMaxEtats) throw SimulateurException("Simulateur1D::build ->" + ERROR_BUFFER_LENGTH);
    if (etats[c] != nullptr) delete etats[c];
    etats[c] = new Etat(depart->getNbRows(),depart->getNbCols());
}


void Simulateur::setEtatDepart(const Etat& e){
    Etat* noconstdepart = const_cast<Etat*>(depart);
    *noconstdepart = e;
    reset();
}


void Simulateur::run(unsigned int nbSteps){
    for (unsigned int i = 0; i < nbSteps; i++)
        next();
}


void Simulateur::next(){
    if (depart==nullptr) throw SimulateurException("Simulateur1D::next->"+ERROR_BAD_START_STATE);
    rang++;
    build(rang%nbMaxEtats);
    myAutomat->applyTransition(etats[(rang - 1) % nbMaxEtats], etats[rang%nbMaxEtats]);
}


const Etat& Simulateur::dernier() const{
    if(etats[rang%nbMaxEtats] != nullptr)
    return *etats[rang%nbMaxEtats];
    else return *depart;
}


void Simulateur::reset(){
    if (depart==nullptr) throw SimulateurException("Simulateur1D::reset->"+ERROR_BAD_START_STATE);
    build(0);
    *etats[0] = *depart;
    rang = 0;
}


