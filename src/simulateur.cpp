#include "headers/simulateur.h"

std::string Simulateur::ERROR_BUFFER_LENGTH = "Erreur taille buffer";
std::string Simulateur::ERROR_BAD_START_STATE = "Erreur etat depart indefini";
std::string Simulateur::ERROR_NO_INIT = "Simulateur non initialisé";


Simulateur::Simulateur(/*const */Automate* a, const Etat* dep, unsigned int buffer):
    myAutomat(a),depart(dep),nbMaxEtats(buffer), rang(0)
{
    etats = new Etat*[nbMaxEtats];
    for(unsigned int i(0); i<nbMaxEtats;i++) etats[i] = nullptr;
    etats[0] = new Etat(*dep);
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
    myAutomat->applyTransition(*etats[(rang - 1) % nbMaxEtats], *etats[rang%nbMaxEtats]);
}


const Etat& Simulateur::dernier() const{
    if(etats[rang%nbMaxEtats] != nullptr)
        return *etats[rang%nbMaxEtats];
    else
        return *depart;
}


void Simulateur::reset(){
    if (depart==nullptr) throw SimulateurException("Simulateur1D::reset->"+ERROR_BAD_START_STATE);
    build(0);
    *etats[0] = *depart;
    rang = 0;
}

bool Simulateur::stepBack(){
    if(rang > 0 && etats[(rang-1)%nbMaxEtats] != nullptr && etats[(rang)%nbMaxEtats] != nullptr){
        delete etats[rang%nbMaxEtats];
        etats[rang%nbMaxEtats] = nullptr;
        rang--;
        return true;
    }
    return false;
}

void Simulateur::updateBufferSize(int newSize){
    Etat** newStates = new Etat*[newSize];
    for (unsigned int i(0); i<newSize; ++i) newStates[i] = nullptr;

    if(nbMaxEtats < newSize){
        if(rang < nbMaxEtats){  // Moins d'états générés que la taille du buffer
            for (unsigned int i(0); i<=rang; ++i)
                newStates[i] = etats[i];
        }else{                  // Plus d'états générés que la taille du buffer, on a alors forcément fait un cycle.
            for (unsigned int i(0); i<nbMaxEtats; ++i)
                newStates[i] = etats[(rang+i+1)%nbMaxEtats];
            rang = nbMaxEtats - 1;
        }
    }
    else if(nbMaxEtats > newSize){
        // On enregistre les newSize derniers états
        if(rang%nbMaxEtats > newSize){
            for (unsigned int i(0); i<newSize; ++i)
                newStates[i] = etats[(rang%nbMaxEtats)-newSize+1+i];
            rang = newSize - 1;
        }
        else if(rang < newSize){
            for (unsigned int i(0); i<newSize; ++i)
                newStates[i] = etats[i];
        }
        else if(rang%nbMaxEtats < newSize){
            for (unsigned int i(0); i<newSize; ++i)
                newStates[i] = etats[(nbMaxEtats - (rang%nbMaxEtats) + i)%nbMaxEtats];
            rang = newSize - 1;
        }
    }
    else{
        return;
    }

    Etat** old = etats;
    delete[] old;
    etats = newStates;
    nbMaxEtats = newSize;
}


QJsonObject& Simulateur::toJson() const{
    QJsonObject* myData = new QJsonObject;
    (*myData)["automate"] = myAutomat->toJson();
    (*myData)["depart"] = depart->toJson();
    QJsonArray monTab;
    for(int unsigned i = 0;i<nbMaxEtats;i++)
            if(etats[i] != nullptr)
                monTab.append(etats[i]->toJson());
     (*myData)["buffer"] = monTab;
     (*myData)["nbMaxEtats"] = (int)nbMaxEtats;
     (*myData)["rang"] = (int)rang;
    return *myData;
}

Simulateur::Simulateur(Automate* myauto, const QJsonObject& myData):myAutomat(myauto){
    if(myData.contains("depart") && myData["depart"].isObject()) depart = new Etat(myData["depart"].toObject());
    if(myData.contains("nbMaxEtats")) nbMaxEtats = myData["nbMaxEtats"].toInt();
    if(myData.contains("rang")) rang = myData["rang"].toInt();
    etats = new Etat*[nbMaxEtats];
    for(unsigned int i(0); i<nbMaxEtats;i++) etats[i] = nullptr;
    if(myData.contains("buffer") && myData["buffer"].isArray()){
      QJsonArray mesEtats = myData["buffer"].toArray();
      for(unsigned int i(0); i<mesEtats.size();i++){ etats[i] = new Etat(mesEtats[i].toObject());}
    }
}
