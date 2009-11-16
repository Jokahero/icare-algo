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

    Window *fenetre = new Window();

    GestionnairePlugins g;
    bool b = g.chargerPlugin("WidgetExec");
    if (b) {
        qDebug() << "Plugin chargé avec succès.";
        fenetre->addDockWidget(Qt::BottomDockWidgetArea, g.getPlugin("WidgetExec")->getDockWidget());
    }
    else
        qDebug() << "Erreur au chargement du plugin.";

    // Chargement d'un fichier passé en paramètre
    if (argc > 1) {
        fenetre->m_widgetPrincipal->ouvrirFichier(argv[1]);
        qDebug() << argv[1];
    }

    QObject::connect(math, SIGNAL(erreur(int)), fenetre, SLOT(erreurMath(int)));

    fenetre->showMaximized();

    return a.exec();
}
