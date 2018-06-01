#ifndef AUTOMATE2D_H
#define AUTOMATE2D_H

#include <vector>
#include <string>


class Etat2D // : public Etat
{
	unsigned short int nbCols;
	unsigned short int nbRows;
	vector< vector<int> > grid;
	// attributs grid et nbCols dans la classe mère

public:
	Etat2D() {}
	Etat2D(unsigned short int m=1, unsigned short int n=1);
	~Etat2D() {} 
	Etat2D(const Etat2D& e);
	Etat2D& operator=(const Etat2D& e);

	void setCellule(unsigned short int i, unsigned int val);
	int getCellule(unsigned short int i) const;
	unsigned short int getNbRows() const { return nbRows; }
	unsigned short int getNbCols() const { return nbCols; }
};



unsigned short int countNeighbours(const Etat2D& e);



class Automate2D // public MainAutomate
{
private:
    unsigned short int minNeighbours;
    unsigned short int maxNeighbours;
    unsigned short int exactNeighbours;

public:
    Automate2D(unsigned short int min=3, unsigned short int max=5, unsigned short int exact=0);
    ~Automate2D(){}
    Automate2D(const Automate2D& a);
    //Automate2D& operator=(const Automate2D& a);

    unsigned short int getMinNeighbours() const { return minNeighbours; }
	unsigned short int getMaxNeighbours() const { return maxNeighbours; }
    unsigned short int getExactNeighbours() const { return exactNeighbours; }
    void applyTransition(const Etat2D& dep, Etat2D& dest) const;
    // template<typename Type> applyTransition(const Type& dep, Type& dest) const;
};




class Simulateur2D
{
	const Automate2D& automate;
    
    Etat2D** etats;
    const Etat2D* depart;
	unsigned int nbMaxEtats;
    unsigned int rang;
	//void build(unsigned int c);
    Simulateur2D(const Simulateur2D& s); 
    // Constructeur de recopie
    Simulateur2D& operator=(const Simulateur2D& s);
	~Simulateur2D();

public:
	Simulateur2D(const Automate2D& a, unsigned int buffer = 2);
	Simulateur2D(const Automate2D& a, const Etat2D& dep, unsigned int buffer = 2);
	void setEtatDepart(const Etat2D& e);
	void run(unsigned int nbSteps); // génère les n prochains états
	void next(); // génère le prochain état
	const Etat2D& dernier() const;
	unsigned int getRangDernier() const { return rang; }
	void reset(); // revenir à l'état de départ
};



#endif // AUTOMATE2D_H
