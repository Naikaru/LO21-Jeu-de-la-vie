#ifndef FENAUTOMATE1D_H
#define FENAUTOMATE1D_H

#include <QWidget>
#include <QMainWindow>
#include <QPushButton>
#include "automate.h"
#include "headers/etat.h"
#include "headers/simulateur.h"
#include <cstdlib>
#include <ctime>
#include <QLabel>
#include <QSpinBox>
#include <QLineEdit>
#include <QIntValidator>
#include <QTableView>
#include <QTableWidget>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QTableWidgetItem>
#include <QSize>
#include <QTimer>
#include <QSlider>
#include "headers/fenautomate.h"
#include "headers/automate1d.h"


// Classe qui correspond à la fenêtre d'un automate 1D
class fenAutomate1D : public fenAutomate{
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
    QTableWidget* maGrid;

    unsigned int dimension = 20;
public:
    fenAutomate1D(QString nom, Simulateur* s);
    virtual ~fenAutomate1D(){}
    virtual void avancer();
    virtual void reculer();
    virtual void initialize();
    void addStep();
    void adaptGridSize();
    void resizeGrid();
    void refreshGrid();
    void cellChange(unsigned int i, unsigned int j);


public slots:
    void synchronizeNumToNumBit(int n);
    void synchronizeNumBitToNum(const QString& n);

    //void simulate();

    void slotGridClick(QModelIndex j); // Slop appellé quand on clique sur une case, les coordonees sont passés en argument par le signal
};



#endif // FENAUTOMATE1D_H
