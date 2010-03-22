#include "window.h"

#include "fenetreaide.h"
#include "fenetresaisie.h"
#include "gestionnaireparametres.h"
#include "recherche.h"

#include <QtCore/QFile>
#include <QtCore/QString>
#include <QtCore/QTextStream>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QCloseEvent>
#include <QtGui/QFileDialog>
#include <QtGui/QIcon>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QMessageBox>
#include <QtGui/QPrintDialog>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>

#include <QtCore/QDebug>

/*! \brief Constructeur. Initialise la fenêtre principale.
*/
Window::Window() : QMainWindow() {
    /* L'objet est détruit lorsque la fenêtre est fermée */
    setAttribute(Qt::WA_DeleteOnClose);

    /* On récupère la taille et la position de la fenêtre
       telle qu'elle était lorsque l'utilisateur l'a fermée la derniere fois */
    if (!GestionnaireParametres::getInstance()->getFenetreMax())
        restoreGeometry(GestionnaireParametres::getInstance()->getFenetreGeo());

    m_wPlugins = new WidgetPlugins();
    m_fenRecherche = new Recherche();

    /* On nomme la fenêtre principale */
    setWindowTitle(tr("[*]Nouvel algorithme - Icare"));


    // Initialisation de la liste des fichiers récents
    for (int i = 0; i < FichiersRecentsMax; i++) {
        m_fichiersRecents[i] = new QAction(this);
        m_fichiersRecents[i]->setVisible(false);
        connect(m_fichiersRecents[i], SIGNAL(triggered()), this, SLOT(ouvrirFichierRecent()));
    }

    /* On instancie la barre de Menu */
    m_barreMenu = new QMenuBar (this);

    /* Mise en place du menu principal */
    /* On instancie et on ajoute des paramètres (nom, raccourci clavier ...) aux objets du menu */
    m_mainMenu = new QMenu (m_barreMenu);
    m_nouveau = new QAction(tr("Nouveau"), this);
    m_nouveau->setShortcut(tr("Ctrl+N"));
    m_ouvrir = new QAction(tr("Ouvrir"), this);
    m_ouvrir->setShortcut(tr("Ctrl+O"));
    m_enregistrer = new QAction(tr("Enregistrer"), this);
    m_enregistrer->setShortcut(tr("Ctrl+S"));
    m_enregistrerSous = new QAction(tr("Enregistrer sous…"), this);
    m_enregistrerSous->setShortcut(tr("Ctrl+Shift+S"));
    m_imprimer = new QAction(tr("Imprimer"), this);
    m_imprimer->setShortcut(tr("Ctrl+P"));
    m_quitter = new QAction(tr("Quitter"), this);
    m_quitter->setShortcut(tr("Ctrl+Q"));
    m_mainMenu->setTitle(tr("&Fichier"));
    m_mainMenu->addAction(m_nouveau);
    m_mainMenu->addAction(m_ouvrir);
    m_mainMenu->addAction(m_enregistrer);
    m_mainMenu->addAction(m_enregistrerSous);
    m_separateurAct = m_mainMenu->addSeparator();
    for (int i = 0; i < FichiersRecentsMax; i++)
        m_mainMenu->addAction(m_fichiersRecents[i]);
    m_mainMenu->addSeparator();
    m_mainMenu->addAction(m_imprimer);
    m_mainMenu->addSeparator();
    m_mainMenu->addAction(m_quitter);

    majFichiersRecents();

    /* Mise en place du menu d'édition */
    m_menuEdition = new QMenu(m_barreMenu);
    m_annuler = new QAction(tr("Annuler"), this);
    m_annuler->setShortcut(tr("Ctrl+Z"));
    m_refaire = new QAction(tr("Refaire"), this);
    QList<QKeySequence> shortcuts;
    shortcuts.append(tr("Ctrl+Y"));
    shortcuts.append(tr("Ctrl+Shift+Z"));
    m_refaire->setShortcuts(shortcuts);
    m_couper = new QAction(tr("&Couper"), this);
    m_couper->setShortcut(tr("Ctrl+X"));
    m_copier = new QAction(tr("Co&pier"), this);
    m_copier->setShortcut(tr("Ctrl+C"));
    m_coller = new QAction(tr("C&oller"), this);
    m_coller->setShortcut(tr("Ctrl+V"));
    m_rechercher = new QAction(tr("Rechercher"), this);
    m_rechercher->setShortcut(tr("Ctrl+F"));
    m_remplacer = new QAction(tr("Remplacer"), this);
    m_remplacer->setShortcut(tr("Ctrl+H"));
    m_selectionnerTout = new QAction(tr("Sélectionner tout"), this);
    m_selectionnerTout->setShortcut(tr("Ctrl+A"));
    m_menuEdition->setTitle(tr("Editio&n"));
    m_menuEdition->addAction(m_annuler);
    m_menuEdition->addAction(m_refaire);
    m_menuEdition->addSeparator();
    m_menuEdition->addAction(m_couper);
    m_menuEdition->addAction(m_copier);
    m_menuEdition->addAction(m_coller);
    m_menuEdition->addSeparator();
    m_menuEdition->addAction(m_rechercher);
    m_menuEdition->addAction(m_remplacer);
    m_menuEdition->addSeparator();
    m_menuEdition->addAction(m_selectionnerTout);

    /* Mise en place du menu d'analyse */
    m_menuAnalyse = new QMenu(m_barreMenu);
    m_testSyntaxe = new QAction (tr("Tester la &syntaxe"), this);
    m_testSemantique = new QAction (tr("Tester la sé&mantique"), this);
    m_testComplet = new QAction (tr("Test complet"), this);
    m_executer = new QAction (tr("Exécuter"), this);
    m_executerPasAPas = new QAction(tr("Exécuter pas à pas"), this);
    m_pas = new QAction(tr("Avancer"), this);
    m_stop = new QAction(tr("Arrêter"), this);
    m_menuAnalyse->setTitle(tr("&Analyse"));
    m_menuAnalyse->addAction(m_testSyntaxe);
    m_menuAnalyse->addAction(m_testSemantique);
    m_menuAnalyse->addAction(m_testComplet);
    m_menuAnalyse->addSeparator();
    m_menuAnalyse->addAction(m_executer);
    m_menuAnalyse->addAction(m_executerPasAPas);
    m_menuAnalyse->addAction(m_pas);
    m_menuAnalyse->addAction(m_stop);

    /* Mise en place du menu d'options */
    m_menuOptions= new QMenu (m_barreMenu);
    m_menuOptions->setTitle(tr("&Options"));
    m_plugins = new QAction(tr("Plu&gins..."), this);
    m_preferences = new QAction(tr("&Préférences..."), this);
    m_menuOptions->addAction(m_plugins);
    m_menuOptions->addAction(m_preferences);

    /* Mise en place du menu d'aide */
    m_help = new QMenu (m_barreMenu);
    m_aPropos = new QAction (tr("À propos de Icare…"), this);
    m_aide = new QAction(tr("Aide"), this);
    m_aide->setShortcut(tr("F1"));
    m_help->setTitle(tr("&Aide"));
    m_help->addAction(m_aPropos);
    m_help->addAction(m_aide);

    /* Insertion des menus dans la barre de Menu */
    /* On ajoute tous les menus précédemment créés dans la barre de menu*/
    m_barreMenu->addMenu(m_mainMenu);
    m_barreMenu->addMenu(m_menuEdition);
    m_barreMenu->addMenu(m_menuAnalyse);
    m_barreMenu->addMenu(m_menuOptions);
    m_barreMenu->addMenu(m_help);

    /* Definition de la barre de Menu de la fenêtre */
    /* On ajoute la barre de menu à la fenêtre */
    setMenuBar(m_barreMenu);

    /* Mise en place du Widget principal */
    m_zoneTexte = new TextEdit(this);
    setCentralWidget(m_zoneTexte);
    m_fichier = new QFile(this);

    /* Mise en place d'icône et de tooltips sur les boutons des barres d'outils */
    m_nouveau->setIcon(QIcon(":/Icônes/window-new.png"));
    m_nouveau->setToolTip(tr("Nouvel algorithme"));
    m_ouvrir->setIcon(QIcon(":/Icônes/document-open.png"));
    m_ouvrir->setToolTip(tr("Ouvrir un algorithme"));
    m_enregistrer->setIcon(QIcon(":/Icônes/gnome-dev-floppy.png"));
    m_enregistrer->setToolTip(tr("Enregistrer l'algorithme"));
    m_enregistrerSous->setIcon(QIcon(":/Icônes/document-save-as.png"));
    m_enregistrerSous->setToolTip(tr("Enregistrer sous"));
    m_imprimer->setIcon(QIcon(":/Icônes/document-print.png"));
    m_imprimer->setToolTip(tr("Imprimer l'algorithme"));
    m_quitter->setIcon(QIcon(":/Icônes/process-stop.png"));
    m_annuler->setIcon(QIcon(":/Icônes/edit-undo.png"));
    m_annuler->setToolTip(tr("Annuler"));
    m_refaire->setIcon(QIcon(":/Icônes/edit-redo.png"));
    m_refaire->setToolTip(tr("Refaire"));
    m_couper->setIcon(QIcon(":/Icônes/edit-cut.png"));
    m_couper->setToolTip(tr("Couper"));
    m_copier->setIcon(QIcon(":/Icônes/edit-copy.png"));
    m_copier->setToolTip(tr("Copier"));
    m_coller->setIcon(QIcon(":/Icônes/edit-paste.png"));
    m_coller->setToolTip(tr("Coller"));
    m_rechercher->setIcon(QIcon(":/Icônes/edit-find.png"));
    m_remplacer->setIcon(QIcon(":/Icônes/edit-find-replace.png"));
    m_selectionnerTout->setIcon(QIcon(":/Icônes/edit-select-all"));
    m_testSyntaxe->setIcon(QIcon(":/Icônes/tools-check-spelling.png"));
    m_testSyntaxe->setToolTip(tr("Tester la syntaxe"));
    m_testSemantique->setIcon(QIcon(":/Icônes/system-run2.png"));
    m_testSemantique->setToolTip(tr("Tester la sémantique"));
    m_testComplet->setIcon(QIcon(":/Icônes/system-run.png"));
    m_testComplet->setToolTip(tr("Lancer tous les tests"));
    m_executer->setIcon(QIcon(":/Icônes/media-playback-start.png"));
    m_executer->setToolTip(tr("Exécuter"));
    m_executerPasAPas->setIcon(QIcon(":/Icônes/media-eject.png"));
    m_executerPasAPas->setToolTip(tr("Exécuter pas à pas"));
    m_pas->setIcon(QIcon(":/Icônes/media-skip-forward.png"));
    m_pas->setToolTip(tr("Exécuter la ligne suivante"));
    m_stop->setIcon(QIcon(":/Icônes/media-playback-stop.png"));
    m_stop->setToolTip(tr("Arrêter l'exécution"));
    m_preferences->setIcon(QIcon(":/Icônes/preferences-system.png"));
    m_plugins->setIcon(QIcon(":/Icônes/synaptic.png"));
    m_aide->setIcon(QIcon(":/Icônes/gtk-help.png"));

    /* Mise en place de la barre d'outils des fichiers */
    m_barreOutilsFichier = new QToolBar;
    m_barreOutilsFichier->setMovable(1);
    m_barreOutilsFichier->setWindowTitle("Fichiers");

    // Ajout des actions dans la barre d'outils
    m_barreOutilsFichier->addAction(m_nouveau);
    m_barreOutilsFichier->addAction(m_ouvrir);
    m_barreOutilsFichier->addAction(m_enregistrer);
    m_barreOutilsFichier->addAction(m_enregistrerSous);
    m_barreOutilsFichier->addAction(m_imprimer);

    addToolBar(m_barreOutilsFichier);

    /* Mise en place de la barre d'outils d'édition */
    m_barreOutilsEdition = new QToolBar;
    m_barreOutilsEdition->setMovable(1);
    m_barreOutilsEdition->setWindowTitle("Edition");

    // Ajout des actions dans la barre d'outils
    m_barreOutilsEdition->addAction(m_annuler);
    m_barreOutilsEdition->addAction(m_refaire);
    m_barreOutilsEdition->addAction(m_couper);
    m_barreOutilsEdition->addAction(m_copier);
    m_barreOutilsEdition->addAction(m_coller);
    m_barreOutilsEdition->addAction(m_selectionnerTout);

    addToolBar(m_barreOutilsEdition);

    /* Mise en place de la barre d'outils des tests */
    m_barreOutilsTests = new QToolBar;
    m_barreOutilsTests->setMovable(1);
    m_barreOutilsTests->setWindowTitle("Tests");

    // Ajout des actions dans la barre d'outils
    m_barreOutilsTests->addAction(m_testSyntaxe);
    m_barreOutilsTests->addAction(m_testSemantique);
    m_barreOutilsTests->addAction(m_testComplet);
    m_barreOutilsTests->addAction(m_executer);
    m_barreOutilsTests->addAction(m_executerPasAPas);
    m_barreOutilsTests->addAction(m_pas);
    m_barreOutilsTests->addAction(m_stop);

    addToolBar(m_barreOutilsTests);

    m_statusBar = new QStatusBar(this);
    setStatusBar(m_statusBar);

    /* Connection des signaux des objets aux slots de l'application
       connect([Objet émetteur], SIGNAL([Signal émis]), [Objet récepteur], SLOT[Slot "activé"]);
    */
    connect(m_aPropos, SIGNAL(triggered()), this, SLOT(afficherApropos()));
    connect(m_aide, SIGNAL(triggered()), this, SLOT(afficherAide()));
    connect(m_quitter, SIGNAL(triggered()), this, SLOT(close()));
    connect(m_ouvrir, SIGNAL(triggered()), this, SLOT(ouvrirFichier()));
    connect(m_enregistrer, SIGNAL(triggered()), this, SLOT(enregistrerFichier()));
    connect(m_enregistrerSous, SIGNAL(triggered()), this, SLOT(enregistrerFichierSous()));
    connect(m_nouveau, SIGNAL(triggered()), this, SLOT(nouveauFichier()));
    connect(m_imprimer, SIGNAL(triggered()), this, SLOT(imprimerFichier()));
    connect(m_testSyntaxe, SIGNAL(triggered()), this, SLOT(analyseSyntaxique()));
    connect(m_testSemantique, SIGNAL(triggered()), this, SLOT(analyseSemantique()));
    connect(m_testComplet, SIGNAL(triggered()), this, SLOT(testComplet()));
    connect(m_executer, SIGNAL(triggered()), this, SLOT(execution()));
    connect(m_executerPasAPas, SIGNAL(triggered()), this, SLOT(executionPasAPas()));
    connect(m_pas, SIGNAL(triggered()), this, SIGNAL(execPas()));
    connect(m_stop, SIGNAL(triggered()), this, SIGNAL(execStop()));
    connect(m_preferences, SIGNAL(triggered()), this, SLOT(afficherPreferences()));
    connect(m_plugins, SIGNAL(triggered()), this, SLOT(afficherMenuPlugins()));
    connect(this, SIGNAL(sigChangementLigne(int)), m_zoneTexte, SLOT(changementLigne(int)));
    connect(this, SIGNAL(ajouterTexte(QString)), m_zoneTexte, SLOT(ajouterTexte(QString)));
    connect(m_zoneTexte->getTextEdit(), SIGNAL(undoAvailable(bool)), m_annuler, SLOT(setEnabled(bool)));
    connect(m_annuler, SIGNAL(triggered()), m_zoneTexte->getTextEdit(), SLOT(undo()));
    connect(m_zoneTexte->getTextEdit(), SIGNAL(redoAvailable(bool)), m_refaire, SLOT(setEnabled(bool)));
    connect(m_refaire, SIGNAL(triggered()), m_zoneTexte->getTextEdit(), SLOT(redo()));
    connect(m_zoneTexte->getTextEdit(), SIGNAL(copyAvailable(bool)), m_couper, SLOT(setEnabled(bool)));
    connect(m_couper, SIGNAL(triggered()), m_zoneTexte->getTextEdit(), SLOT(cut()));
    connect(m_zoneTexte->getTextEdit(), SIGNAL(copyAvailable(bool)), m_copier, SLOT(setEnabled(bool)));
    connect(m_copier, SIGNAL(triggered()), m_zoneTexte->getTextEdit(), SLOT(copy()));
    connect(m_coller, SIGNAL(triggered()), m_zoneTexte->getTextEdit(), SLOT(paste()));
    connect(m_rechercher, SIGNAL(triggered()), m_fenRecherche, SLOT(rec()));
    connect(m_remplacer, SIGNAL(triggered()), m_fenRecherche, SLOT(rem()));
    connect(m_selectionnerTout, SIGNAL(triggered()), m_zoneTexte->getTextEdit(), SLOT(selectAll()));
    connect(m_fenRecherche, SIGNAL(recherche(TRecherche)), m_zoneTexte, SLOT(recherche(TRecherche)));
    connect(m_fenRecherche, SIGNAL(remplacement(TRecherche)), m_zoneTexte, SLOT(remplacement(TRecherche)));
    connect(m_fenRecherche, SIGNAL(remplacerTout(TRecherche)), m_zoneTexte, SLOT(remplacerTout(TRecherche)));

    m_documentModifie = false;
    nouveauFichier();
}

/*! \brief Destructeur.
*/
Window::~Window() {
    m_fenRecherche->close();
    delete m_zoneTexte;

    delete m_mainMenu;
    delete m_nouveau;
    delete m_ouvrir;
    delete m_enregistrer;
    delete m_enregistrerSous;
    delete m_imprimer;
    delete m_quitter;

    delete m_menuEdition;
    delete m_annuler;
    delete m_refaire;
    delete m_couper;
    delete m_copier;
    delete m_coller;
    delete m_rechercher;
    delete m_remplacer;
    delete m_selectionnerTout;

    delete m_menuAnalyse;
    delete m_testSyntaxe;
    delete m_testSemantique;
    delete m_testComplet;
    delete m_executer;
    delete m_executerPasAPas;
    delete m_pas;
    delete m_stop;

    delete m_menuOptions;
    delete m_plugins;
    delete m_preferences;

    delete m_help;
    delete m_aPropos;
    delete m_aide;
    delete m_wPlugins;
    delete m_fenRecherche;

    delete m_barreOutilsTests;
    delete m_barreOutilsEdition;
    delete m_barreOutilsFichier;


    delete m_fichier;

    delete m_statusBar;

    delete m_barreMenu;
}

void Window::erreurMath(MathExp::erreur pCodeErreur) {
    if(pCodeErreur == MathExp::DivisionParZero)
        QMessageBox::information(this, "Erreur", "Division par zero");
    else
        QMessageBox::information(this, "Erreur", "Erreur inconnue");
}

void Window::executionTerminee() {
    m_testSyntaxe->setEnabled(true);
    m_testSemantique->setEnabled(true);
    m_testComplet->setEnabled(true);
    m_executer->setEnabled(true);
    m_executerPasAPas->setEnabled(true);
    m_pas->setEnabled(false);
    m_stop->setEnabled(false);
    m_zoneTexte->getTextEdit()->setReadOnly(false);
}

/*! \brief Lance l'exécution de l'algorithme en temps réel.

  \sa Window::executionPasAPas()
*/
void Window::execution() {
    m_testSyntaxe->setEnabled(false);
    m_testSemantique->setEnabled(false);
    m_testComplet->setEnabled(false);
    m_executer->setEnabled(false);
    m_executerPasAPas->setEnabled(false);
    m_stop->setEnabled(true);
    m_zoneTexte->getTextEdit()->setReadOnly(true);
    emit executer(false);
}

/*! \brief Lance l'exécution de l'algorithme en mode pas à pas.

  \sa Window::execution
*/
void Window::executionPasAPas() {
    m_testSyntaxe->setEnabled(false);
    m_testSemantique->setEnabled(false);
    m_testComplet->setEnabled(false);
    m_executer->setEnabled(false);
    m_executerPasAPas->setEnabled(false);
    m_pas->setEnabled(true);
    m_stop->setEnabled(true);
    m_zoneTexte->getTextEdit()->setReadOnly(true);
    emit executer(true);
}

/*! \brief Lancement de l'analyse syntaxique.
*/
void Window::analyseSyntaxique() {
    if (m_documentModifie)
        enregistrerFichier();
    if (m_documentModifie)
        return;
    showMessage(tr("Début de l'analyse syntaxique du fichier %1…").arg(QFileInfo(m_fichier->fileName()).fileName()), 2000);
    emit lancerAnalyseSyntaxique(m_fichier);
}

/*! \brief Lancement de l'analyse sémantique.
*/
void Window::analyseSemantique() {
    if (m_documentModifie)
        analyseSyntaxique();
    emit lancerAnalyseSemantique();
}

/*! \brief Affichage de la fenêtre d'à propos.

  Cette fonction ouvre la fenêtre contenant les informations à propos de l'application.
*/
void Window::afficherApropos() {
    /* Mise en place de la fenêtre d'à propos */
    m_fenApropos = new Apropos;
    //m_fenApropos->setWindowTitle("À propos de Icare");
    m_fenApropos->show();
}

/*! \brief Affichage de la fenêtre d'aide.

  Cette fonction ouvre la fenêtre contenant l'aide utilisateur.
*/
void Window::afficherAide() {
    /* Mise en place de la fenêtre d'aide */
    m_fenAide = new FenetreAide;
    m_fenAide->show();
}

/*! \brief Ouverture d'un fichier.

  Cette fonction sans paramètre ouvre une boîte de dialogue permettant d'ouvrir un fichier existant
  et d'insérer son contenu dans la zone de texte.
  \sa Window::ouvrirFichier(QString pNomFichier)
*/
void Window::ouvrirFichier() {
    if (m_documentModifie) {
        QMessageBox msgBox;
        msgBox.setText(tr("L'algorithme a été modifié."));
        msgBox.setInformativeText(tr("Voulez-vous enregistrer les modifications ?"));
        msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Save);
        int ret = msgBox.exec();
        switch (ret) {
        case QMessageBox::Save:
            enregistrerFichier();
            break;
        case QMessageBox::Discard:
            break;
        case QMessageBox::Cancel:
            return;
            break;
        default:
            // ne devrait jamais être atteint
            break;
        }
    }

    QString nomFichier = QFileDialog::getOpenFileName(this, tr("Ouvrir un fichier"), ".", "Algorithmes (*.algo);;Tous les fichiers (*);;Fichiers texte (*.txt)");
    ouvrirFichier(nomFichier);
}

/*! \brief Ouverture d'un fichier.

Cette fonction ouvre le fichier passé en paramètre et insère son contenu dans la zone de texte.
  \param pNomFichier Nom du fichier à ouvrir.
  \sa Window::ouvrirFichier()
*/
void Window::ouvrirFichier(QString pNomFichier) {
    m_fichier->setFileName(pNomFichier);
    bool ouverture = m_fichier->open(QIODevice::ReadOnly | QIODevice::Text);

    switch (m_fichier->error()) {
    case QFile::NoError:
        showMessage(tr("Fichier %1 ouvert avec succès.").arg(QFileInfo(m_fichier->fileName()).fileName()), 2000);
        break;
    case QFile::ReadError:
        showMessage(tr("Erreur lors de la lecture du fichier %1.").arg(QFileInfo(m_fichier->fileName()).fileName()), 2000);
        break;
    case QFile::WriteError:
        showMessage(tr("Erreur lors de l'écriture du fichier %1.").arg(QFileInfo(m_fichier->fileName()).fileName()), 2000);
        break;
    case QFile::FatalError:
        showMessage(tr("Erreur fatale."), 2000);
        break;
    case QFile::ResourceError:
        showMessage(tr("Erreur de ressource."), 2000);
        break;
    case QFile::OpenError:
        showMessage(tr("Le fichier %1 ne peut pas être ouvert.").arg(QFileInfo(m_fichier->fileName()).fileName()), 2000);
        break;
    case QFile::AbortError:
        showMessage(tr("L'opération a été interrompue."), 2000);
        break;
    case QFile::TimeOutError:
        showMessage(tr("Délai d'attente dépassé."), 2000);
        break;
    case QFile::UnspecifiedError:
        showMessage(tr("Erreur inconnue."), 2000);
        break;
    case QFile::RemoveError:
        showMessage(tr("Erreur lors de la suppression du fichier %1.").arg(QFileInfo(m_fichier->fileName()).fileName()), 2000);
        break;
    case QFile::RenameError:
        showMessage(tr("Erreur lors du renommage du fichier %1.").arg(QFileInfo(m_fichier->fileName()).fileName()), 2000);
        break;
    case QFile::PositionError:
        showMessage(tr("La position du fichier %1 ne peut pas être modifiée.").arg(QFileInfo(m_fichier->fileName()).fileName()), 2000);
        break;
    case QFile::ResizeError:
        showMessage(tr("Le fichier %1 ne peut pas être redimensionné.").arg(QFileInfo(m_fichier->fileName()).fileName()), 2000);
        break;
    case QFile::PermissionsError:
        showMessage(tr("Accès au fichier %1 impossible.").arg(QFileInfo(m_fichier->fileName()).fileName()), 2000);
        break;
    case QFile::CopyError:
        showMessage(tr("Le fichier %1 ne peut pas être copié.").arg(QFileInfo(m_fichier->fileName()).fileName()), 2000);
        break;
    }

    if (!ouverture)
        return;

    connect(m_zoneTexte->getTextEdit()->document(), SIGNAL(modificationChanged(bool)), this, SLOT(documentModifie(bool)));
    // On créé un flux de texte
    QApplication::setOverrideCursor(Qt::WaitCursor);
    QTextStream flux(m_fichier);
    m_zoneTexte->getTextEdit()->setPlainText(flux.readAll());
    m_zoneTexte->getTextEdit()->setDocumentTitle(m_fichier->fileName());
    m_zoneTexte->getTextEdit()->document()->setModified(false);
    setWindowModified(false);
    setWindowTitle(tr("[*]%1 - Icare").arg(QFileInfo(m_fichier->fileName()).fileName()));

    setWindowFilePath(m_fichier->fileName());

    QStringList fichiers = GestionnaireParametres::getInstance()->getListeFichiersRecents();
    fichiers.removeAll(m_fichier->fileName());
    fichiers.prepend(m_fichier->fileName());
    while (fichiers.size() > FichiersRecentsMax)
        fichiers.removeLast();

    GestionnaireParametres::getInstance()->setListeFichiersRecents(fichiers);

    majFichiersRecents();

    m_fichier->close();
    QApplication::restoreOverrideCursor();
}

/*! \brief Affichage des préférences.

  Cette fonction affiche une fenêtre permettant de modifier les options de l'application.
*/
void Window::afficherPreferences() {
    m_pref = new Preferences();
    QObject::connect(m_pref, SIGNAL(settingsChanged()), this, SLOT(rechargerPreferences()));
    m_pref->show();
}

/*! \brief Affichage du menu des plugins.

  Cette fonction affiche la fenêtre permettant à l'utilisateur d'activer/désactiver les plugins.
*/
void Window::afficherMenuPlugins() {
    m_wPlugins->show();
}

/*! \brief Enregistrement du fichier courant.

  Cette méthode enregistre les modifications d'un fichier ouvert.
  Si aucun fichier n'a été ouvert, cette méthode fait appel à la méthode enregistrerFichierSous.

  \sa Window::enregistrerFichierSous()
*/
void Window::enregistrerFichier() {
    if (m_fichier->fileName() == QString::null) {
        enregistrerFichierSous();
        return;
    }

    QApplication::setOverrideCursor(Qt::WaitCursor);
    bool ouverture = m_fichier->open(QIODevice::WriteOnly | QIODevice::Text);

    switch (m_fichier->error()) {
    case QFile::NoError:
        showMessage(tr("Fichier %1 ouvert avec succès.").arg(QFileInfo(m_fichier->fileName()).fileName()), 2000);
        break;
    case QFile::ReadError:
        showMessage(tr("Erreur lors de la lecture du fichier %1.").arg(QFileInfo(m_fichier->fileName()).fileName()), 2000);
        break;
    case QFile::WriteError:
        showMessage(tr("Erreur lors de l'écriture du fichier %1.").arg(QFileInfo(m_fichier->fileName()).fileName()), 2000);
        break;
    case QFile::FatalError:
        showMessage(tr("Erreur fatale."), 2000);
        break;
    case QFile::ResourceError:
        showMessage(tr("Erreur de ressource."), 2000);
        break;
    case QFile::OpenError:
        showMessage(tr("Le fichier %1 ne peut pas être ouvert.").arg(QFileInfo(m_fichier->fileName()).fileName()), 2000);
        break;
    case QFile::AbortError:
        showMessage(tr("L'opération a été interrompue."), 2000);
        break;
    case QFile::TimeOutError:
        showMessage(tr("Délai d'attente dépassé."), 2000);
        break;
    case QFile::UnspecifiedError:
        showMessage(tr("Erreur inconnue."), 2000);
        break;
    case QFile::RemoveError:
        showMessage(tr("Erreur lors de la suppression du fichier %1.").arg(QFileInfo(m_fichier->fileName()).fileName()), 2000);
        break;
    case QFile::RenameError:
        showMessage(tr("Erreur lors du renommage du fichier %1.").arg(QFileInfo(m_fichier->fileName()).fileName()), 2000);
        break;
    case QFile::PositionError:
        showMessage(tr("La position du fichier %1 ne peut pas être modifiée.").arg(QFileInfo(m_fichier->fileName()).fileName()), 2000);
        break;
    case QFile::ResizeError:
        showMessage(tr("Le fichier %1 ne peut pas être redimensionné.").arg(QFileInfo(m_fichier->fileName()).fileName()), 2000);
        break;
    case QFile::PermissionsError:
        showMessage(tr("Accès au fichier %1 impossible.").arg(QFileInfo(m_fichier->fileName()).fileName()), 2000);
        break;
    case QFile::CopyError:
        showMessage(tr("Le fichier %1 ne peut pas être copié.").arg(QFileInfo(m_fichier->fileName()).fileName()), 2000);
        break;
    }

    if (!ouverture)
        return;

    QString texte = m_zoneTexte->getTextEdit()->toPlainText();
    m_fichier->write(texte.toUtf8());
    m_fichier->close();
    m_zoneTexte->getTextEdit()->document()->setModified(false);
    QApplication::restoreOverrideCursor();
}

/*! \brief Enregistrement du fichier courant.

  Cette méthode ouvre une boîte de dialogue permettant d'enregistrer le fichier.
*/
void Window::enregistrerFichierSous() {
    QString nomFichier = QFileDialog::getSaveFileName(this, tr("Enregistrer un fichier"), ".", "Algorithmes (*.algo);;Tous les fichiers (*);;Fichiers texte (*.txt)");
    if (nomFichier == QString::null)
        return;
    m_fichier->setFileName(nomFichier);
    enregistrerFichier();
    m_zoneTexte->getTextEdit()->setDocumentTitle(m_fichier->fileName());
    //m_zoneTexte->getTextEdit()->document()->setModified(false);
    setWindowModified(false);
    m_documentModifie = false;
    setWindowTitle(tr("[*]%1 - Icare").arg(QFileInfo(m_fichier->fileName()).fileName()));
}

/*! \brief Création d'un nouveau fichier.

  Cette fonction permet de créer un nouveau fichier.
  Si les modifications du fichier courant n'ont pas été modifiées, affiche une boîte de dialogue de confirmation.
*/
void Window::nouveauFichier() {
    if (m_documentModifie) {
        QMessageBox msgBox;
        msgBox.setText(tr("L'algorithme a été modifié."));
        msgBox.setInformativeText(tr("Voulez-vous enregistrer les modifications ?"));
        msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Save);
        int ret = msgBox.exec();
        switch (ret) {
        case QMessageBox::Save:
            enregistrerFichier();
            break;
        case QMessageBox::Discard:
            break;
        case QMessageBox::Cancel:
            return;
            break;
        default:
            // ne devrait jamais être atteint
            break;
        }
    }
    setWindowTitle(tr("[*]Nouvel algorithme - Icare"));
    m_fichier->setFileName(QString::null);
    m_zoneTexte->getTextEdit()->document()->clear();
    m_zoneTexte->getTextEdit()->setDocumentTitle(QString::null);
    QFile* tmp = new QFile;
    tmp->setFileName(":/Algos/defaut.algo");
    bool ouverture = tmp->open(QIODevice::ReadOnly | QIODevice::Text);
    if (ouverture) {
        QApplication::setOverrideCursor(Qt::WaitCursor);
        QTextStream flux(tmp);
        m_zoneTexte->getTextEdit()->setPlainText(flux.readAll());
        tmp->close();
        QApplication::restoreOverrideCursor();
    }
    m_annuler->setEnabled(m_zoneTexte->getTextEdit()->document()->isUndoAvailable());
    m_refaire->setEnabled(m_zoneTexte->getTextEdit()->document()->isRedoAvailable());
    m_couper->setEnabled(false);
    m_copier->setEnabled(false);
    documentModifie(true);
}

void Window::closeEvent(QCloseEvent *pE) {
    m_stop->trigger();
    if (m_documentModifie) {
        QMessageBox msgBox;
        msgBox.setText(tr("L'algorithme a été modifié."));
        msgBox.setInformativeText(tr("Voulez-vous enregistrer les modifications ?"));
        msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Save);
        int ret = msgBox.exec();
        switch (ret) {
        case QMessageBox::Save:
            enregistrerFichier();
            break;
        case QMessageBox::Discard:
            break;
        case QMessageBox::Cancel:
            pE->ignore();
            return;
            break;
        default:
            // ne devrait jamais être atteint
            break;
        }
    }

    GestionnaireParametres::getInstance()->setFenetreGeo(saveGeometry());
    GestionnaireParametres::getInstance()->setFenetreMax(isMaximized());
    GestionnaireParametres::getInstance()->destroy();
    pE->accept();
}

/*! \brief Impression du fichier courant.

  Cette fonction affichae une boîte de dialogue permettant d'imprimer le fichier courant.
*/
void Window::imprimerFichier() {
    QPrintDialog printDialog(this);
    if (printDialog.exec() == QDialog::Accepted) {
        m_zoneTexte->getTextEdit()->print(printDialog.printer());
    }
}

void Window::showMessage(const QString& pMessage, int pTimeout) {
    m_statusBar->showMessage(pMessage, pTimeout);
}

/*! \brief Rechargement des préférences.
*/
void Window::rechargerPreferences() {
    emit reloadSettings();
}

/*! \brief Retourne la zone de texte.

  \return m_zoneTexte
*/
TextEdit* Window::getZoneTexte() {
    return m_zoneTexte;
}

void Window::changementLigne(int pNumLigne) {
    emit sigChangementLigne(pNumLigne);
}

void Window::documentModifie(bool pMod) {
    setWindowModified(pMod);
    m_enregistrer->setEnabled(pMod);
    m_documentModifie = pMod;
    m_testSemantique->setEnabled(false);
    m_executer->setEnabled(false);
    m_executerPasAPas->setEnabled(false);
    m_pas->setEnabled(false);
    m_stop->setEnabled(false);
}

/*! \brief Affichage de la fenêtre de saisie.

  Cette fonction affiche une boite de dialogue permettant de saisir la valeur d'une variable.
*/
void Window::afficherFenSaisie(bool pBonType) {
    m_fenSaisie = new FenetreSaisie(pBonType);
    connect(m_fenSaisie, SIGNAL(saisie(QString)), this, SLOT(transmettreSaisie(QString)));
    m_fenSaisie->show();
}

/*! \brief Transmission de la saisie.

  Cette méthode permet de transmettre la saisie effectuée à l'analyse.
*/
void Window::transmettreSaisie(QString pSaisie) {
    emit sigSaisie(pSaisie);
}

/*! \brief Retourne le widgetPlugins.

  \return m_wPlugins
*/
WidgetPlugins* Window::getWPlugins() {
    return m_wPlugins;
}

/*! \brief Retourne la barre de menus.

  \return m_barreMenu
*/
QMenuBar* Window::getMenuBar() {
    return m_barreMenu;
}

void Window::analyseSyntaxiqueTerminee(bool pOk) {
    m_testSemantique->setEnabled(pOk);
    if (pOk && m_isTestComplet)
        analyseSemantique();
}

void Window::analyseSemantiqueTerminee(bool pOk) {
    m_executer->setEnabled(pOk);
    m_executerPasAPas->setEnabled(pOk);
    m_isTestComplet = false;
}

void Window::ouvrirFichierRecent() {
    QAction *action = qobject_cast<QAction *>(sender());
    if (action)
        ouvrirFichier(action->data().toString());
}

void Window::majFichiersRecents() {
    QStringList fichiers = GestionnaireParametres::getInstance()->getListeFichiersRecents();

    int numRecentFiles = qMin(fichiers.size(), (int)FichiersRecentsMax);

    for (int i = 0; i < numRecentFiles; i++) {
        QString text = tr("&%1 %2").arg(i + 1).arg(nomCourt(fichiers[i]));
        m_fichiersRecents[i]->setText(text);
        m_fichiersRecents[i]->setData(fichiers[i]);
        m_fichiersRecents[i]->setVisible(true);
    }
    for (int i = numRecentFiles; i < FichiersRecentsMax; i++)
        m_fichiersRecents[i]->setVisible(false);

    m_separateurAct->setVisible(numRecentFiles > 0);
}

QString Window::nomCourt(const QString& pNomComplet) {
    return QFileInfo(pNomComplet).fileName();
}

/*! \brief Lance un test complet du fichier ouvert.
*/
void Window::testComplet() {
    m_isTestComplet = true;
    analyseSyntaxique();
}
