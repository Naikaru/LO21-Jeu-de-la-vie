#include <QApplication>
#include "fenprincipale.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    FenPrincipale myFen;
    myFen.show();
    return app.exec();
}
