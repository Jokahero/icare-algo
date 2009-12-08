#ifndef WINDOW_H
#define WINDOW_H

#include <QtGui>
#include <QtCore>

#include "GUI_global.h"

#include "apropos.h"
#include "textedit.h"
#include "preferences.h"
#include "../ExpressionsMathematiques/mathexp.h"

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
    QAction *m_testOperation;
    QAction *m_testComplet;
    QAction *m_executer;

    QMenu *m_menuOptions;
    QAction *m_plugins;
    QAction *m_preferences;

    QMenu *m_help;
    QAction *m_aPropos;

    Apropos *m_fenApropos;
    Preferences *m_pref;

    QIcon m_icone;

    QToolBar *m_barreOutilsTests;
    QToolBar *m_barreOutilsFichier;


    QFile *m_fichier;

public slots:
    void erreurMath(MathExp::erreur);

    void analyseSyntaxique();

    void execution();

    void afficherApropos();

    void ouvrirFichier();

    void ouvrirFichier(QString pNomFichier);

    void afficherPreferences();

    void enregistrerFichier();

    void imprimerFichier();

    void quitter();

signals:
    void lancerAnalyseSyntaxique(QFile*);
    void executer(QFile*);
};
#endif // WINDOW_H
