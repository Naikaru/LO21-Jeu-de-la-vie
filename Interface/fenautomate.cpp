#include "fenautomate.h"

fenAutomate::fenAutomate()
{
    setWindowIcon(QIcon(":/virus.png"));
    setWindowTitle("Automate anonyme");
    setMinimumSize(500,500);

}
fenAutomate::fenAutomate(QString nom)
{
    setWindowIcon(QIcon(":/virus.png"));
    setWindowTitle("Automate : " + nom);
    setMinimumSize(500,500);

}
