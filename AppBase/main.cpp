#include <QtCore/QCoreApplication>
#include "../Interface/window.h"
#include "../ExpressionsMathematiques/mathexp.h"
#include "../Interface/gestionnaireplugins.h"
#include "../Analyse/analyse.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    // Réglage de l'encodage
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));

    // Application de la traduction
    QString locale = QLocale::system().name().section('_', 0, 0);
    QTranslator translator;
    // De l'application elle même
    translator.load(QString("icare_") + locale);
    a.installTranslator(&translator);
    // Et de Qt
    translator.load(QString("qt_") + locale, QLibraryInfo::location(QLibraryInfo::TranslationsPath));
    a.installTranslator(&translator);

    // Création des différents modules
    MathExp *math = new MathExp();
    Window *fenetre = new Window();
    Analyse *analyse = new Analyse();
    GestionnairePlugins g;

    // Chargement des plugins, temporaire
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
        fenetre->ouvrirFichier(argv[1]);
        qDebug() << argv[1];
    }

    // Connects des modules
    QObject::connect(math, SIGNAL(erreur(int)), fenetre, SLOT(erreurMath(int)));
    QObject::connect(fenetre, SIGNAL(analyseSyntaxique(QFile*)), analyseSyntaxique, SLOT(lancer(QFile*)));
    //QObject::connect(AnalyseSyntaxique->m_glossaire, SIGNAL(erreur(int)), fenetre, SLOT(erreurAnalyse(int)));

    // Connects des plugins
    for (int i = 0; i < g.getListePlugins().size(); i++) {
        QObject::connect(analyse->getGlossaire(), SIGNAL(variableAjoutee(QString, QString, QString)), g.getListePlugins().at(i), SLOT(variableAjoutee(QString, QString, QString)));
        QObject::connect(analyse->getGlossaire(), SIGNAL(variableModifiee(QString, QString)), g.getListePlugins().at(i), SLOT(variableModifiee(QString, QString)));
    }

    // Affichage de la fenêtre
    fenetre->showMaximized();

    return a.exec();
}
