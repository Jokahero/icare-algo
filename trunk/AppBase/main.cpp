#include <QtCore/QCoreApplication>
#include "../Interface/window.h"
#include "../ExpressionsMathematiques/mathexp.h"
#include "../Interface/gestionnaireplugins.h"
#include "../Analyse/analyse.h"
#include "../Analyse/glossaire.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    QCoreApplication::setOrganizationName("IUT Blagnac");
    QCoreApplication::setOrganizationDomain("code.google.com/p/icare-algo");
    QCoreApplication::setApplicationName("Icare");
    QSettings settings;

    // Réglage de l'encodage
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));

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

    // Connects des plugins
    for (int i = 0; i < g.getListePlugins().size(); i++) {
        QObject::connect(Analyse::getInstance()->getGlossaire(), SIGNAL(variableAjoutee(QString, QString, QString)), g.getListePlugins().at(i), SLOT(variableAjoutee(QString, QString, QString)));
        QObject::connect(Analyse::getInstance()->getGlossaire(), SIGNAL(variableModifiee(QString, QString)), g.getListePlugins().at(i), SLOT(variableModifiee(QString, QString)));
        QObject::connect(Analyse::getInstance()->getGlossaire(), SIGNAL(sigReinit()), g.getListePlugins().at(i), SLOT(reinitialisationGlossaire()));
        QObject::connect(math, SIGNAL(sigErreur(MathExp::erreur)), g.getListePlugins().at(i), SLOT(erreurMathematique(MathExp::erreur)));
        QObject::connect(Analyse::getInstance(), SIGNAL(sigErreur(Analyse::erreur, int)), g.getListePlugins().at(i), SLOT(erreurAnalyse(Analyse::erreur, int)));
        QObject::connect(fenetre, SIGNAL(lancerAnalyseSyntaxique(QFile*)), g.getListePlugins().at(i), SLOT(lancerAnalyse(QFile*)));
        QObject::connect(fenetre, SIGNAL(reloadSettings()), fenetre->getZoneTexte(), SLOT(loadSettings()));
    }

    // Connects des modules
    QObject::connect(math, SIGNAL(sigErreur(MathExp::erreur)), fenetre, SLOT(erreurMath(MathExp::erreur)));
    QObject::connect(fenetre, SIGNAL(lancerAnalyseSyntaxique(QFile*)), Analyse::getInstance(), SLOT(lancerAnalyseSyntaxique(QFile*)));
    //QObject::connect(Analyse::getInstance()->getGlossaire(), SIGNAL(erreur(int)), fenetre, SLOT(erreurAnalyse(int)));

    // Affichage de la fenêtre
    if (settings.value("Maximized", false).toBool()) {
        fenetre->showMaximized();
    } else {
        fenetre->show();
    }

    return a.exec();
}
