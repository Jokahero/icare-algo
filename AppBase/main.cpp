#include "../Interface/window.h"
#include "../Interface/gestionnaireplugins.h"
#include "../Analyse/analyse.h"
#include "../Analyse/glossaire.h"

#include <QtCore/QDebug>
#include <QtCore/QLibraryInfo>
#include <QtCore/QLocale>
#include <QtCore/QObject>
#include <QtCore/QSettings>
#include <QtCore/QTextCodec>
#include <QtCore/QTranslator>
#include <QtGui/QApplication>
#include <QtGui/QMenuBar>
#include <QtGui/QPixmap>
#include <QtGui/QSplashScreen>

/*! \brief Point d'entrée. Charge tous les modules et plugins et le connecte.

  \todo Faire une image pour le splashcreen
  \param argc Nombre d'arguments
  \param argv Arguments
  \return Code de retour système
*/
int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    QPixmap p(200, 100);
    p.fill();
    QSplashScreen* sp = new QSplashScreen(p, Qt::SplashScreen);
    sp->show();
    a.processEvents();

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
    if (translator.load(QString("qt_") + locale, QLibraryInfo::location(QLibraryInfo::TranslationsPath)))
        a.installTranslator(&translator);
    else {
        translator.load(QString("qt_") + locale);
        a.installTranslator(&translator);
    }

    sp->showMessage(QObject::tr("Chargement des modules…"));
    Analyse *analyse = Analyse::getInstance();
    Window *fenetre = new Window();

    sp->showMessage(QObject::tr("Chargement des plugins…"));
    a.processEvents();

    GestionnairePlugins *g = fenetre->getWPlugins()->getGestionnairePlugins();
    QList<PluginInterface*> liste = g->getListePluginsDispo();

    for (int i = 0; i < liste.length(); i++)
        if (settings.value("Plugins/" + liste.at(i)->getNom() + "/Actif", true).toBool()) {
        g->chargerPlugin(liste.at(i)->getNom());
        if (g->getPlugin(liste.at(i)->getNom())->getDockWidget() != 0) {
            fenetre->addDockWidget((Qt::DockWidgetArea)settings.value(QString(liste.at(i)->getNom() + "pos"), Qt::BottomDockWidgetArea).toInt(), g->getPlugin(liste.at(i)->getNom())->getDockWidget());
            g->getPlugin(liste.at(i)->getNom())->getDockWidget()->setFloating(settings.value(QString(liste.at(i)->getNom() + "floating"), false).toBool());
        }
        if (g->getPlugin(liste.at(i)->getNom())->getMenu() != 0) {
            fenetre->getMenuBar()->addMenu(g->getPlugin(liste.at(i)->getNom())->getMenu());
        }
    }

    sp->showMessage(QObject::tr("Établissement des liens entre les modules…"));
    a.processEvents();

    // Connects des plugins
    for (int i = 0; i < g->getListePlugins().size(); i++) {
        QObject::connect(analyse->getGlossaire(), SIGNAL(variableAjoutee(QString, QString, QString)), g->getListePlugins().at(i), SLOT(variableAjoutee(QString, QString, QString)));
        QObject::connect(analyse->getGlossaire(), SIGNAL(variableModifiee(QString, QString)), g->getListePlugins().at(i), SLOT(variableModifiee(QString, QString)));
        QObject::connect(analyse->getGlossaire(), SIGNAL(sigReinit()), g->getListePlugins().at(i), SLOT(reinitialisationGlossaire()));
        QObject::connect(analyse, SIGNAL(sigErreur(Analyse::erreur, int)), g->getListePlugins().at(i), SLOT(erreurAnalyse(Analyse::erreur, int)));
        QObject::connect(analyse, SIGNAL(sigErreurMathematique(MathExp::erreur, int)), g->getListePlugins().at(i), SLOT(erreurMathematique(MathExp::erreur, int)));
        QObject::connect(analyse, SIGNAL(sigErreurLogique(ExpressionLogique::erreur, int)), g->getListePlugins().at(i), SLOT(erreurLogique(ExpressionLogique::erreur, int)));
        QObject::connect(fenetre, SIGNAL(lancerAnalyseSyntaxique(QFile*)), g->getListePlugins().at(i), SLOT(lancerAnalyse(QFile*)));
        QObject::connect(fenetre, SIGNAL(executer(bool)), g->getListePlugins().at(i), SLOT(lancerExecution()));
        QObject::connect(analyse, SIGNAL(sigAfficher(QString)), g->getListePlugins().at(i), SLOT(afficher(QString)));
        QObject::connect(g->getListePlugins().at(i), SIGNAL(changementLigne(int)), fenetre, SLOT(changementLigne(int)));
        QObject::connect(analyse, SIGNAL(analyseSyntaxiqueTerminee(bool)), g->getListePlugins().at(i), SLOT(analyseSyntaxiqueTerminee(bool)));
        QObject::connect(analyse, SIGNAL(analyseSemantiqueTerminee(bool)), g->getListePlugins().at(i), SLOT(analyseSemantiqueTerminee(bool)));
        QObject::connect(g->getListePlugins().at(i), SIGNAL(ajouterTexte(QString)), fenetre, SIGNAL(ajouterTexte(QString)));
    }

    // Connects des modules
    QObject::connect(fenetre, SIGNAL(lancerAnalyseSyntaxique(QFile*)), analyse, SLOT(lancerAnalyseSyntaxique(QFile*)));
    QObject::connect(fenetre, SIGNAL(lancerAnalyseSemantique()), analyse, SLOT(lancerAnalyseSemantique()));
    QObject::connect(fenetre, SIGNAL(executer(bool)), analyse, SLOT(lancerExecution(bool)));
    QObject::connect(fenetre, SIGNAL(execPas()), analyse, SIGNAL(execPas()));
    QObject::connect(fenetre, SIGNAL(execStop()), analyse, SIGNAL(execStop()));
    QObject::connect(fenetre, SIGNAL(reloadSettings()), fenetre->getZoneTexte(), SLOT(loadSettings()));
    QObject::connect(qApp, SIGNAL(aboutToQuit()), analyse, SLOT(destroy()));
    QObject::connect(analyse, SIGNAL(sigSaisir(bool)), fenetre, SLOT(afficherFenSaisie(bool)));
    QObject::connect(analyse, SIGNAL(analyseSyntaxiqueTerminee(bool)), fenetre, SLOT(analyseSyntaxiqueTerminee(bool)));
    QObject::connect(analyse, SIGNAL(analyseSemantiqueTerminee(bool)), fenetre, SLOT(analyseSemantiqueTerminee(bool)));
    QObject::connect(analyse, SIGNAL(executionTerminee()), fenetre, SLOT(executionTerminee()));
    QObject::connect(analyse, SIGNAL(changementLigne(int)), fenetre, SLOT(changementLigne(int)));
    QObject::connect(fenetre, SIGNAL(sigSaisie(QString)), analyse, SLOT(transmettreSaisie(QString)));

    // Chargement d'un fichier passé en paramètre
    if (argc > 1) {
        sp->showMessage(QObject::tr("Chargement du fichier…"));
        a.processEvents();
        fenetre->ouvrirFichier(argv[1]);
    }

    sp->showMessage(QObject::tr("Chargement de l'interface…"));
    a.processEvents();

    // Affichage de la fenêtre
    if (settings.value("Fenetre/Max", true).toBool()) {
        fenetre->showMaximized();
    } else {
        fenetre->show();
    }
    sp->finish(fenetre);

    return a.exec();
}
