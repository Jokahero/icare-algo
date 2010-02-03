#ifndef WINDOW_H
#define WINDOW_H

#include <QtGui/QMainWindow>

#include "GUI_global.h"

#include "apropos.h"
#include "textedit.h"
#include "preferences.h"
#include "widgetplugins.h"
#include "../ExpressionsMathematiques/mathexp.h"

class QMenuBar;
class QMenu;
class QAction;
class QIcon;
class QToolBar;
class QFile;
class QStatusBar;
class QString;

/*! \brief Fenêtre principale
  */
class Window : public QMainWindow {
    Q_OBJECT

public:
    Window();

private:
    TextEdit *m_zoneTexte;

    QMenuBar *m_barreMenu;

    QMenu *m_mainMenu;
    QAction *m_ouvrir;
    QAction *m_enregistrer;
    QAction *m_imprimer;
    QAction *m_quitter;

    QMenu *m_menuAnalyse;
    QAction *m_testSyntaxe;
    QAction *m_testSemantique;
    QAction *m_testComplet;
    QAction *m_executer;

    QMenu *m_menuOptions;
    QAction *m_plugins;
    QAction *m_preferences;

    QMenu *m_help;
    QAction *m_aPropos;

    Apropos *m_fenApropos;
    Preferences *m_pref;
    WidgetPlugins *m_wPlugins;

    QIcon m_icone;

    QToolBar *m_barreOutilsTests;
    QToolBar *m_barreOutilsFichier;


    QFile *m_fichier;

    QStatusBar* m_statusBar;

public slots:
    void erreurMath(MathExp::erreur);

    void analyseSyntaxique();

    void analyseSemantique();

    void execution();

    void afficherApropos();

    void ouvrirFichier();

    void ouvrirFichier(QString pNomFichier);

    void afficherPreferences();

    void afficherMenuPlugins();

    void enregistrerFichier();

    void imprimerFichier();

    void quitter();

    void showMessage(const QString& pMessage, int pTimeout = 0);

    void rechargerPreferences();

    TextEdit* getZoneTexte();

signals:
    void lancerAnalyseSyntaxique(QFile*);
    void lancerAnalyseSemantique();
    void executer(QFile*);
    void reloadSettings();
};
#endif // WINDOW_H
