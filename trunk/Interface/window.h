#ifndef WINDOW_H
#define WINDOW_H

#include <QtGui/QMainWindow>

#include "GUI_global.h"

#include "apropos.h"
#include "textedit.h"
#include "preferences.h"
#include "widgetplugins.h"
#include "../Analyse/mathexp.h"

class QMenuBar;
class QMenu;
class QAction;
class QIcon;
class QToolBar;
class QFile;
class QStatusBar;
class QString;
class Recherche;

/*! \brief Fenêtre principale
  */
class Window : public QMainWindow {
    Q_OBJECT

public:
    Window();
    ~Window();

    TextEdit* getZoneTexte();

    WidgetPlugins* getWPlugins();

private:
    TextEdit *m_zoneTexte;

    QMenuBar *m_barreMenu;

    QMenu *m_mainMenu;
    QAction *m_nouveau;
    QAction *m_ouvrir;
    QAction *m_enregistrer;
    QAction *m_enregistrerSous;
    QAction *m_imprimer;
    QAction *m_quitter;

    QMenu *m_menuEdition;
    QAction *m_annuler;
    QAction *m_refaire;
    QAction *m_couper;
    QAction *m_copier;
    QAction *m_coller;
    QAction *m_rechercher;
    QAction *m_remplacer;
    QAction *m_selectionnerTout;

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
    Recherche *m_fenRecherche;

    QToolBar *m_barreOutilsTests;
    QToolBar *m_barreOutilsEdition;
    QToolBar *m_barreOutilsFichier;


    QFile *m_fichier;

    QStatusBar* m_statusBar;

    bool m_documentModifie;

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
    void enregistrerFichierSous();

    void nouveauFichier();

    void imprimerFichier();

    void quitter();

    void showMessage(const QString& pMessage, int pTimeout = 0);

    void rechargerPreferences();

    void changementLigne(int pNumLigne);

    void documentModifie(bool pMod);

signals:
    void lancerAnalyseSyntaxique(QFile*);
    void lancerAnalyseSemantique();
    void executer();
    void reloadSettings();
    void sigChangementLigne(int pNumLigne);
};
#endif // WINDOW_H
