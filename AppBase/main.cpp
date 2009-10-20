#include <QtCore/QCoreApplication>

#include "../Interface/window.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QString locale = QLocale::system().name().section('_', 0, 0);

    QTranslator translator;
    translator.load(QString("icare_") + locale);
    a.installTranslator(&translator);


    Window *fenetre = new Window();
    fenetre->show();

    return a.exec();
}
