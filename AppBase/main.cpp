#include <QtCore/QCoreApplication>
#include "../Interface/window.h"
#include "../ExpressionsMathematiques/mathexp.h"
#include "../Interface/gestionnaireplugins.h"
#include "../Analyse/analysesyntaxique.h"

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

    AnalyseSyntaxique *analyseSyntaxique = new AnalyseSyntaxique(fenetre->m_widgetPrincipal->m_zoneTexte);

    GestionnairePlugins g;
    bool b = g.chargerPlugin("WidgetExec");
    if (b) {
        qDebug() << "Plugin WidgetExec chargé avec succès.";
        fenetre->addDockWidget(Qt::BottomDockWidgetArea, g.getPlugin("WidgetExec")->getDockWidget());
    }
    else
        qDebug() << "Erreur au chargement du plugin WidgetExec.";

    b = g.chargerPlugin("WidgetGlossaire");
    if (b) {
        qDebug() << "Plugin WidgetGlossaire chargé avec succès.";
        fenetre->addDockWidget(Qt::RightDockWidgetArea, g.getPlugin("WidgetGlossaire")->getDockWidget());
    }
    else
        qDebug() << "Erreur au chargement du plugin WidgetGlossaire.";

    // Chargement d'un fichier passé en paramètre
    if (argc > 1) {
        fenetre->m_widgetPrincipal->ouvrirFichier(argv[1]);
        qDebug() << argv[1];
    }

    QObject::connect(math, SIGNAL(erreur(int)), fenetre, SLOT(erreurMath(int)));
    QObject::connect(fenetre->m_testSyntaxe, SIGNAL(triggered()), analyseSyntaxique, SLOT(lancer()));
    //QObject::connect(AnalyseSyntaxique->m_glossaire, SIGNAL(erreur(int)), fenetre, SLOT(erreurAnalyse(int)));

    // Connects des plugins
    for (int i = 0; i < g.getListePlugins().size(); i++) {
        QObject::connect(analyseSyntaxique->getGlossaire(), SIGNAL(variableAjoutee(QString, QString, QString)), g.getListePlugins().at(i), SLOT(variableAjoutee(QString, QString, QString)));
        QObject::connect(analyseSyntaxique->getGlossaire(), SIGNAL(variableModifiee(QString, QString)), g.getListePlugins().at(i), SLOT(variableModifiee(QString, QString)));
    }

    fenetre->showMaximized();

    return a.exec();
}
