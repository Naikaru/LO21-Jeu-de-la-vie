#ifndef AUTOMATE_H
#define AUTOMATE_H

#include <string>
#include <vector>
#include <iostream>

class AutomateException {
	private:
		std::string info;
	
	public:
		AutomateException(const std::string& message) : info(message) {}
		std::string getInfo() const { return info; }
};

/*
class Cellular {
	short int life;
};
*/

/////////////////////////////////////////////////////////////////////////

/*
class Etat 
{
	std::vector< std::vector<int> > grid;
	//std::vector< std::vector<Cellular> > grid(nbRows, std::vector<Cellular>(nbCols, 0));

public:
	Etat(): {}

};
*/


class Etat1D //: public Etat
{
    std::vector< std::vector<int> > grid;
    unsigned short int nbCols;

public:
	// ? à ajouter dans la classe mère comme des méthodes virtuelles.
    Etat1D(): nbCols(0){ grid.push_back(std::vector<int>(0)); } // à redéfinir
	Etat1D(unsigned short int n); 
    ~Etat1D() {} // for(unsigned int i=0; i<nbCols; ++i) delete grid[0][i];
	Etat1D(const Etat1D& e);
	Etat1D& operator=(const Etat1D& e);

    void setCellule(unsigned short int i, unsigned int val);
	int getCellule(unsigned short int i) const;
	unsigned short int getNbCols() const { return nbCols; }
};


/////////////////////////////////////////////////////////////////////////
/*
class MainAutomate 
{
private:

public:
	MainAutomate(): {}
	virtual void applyTransition();
	// voir les templates
};

*/
// Fonctions de transformation nombre binaire (string) <-> nombre décimal (short int)

short unsigned int NumBitToNum(const std::string& num);
std::string NumToNumBit(short unsigned int num);


// Automate Cellule de dimension 1 

class Automate1D //: public MainAutomate
{
private:
    unsigned short int numero;
    std::string numeroBit;

public:
    Automate1D(unsigned short int num);
    Automate1D(const std::string& num);
    ~Automate1D(){}
    Automate1D(const Automate1D& a);
    Automate1D& operator=(const Automate1D& a);

    unsigned short int getNumero() const { return numero; }
    const std::string& getNumeroBit() const { return numeroBit; }
    void applyTransition(const Etat1D& dep, Etat1D& dest) const;
    // template<typename Type> applyTransition(const Type& dep, Type& dest) const;
};


class Simulateur1D
{
	const Automate1D& automate;
    
    Etat1D** etats;
    const Etat1D* depart;
	unsigned int nbMaxEtats;
    unsigned int rang;

public:
	Simulateur1D(const Automate1D& a, unsigned int buffer = 2);
	Simulateur1D(const Automate1D& a, const Etat1D& dep, unsigned int buffer = 2);
    Simulateur1D(const Simulateur1D& s);
    Simulateur1D& operator=(const Simulateur1D& s);
    ~Simulateur1D();

    void build(unsigned int c);
	void setEtatDepart(const Etat1D& e);
	void run(unsigned int nbSteps); // génère les n prochains états
	void next(); // génère le prochain état
	const Etat1D& dernier() const;
	unsigned int getRangDernier() const { return rang; }
	void reset(); // revenir à l'état de départ
};


/**********************************************
 *********       MODE 2D      *****************
 **********************************************/


class Etat2D // : public Etat
{
    unsigned short int nbCols;
    unsigned short int nbRows;
    std::vector< std::vector<int> > grid;
    // attributs grid et nbCols à placer dans la classe mère

public:
    //Etat2D() {}
    Etat2D(unsigned short int m=1, unsigned short int n=1);
    ~Etat2D() {}
    Etat2D(const Etat2D& e);
    Etat2D& operator=(const Etat2D& e);

    void setCellule(unsigned short int i, unsigned short int j, unsigned int val);
    unsigned short int getCellule(unsigned short int i, unsigned short int j) const;
    unsigned short int getNbRows() const { return nbRows; }
    unsigned short int getNbCols() const { return nbCols; }
};

unsigned short int countNeighbours(const Etat2D& e, unsigned short int row, unsigned short int col);

class Automate2D // public MainAutomate
{
private:
    unsigned short int minNeighbours;
    unsigned short int maxNeighbours;
    unsigned short int exactNeighbours;

public:
    Automate2D(unsigned short int min=2, unsigned short int max=3, unsigned short int exact=3);
    ~Automate2D() {}
    Automate2D(const Automate2D& a);
    //Automate2D& operator=(const Automate2D& a);

    unsigned short int getMinNeighbours() const { return minNeighbours; }
    unsigned short int getMaxNeighbours() const { return maxNeighbours; }
    unsigned short int getExactNeighbours() const { return exactNeighbours; }
    void applyTransition(const Etat2D& dep, Etat2D& dest) const;
    // template<typename Type> applyTransition(const Type& dep, Type& dest) const;
};


template<class A, class E>
class Simulateur
{
  const A& automate;
  E** etats;
  const E* depart;
  unsigned int nbMaxEtats;
  unsigned int rang;

  Simulateur();
  Simulateur(const Automate2D& a, const Etat2D& dep, unsigned int buffer = 2);
  Simulateur(const Simulateur2D& s);
  // Constructeur de recopie
  Simulateur2D& operator=(const Simulateur2D& s);
  ~Simulateur2D();

  virtual void build(unsigned int c) = 0;
  virtual void setEtatDepart(const E& e) = 0;
  virtual void run(unsigned int nbSteps) = 0; // génère les n prochains états
  virtual void next() = 0; // génère le prochain état
  virtual const E& dernier() const = 0;
  unsigned int getRangDernier() const { return rang; }
  virtual void reset() = 0; // revenir à l'état de départ
};


class Simulateur2D : public Simulateur<Automate2D, Etat2D>
{
/*
    const Automate2D& automate;

    Etat2D** etats;
    const Etat2D* depart;
    unsigned int nbMaxEtats;
    unsigned int rang;
*/
public:
    virtual Simulateur2D(const Automate2D& a, unsigned int buffer = 2);
    Simulateur2D(const Automate2D& a, const Etat2D& dep, unsigned int buffer = 2);
    Simulateur2D(const Simulateur2D& s);
    // Constructeur de recopie
    Simulateur2D& operator=(const Simulateur2D& s);
    ~Simulateur2D();

    virtual void build(unsigned int c);
    virtual void setEtatDepart(const Etat2D& e);
    virtual void run(unsigned int nbSteps); // génère les n prochains états
    virtual void next(); // génère le prochain état
    virtual const Etat2D& dernier() const;
    //virtual unsigned int getRangDernier() const { return rang; }
    virtual void reset(); // revenir à l'état de départ
};




#endif // AUTOMATE_H
