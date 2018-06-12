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
    QSpinBox* dimCols;
public:
    fenAutomate1D(QString nom, Simulateur* s);
    virtual ~fenAutomate1D(){}
    virtual void avancer();
    virtual void reculer();
    virtual void addCols(unsigned int c=1);
    virtual void redimensionner();
    virtual void initialize();
    virtual void reinitialize();

    virtual void resizeGrid();
    virtual void refreshGrid();
    virtual void cellChange(unsigned int i, unsigned int j);

    void addStep();

public slots:
    void slotUpdateDimensions();
    void slotGridClick(QModelIndex j); // Slop appellé quand on clique sur une case, les coordonees sont passés en argument par le signal
};



#endif // FENAUTOMATE1D_H
