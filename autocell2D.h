#ifndef AUTOCELL2D_H
#define AUTOCELL2D_H

//#include "automate2D.h"
#include "automate.h"
#include <windows.h> // fonction sleep

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

class AutoCell2D : public QWidget{

    Q_OBJECT
    QLabel* labelMinNeighbours;
    QLabel* labelMaxNeighbours;
    QLabel* labelExactNeighbours;
    QLabel* labelDimensions;
    QLabel* labelRows;
    QLabel* labelCols;

	QSpinBox* numMinNeighbours;
	QSpinBox* numMaxNeighbours;
	QSpinBox* numExactNeighbours;

	QLineEdit* numRows;
	QLineEdit* numCols;

	QVBoxLayout* mainVLayout[4];
	QVBoxLayout* subVLayout[2];
	QHBoxLayout* subHLayout;
    QVBoxLayout* interface2D;
    QHBoxLayout* mainHLayout;

    QPushButton* simulation;
    QPushButton* nextGeneration;
    QTableWidget* states = nullptr;

    bool* continueGenerate;

public:
    explicit AutoCell2D(QWidget *parent = nullptr);

private slots:
    void simulate2D();
    void generate2D();
    void cellActivation2D(QModelIndex indx);

};


class SecondMainWindow : public QMainWindow
{
public:
    SecondMainWindow();
private:
    /*
    QMenu* menuFichier;
    QMenu* menuEdition;
    QMenu* menuAffichage;
    QAction* actionQuitter;
    QMenu* fichiersRecents;
    */
};



#endif // AUTOCELL2D_H
