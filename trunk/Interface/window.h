    #ifndef WINDOW_H
#define WINDOW_H

#include <QtGui/QMainWindow>

#include "GUI_global.h"

#include "../Analyse/mathexp.h"
#include "apropos.h"
#include "preferences.h"
#include "textedit.h"
#include "widgetplugins.h"

class QAction;
class QFile;
class QIcon;
class QMenu;
class QMenuBar;
class QStatusBar;
class QString;
class QToolBar;
class FenetreSaisie;
class Recherche;

/*! \brief Fenêtre principale
  */
class Window : public QMainWindow {
    Q_OBJECT

public:
    Window();
    ~Window();

    static const int FichiersRecentsMax = 5;


    TextEdit* getZoneTexte();
    WidgetPlugins* getWPlugins();
    QMenuBar* getMenuBar();

protected:
    void closeEvent(QCloseEvent *pE);

private:
    TextEdit *m_zoneTexte; /*!< \brief Pointeur vers la zone d'édition. */

    QMenuBar *m_barreMenu; /*!< \brief Barre de menu. */

    QMenu *m_mainMenu; /*!< \brief Menu principal. */
    QAction *m_nouveau;
    QAction *m_ouvrir;
    QAction *m_enregistrer;
    QAction *m_enregistrerSous;
    QAction *m_imprimer;
    QAction *m_quitter;

    QMenu *m_menuEdition; /*!< \brief Menu d'édition. */
    QAction *m_annuler;
    QAction *m_refaire;
    QAction *m_couper;
    QAction *m_copier;
    QAction *m_coller;
    QAction *m_rechercher;
    QAction *m_remplacer;
    QAction *m_selectionnerTout;

    QMenu *m_menuAnalyse; /*!< \brief Menu d'analyse. */
    QAction *m_testSyntaxe;
    QAction *m_testSemantique;
    QAction *m_testComplet;
    QAction *m_executer;
    QAction *m_executerPasAPas;
    QAction *m_pas;
    QAction *m_stop;

    QMenu *m_menuOptions; /*!< \brief Menu des options. */
    QAction *m_plugins;
    QAction *m_preferences;

    QMenu *m_help; /*!< \brief Menu d'aide. */
    QAction *m_aPropos;

    Apropos *m_fenApropos;
    Preferences *m_pref;
    WidgetPlugins *m_wPlugins;
    Recherche *m_fenRecherche;
    FenetreSaisie *m_fenSaisie;

    QToolBar *m_barreOutilsTests; /*!< \brief Barre d'outils d'analyse. */
    QToolBar *m_barreOutilsEdition; /*!< \brief Barre d'outils d'édition. */
    QToolBar *m_barreOutilsFichier; /*!< \brief Barre d'outils de manipulation des fichiers. */


    QFile *m_fichier; /*!< Fichier courant. */

    QStatusBar* m_statusBar; /*!< Barre de status. */

    bool m_documentModifie;
    bool m_isTestComplet;

    void majFichiersRecents();
    QString nomCourt(const QString& pNomComplet);
    QAction *m_fichiersRecents[FichiersRecentsMax];
    QAction *m_separateurAct;

public slots:
    void erreurMath(MathExp::erreur);
    void analyseSyntaxique();
    void analyseSemantique();
    void testComplet();
    void execution();
    void executionPasAPas();
    void afficherApropos();
    void ouvrirFichier();
    void ouvrirFichier(QString pNomFichier);
    void afficherPreferences();
    void afficherMenuPlugins();
    void enregistrerFichier();
    void enregistrerFichierSous();
    void nouveauFichier();
    void imprimerFichier();
    void showMessage(const QString& pMessage, int pTimeout = 0);
    void rechargerPreferences();
    void changementLigne(int pNumLigne);
    void documentModifie(bool pMod);
    void afficherFenSaisie();
    void transmettreSaisie(QString pSaisie);
    void analyseSyntaxiqueTerminee(bool pOk);
    void analyseSemantiqueTerminee(bool pOk);
    void executionTerminee();
    void ouvrirFichierRecent();

signals:
    void lancerAnalyseSyntaxique(QFile*);
    void lancerAnalyseSemantique();
    void executer(bool pPasAPas);
    void execPas();
    void execStop();
    void reloadSettings();
    void sigChangementLigne(int pNumLigne);
    void sigSaisie(QString pSaisie);
    void ajouterTexte(QString pTexte);
};
#endif // WINDOW_H
