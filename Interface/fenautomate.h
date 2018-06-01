#ifndef FENAUTOMATE_H
#define FENAUTOMATE_H
#include <QMainWindow>
#include <QPushButton>

class fenAutomate : public QMainWindow
{
public:
    fenAutomate();
    fenAutomate(QString nom);
private:
    QPushButton* btPlay,btReculer,btAvancer;
};

#endif // FENAUTOMATE_H
