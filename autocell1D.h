#ifndef AUTOCELL1D_H
#define AUTOCELL1D_H

#include "automate.h"
#include <QMainWindow>
#include <QWidget>
#include <QSpinBox>
#include <QLineEdit>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QIntValidator>
#include <QTableWidget>
#include <QHeaderView>
#include <QPushButton>
#include <QString>
#include <QModelIndex>
#include <QAction>
#include <QMenu>
#include <QMenuBar>
#include <QMdiArea>

class AutoCell1D : public QWidget{

    Q_OBJECT
    QSpinBox* num; // numéro
    QLineEdit* numeroBit[8]; // un QLineEdit par bit
    QLabel* numl;
    QLabel* numeroBitl[8];
    QVBoxLayout* numc;
    QVBoxLayout* bitc[8];
    QHBoxLayout* numeroc;
    QIntValidator* zeroOneValidator;
    QTableWidget* depart;
    QPushButton* simulation;
    QTableWidget* states = nullptr;

    QVBoxLayout* interface;

    unsigned int dimension = 20;
    QSpinBox* nbSim; // Nombre de générations
    QHBoxLayout* simLaye;

public:
    explicit AutoCell1D(QWidget *parent = nullptr);

private slots:
    void synchronizeNumToNumBit(int n);
    void synchronizeNumBitToNum(const QString& n);
    void numberGeneration(int value);


    void simulate();
    void cellActivation(QModelIndex indx);

};


class MainWindow : public QMainWindow
{
public:
    MainWindow();
private:
    QMenu* menuFichier;
    QMenu* menuEdition;
    QMenu* menuAffichage;
    QAction* actionQuitter;
    QMenu* fichiersRecents;
};

#endif // AUTOCELL1D_H
