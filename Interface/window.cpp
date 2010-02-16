#include "window.h"

#include "gestionnaireparametres.h"
#include "recherche.h"
#include "fenetresaisie.h"

#include <QtCore/QFile>
#include <QtCore/QString>
#include <QtCore/QTextStream>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QFileDialog>
#include <QtGui/QIcon>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QMessageBox>
#include <QtGui/QPrintDialog>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>

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
    m_mainMenu->addSeparator();
    m_mainMenu->addAction(m_imprimer);
    m_mainMenu->addSeparator();
    m_mainMenu->addAction(m_quitter);

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
    m_menuAnalyse->setTitle(tr("&Analyse"));
    m_menuAnalyse->addAction(m_testSyntaxe);
    m_menuAnalyse->addAction(m_testSemantique);
    m_menuAnalyse->addAction(m_testComplet);
    m_menuAnalyse->addSeparator();
    m_menuAnalyse->addAction(m_executer);

    /* Mise en place du menu d'options */
    m_menuOptions= new QMenu (m_barreMenu);
    m_menuOptions->setTitle(tr("&Options"));
    m_plugins = new QAction(tr("Plu&gins..."), this);
    m_preferences = new QAction(tr("&Préférences..."), this);
    m_menuOptions->addAction(m_plugins);
    m_menuOptions->addAction(m_preferences);

    /* Mise en place du menu d'aide */
    m_help = new QMenu (m_barreMenu);
    m_aPropos = new QAction (tr("A propos de Icare ..."), this);
    m_help->setTitle(tr("&Aide"));
    m_help->addAction(m_aPropos);

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
    m_quitter->setIcon(QIcon(":/Icônes/dialog-cancel.png"));
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
    m_rechercher->setIcon(QIcon(":/Icônes/document-preview.png"));
    m_testSyntaxe->setIcon(QIcon(":/Icônes/tools-check-spelling.png"));
    m_testSyntaxe->setToolTip(tr("Tester la syntaxe"));
    m_executer->setIcon(QIcon(":/Icônes/exec.png"));
    m_executer->setToolTip(tr("Exécuter"));
    m_preferences->setIcon(QIcon(":/Icônes/preferences-system.png"));
    m_plugins->setIcon(QIcon(":/Icônes/synaptic.png"));

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

    addToolBar(m_barreOutilsTests);

    m_statusBar = new QStatusBar(this);
    setStatusBar(m_statusBar);

    /* Connection des signaux des objets aux slots de l'application
       connect([Objet émetteur], SIGNAL([Signal émis]), [Objet récepteur], SLOT[Slot "activé"]);
    */
    connect(m_aPropos, SIGNAL(triggered()), this, SLOT(afficherApropos()));
    connect(m_quitter, SIGNAL(triggered()), this, SLOT(close()));
    connect(m_ouvrir, SIGNAL(triggered()), this, SLOT(ouvrirFichier()));
    connect(m_enregistrer, SIGNAL(triggered()), this, SLOT(enregistrerFichier()));
    connect(m_enregistrerSous, SIGNAL(triggered()), this, SLOT(enregistrerFichierSous()));
    connect(m_nouveau, SIGNAL(triggered()), this, SLOT(nouveauFichier()));
    connect(m_imprimer, SIGNAL(triggered()), this, SLOT(imprimerFichier()));
    connect(m_testSyntaxe, SIGNAL(triggered()), this, SLOT(analyseSyntaxique()));
    connect(m_testSemantique, SIGNAL(triggered()), this, SLOT(analyseSemantique()));
    connect(m_executer, SIGNAL(triggered()), this, SLOT(execution()));
    connect(m_preferences, SIGNAL(triggered()), this, SLOT(afficherPreferences()));
    connect(m_plugins, SIGNAL(triggered()), this, SLOT(afficherMenuPlugins()));
    connect(this, SIGNAL(sigChangementLigne(int)), m_zoneTexte, SLOT(changementLigne(int)));
    connect(m_zoneTexte, SIGNAL(undoAvailable(bool)), m_annuler, SLOT(setEnabled(bool)));
    connect(m_annuler, SIGNAL(triggered()), m_zoneTexte, SLOT(undo()));
    connect(m_zoneTexte, SIGNAL(redoAvailable(bool)), m_refaire, SLOT(setEnabled(bool)));
    connect(m_refaire, SIGNAL(triggered()), m_zoneTexte, SLOT(redo()));
    connect(m_zoneTexte, SIGNAL(copyAvailable(bool)), m_couper, SLOT(setEnabled(bool)));
    connect(m_couper, SIGNAL(triggered()), m_zoneTexte, SLOT(cut()));
    connect(m_zoneTexte, SIGNAL(copyAvailable(bool)), m_copier, SLOT(setEnabled(bool)));
    connect(m_copier, SIGNAL(triggered()), m_zoneTexte, SLOT(copy()));
    connect(m_coller, SIGNAL(triggered()), m_zoneTexte, SLOT(paste()));
    connect(m_rechercher, SIGNAL(triggered()), m_fenRecherche, SLOT(rec()));
    connect(m_remplacer, SIGNAL(triggered()), m_fenRecherche, SLOT(rem()));
    connect(m_selectionnerTout, SIGNAL(triggered()), m_zoneTexte, SLOT(selectAll()));
    connect(m_fenRecherche, SIGNAL(recherche(QString)), m_zoneTexte, SLOT(recherche(QString)));
    connect(m_fenRecherche, SIGNAL(remplacement(QString, QString)), m_zoneTexte, SLOT(remplacement(QString, QString)));
    connect(m_fenRecherche, SIGNAL(remplacerTout(QString, QString)), m_zoneTexte, SLOT(remplacerTout(QString, QString)));

    m_annuler->setEnabled(m_zoneTexte->document()->isUndoAvailable());
    m_refaire->setEnabled(m_zoneTexte->document()->isRedoAvailable());
    m_couper->setEnabled(false);
    m_copier->setEnabled(false);
    documentModifie(true);
}

Window::~Window() {
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

    delete m_menuOptions;
    delete m_plugins;
    delete m_preferences;

    delete m_help;
    delete m_aPropos;

    //delete m_fenApropos;
    //delete m_pref;
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

void Window::execution() {
    emit executer();
}

void Window::analyseSyntaxique() {
    if (m_documentModifie)
        enregistrerFichier();
    showMessage(tr("Début de l'analyse syntaxique du fichier %1…").arg(QFileInfo(m_fichier->fileName()).fileName()), 2000);
    emit lancerAnalyseSyntaxique(m_fichier);
}

void Window::analyseSemantique() {
    if (m_documentModifie)
        analyseSyntaxique();
    emit lancerAnalyseSemantique();
}

void Window::afficherApropos() {
    /* Mise en place de la fenêtre d'à propos */
    m_fenApropos = new Apropos;
    m_fenApropos->setWindowTitle("À propos de Icare");
    m_fenApropos->show();
}

/*! \brief Ouverture d'un fichier.
  Cette fonction sans paramètre ouvre une boÃ®te de dialogue permettant d'ouvrir un fichier existant
  et d'insérer son contenu dans la zone de texte.
*/
void Window::ouvrirFichier() {
    QString nomFichier = QFileDialog::getOpenFileName(this, tr("Ouvrir un fichier"), ".", "Algorithmes (*.algo);;Tous les fichiers (*);;Fichiers texte (*.txt)");

    ouvrirFichier(nomFichier);
}

/*! \brief Ouverture d'un fichier.
  Cette fonction ouvre le fichier passé en paramètre et insère son contenu dans la zone de texte.
  \param pNomFichier Nom du fichier à ouvrir.
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

    connect(m_zoneTexte->document(), SIGNAL(modificationChanged(bool)), this, SLOT(documentModifie(bool)));
    // On créé un flux de texte
    QApplication::setOverrideCursor(Qt::WaitCursor);
    QTextStream flux(m_fichier);
    m_zoneTexte->setPlainText(flux.readAll());
    m_zoneTexte->setDocumentTitle(m_fichier->fileName());
    m_zoneTexte->document()->setModified(false);
    setWindowModified(false);
    setWindowTitle(tr("[*]%1 - Icare").arg(QFileInfo(m_fichier->fileName()).fileName()));
    m_fichier->close();
    QApplication::restoreOverrideCursor();
}

void Window::afficherPreferences() {
    m_pref = new Preferences();
    QObject::connect(m_pref, SIGNAL(settingsChanged()), this, SLOT(rechargerPreferences()));
    m_pref->show();
}

void Window::afficherMenuPlugins() {
    m_wPlugins->show();
}

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

    QString texte = m_zoneTexte->toPlainText();
    m_fichier->write(texte.toUtf8());
    m_fichier->close();
    m_zoneTexte->document()->setModified(false);
    QApplication::restoreOverrideCursor();
}

void Window::enregistrerFichierSous() {
    QString nomFichier = QFileDialog::getSaveFileName(this, tr("Enregistrer un fichier"), ".", "Algorithmes (*.algo);;Tous les fichiers (*);;Fichiers texte (*.txt)");
    if (nomFichier == QString::null)
        return;
    m_fichier->setFileName(nomFichier);
    enregistrerFichier();
    m_zoneTexte->setDocumentTitle(m_fichier->fileName());
    m_zoneTexte->document()->setModified(false);
    setWindowModified(false);
    setWindowTitle(tr("[*]%1 - Icare").arg(QFileInfo(m_fichier->fileName()).fileName()));
}

void Window::nouveauFichier() {
    setWindowTitle(tr("[*]Nouvel algorithme - Icare"));
    m_fichier->setFileName(QString::null);
    m_zoneTexte->document()->clear();
    m_zoneTexte->setDocument(new QTextDocument);
    m_annuler->setEnabled(m_zoneTexte->document()->isUndoAvailable());
    m_refaire->setEnabled(m_zoneTexte->document()->isRedoAvailable());
    m_couper->setEnabled(false);
    m_copier->setEnabled(false);
    documentModifie(true);
}

void Window::closeEvent(QCloseEvent *pE) {
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

void Window::imprimerFichier() {
    QPrintDialog printDialog(this);
    if (printDialog.exec() == QDialog::Accepted) {
        m_zoneTexte->print(printDialog.printer());
    }
}

void Window::showMessage(const QString& pMessage, int pTimeout) {
    m_statusBar->showMessage(pMessage, pTimeout);
}

void Window::rechargerPreferences() {
    emit reloadSettings();
}

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
}

void Window::afficherFenSaisie() {
    FenetreSaisie *fenSaisie = new FenetreSaisie();
    fenSaisie->show();
}

WidgetPlugins* Window::getWPlugins() {
    return m_wPlugins;
}
