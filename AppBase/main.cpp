#include <QtCore/QCoreApplication>

#include "../Interface/window.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Window *fenetre = new Window();
    fenetre->show();

    return a.exec();
}
