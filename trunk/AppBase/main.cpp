#include <QtCore/QCoreApplication>
#include "../Interface/window.h"
#include "../ExpressionsMathematiques/mathexp.h"
#include "../Interface/gestionnaireplugins.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MathExp *math = new MathExp();
    QString locale = QLocale::system().name().section('_', 0, 0);

    QTranslator translator;
    translator.load(QString("icare_") + locale);
    a.installTranslator(&translator);

    translator.load(QString("qt_") + locale, QLibraryInfo::location(QLibraryInfo::TranslationsPath));
    a.installTranslator(&translator);

    GestionnairePlugins g;
    bool b = g.chargerPlugin("WidgetExec");
    if (b) {
        qDebug() << "Plugin chargé avec succès.";
        g.getPlugin("WidgetExec")->getWidget()->show();
    }
    else
        qDebug() << "Erreur au chargement du plugin.";

    Window *fenetre = new Window();

    QObject::connect(math, SIGNAL(erreur(int)), fenetre, SLOT(erreurMath(int)));

    fenetre->show();

    return a.exec();
}
