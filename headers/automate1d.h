#ifndef AUTOMATE1D_H
#define AUTOMATE1D_H

#include <string>
#include <vector>
#include <iostream>
#include "headers/etat.h"
#include "headers/automate.h"
#include "headers/fenautomate.h"
#include "headers/fenautomate1d.h"
#include "headers/abstractautomatefactory.h"

class Automate1D : public Automate
{
private:
    unsigned short int numero;
    std::string numeroBit;
    static std::string ERROR_BAD_ETAT;

public:
    Automate1D(unsigned short int num = 42);
    Automate1D(const std::string& num);
    virtual ~Automate1D()= default;
    Automate1D(const Automate1D& a);
    Automate1D& operator=(const Automate1D& a);
    virtual Automate* copy() const;
    unsigned short int getNumero() const { return numero; }
    const std::string& getNumeroBit() const { return numeroBit; }

    virtual void applyTransition(const Etat& depart, Etat& arrivee) const;
    virtual void changeStatus(unsigned int r, unsigned int c, Etat* e) const;
    virtual const QColor& colorize(int value)const;
    virtual QWidget* changeRules() const { QWidget* newRules = new QWidget(); return newRules; }

//public slots:
//    virtual void slotMinChanged(int) { return; }
//    virtual void slotMaxChanged(int) { return; }
//    virtual void makeRulesChange() { return; }

};

short unsigned int NumBitToNum(const std::string& num); // Transforme les string de 0 et de 1 en int
std::string NumToNumBit(short unsigned int num); // Transforme les int en string de 0 et 1

class Automate1DFactory : public abstractAutomateFactory{
public:
    Automate1DFactory():abstractAutomateFactory("Automate 1D"){}
    virtual fenAutomate* getfenAutomate();
    virtual ~Automate1DFactory() = default;
};
#endif // AUTOMATE1D_H
