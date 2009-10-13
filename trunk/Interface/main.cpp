#include <QtGui>

#include "window.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Window fenetre;
    fenetre.show();

    return a.exec();
}
