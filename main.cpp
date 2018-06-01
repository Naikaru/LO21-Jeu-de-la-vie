#include <QApplication>
#include "autocell1D.h"
#include "autocell2D.h"

using namespace std;

int main(int argc, char* argv[]) {

    QApplication app(argc, argv);

    // MainWindows fenetre;
    SecondMainWindow fenetre;


    fenetre.show();
    return app.exec();


  /*
    Automate2D a(2,3,3);
    Etat2D e(9,9);
    e.setCellule(4,3,1);
    e.setCellule(4,4,1);
    e.setCellule(4,5,1);
    e.setCellule(4,6,1);

    Simulateur2D s(a, e);



    for (unsigned int i(0); i<9; ++i)
    {
        for (unsigned int j(0); j<9; ++j)
        {
            cout << " " << e.getCellule(i,j) << " ";
        }
        cout << "\n";
    }

    for (unsigned int k(0); k<3; ++k)
    {
        cout << endl << endl << endl;
        s.next();
        //cout << " generation numero : " << k+1 << endl;
        const Etat2D& tmpEtat = s.dernier();
        for (unsigned int i(0); i<9; ++i)
        {
            for (unsigned int j(0); j<9; ++j)
            {
                cout << " " << tmpEtat.getCellule(i,j) << " ";
            }
            cout << "\n";
        }
    }


    return 0;
*/
}
