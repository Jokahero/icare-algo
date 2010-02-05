#include "window.h"

#include <QtCore/QFile>
#include <QtCore/QSettings>
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
Window::Window() : QMainWindow()
{
    /* On récupère la taille et la position de la fenêtre
       telle qu'elle était lorsque l'utilisateur l'a fermée la derniere fois */
    QSettings settings;
    if(!settings.value("Maximized", false).toBool()) {
        restoreGeometry(settings.value("Size").toByteArray());
    }

    /* On nomme la fenêtre principale */
    setWindowTitle(tr("Icare"));

    /* On instancie la barre de Menu */
    m_barreMenu = new QMenuBar (this);

    /* Mise en place du menu principal */
    /* On instancie et on ajoute des paramètres (nom, raccourci clavier ...) aux objets du menu */
    m_mainMenu = new QMenu (m_barreMenu);
    m_ouvrir = new QAction(tr("Ouvrir"), this);
    m_ouvrir->setShortcut(tr("Ctrl+O"));
    m_enregistrer = new QAction(tr("Enregistrer"), this);
    m_enregistrer->setShortcut(tr("Ctrl+S"));
    m_imprimer = new QAction(tr("Imprimer"), this);
    m_imprimer->setShortcut(tr("Ctrl+P"));
    m_quitter = new QAction(tr("Quitter"), this);
    m_quitter->setShortcut(tr("Ctrl+Q"));
    m_mainMenu->setTitle(tr("&Fichier"));
    m_mainMenu->addAction(m_ouvrir);
    m_mainMenu->addAction(m_enregistrer);
    m_mainMenu->addSeparator();
    m_mainMenu->addAction(m_imprimer);
    m_mainMenu->addSeparator();
    m_mainMenu->addAction(m_quitter);

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
    m_barreMenu->addMenu(m_menuAnalyse);
    m_barreMenu->addMenu(m_menuOptions);
    m_barreMenu->addMenu(m_help);

    /* Definition de la barre de Menu de la fenêtre */
    /* On ajoute la barre de menu à la fenêtre */
    setMenuBar(m_barreMenu);

    /* Mise en place du Widget principal */
    m_zoneTexte = new TextEdit;
    setCentralWidget(m_zoneTexte);
    m_fichier = new QFile(this);

    /* Mise en place d'icône et de tooltips sur les boutons des barres d'outils */
    m_icone = QIcon(":/Icônes/go.png");
    m_executer->setIcon(m_icone);
    m_executer->setToolTip(tr("Exécuter"));

    /* Mise en place de la barre d'outils des fichiers */
    m_barreOutilsFichier = new QToolBar;
    m_barreOutilsFichier->setMovable(1);
    m_barreOutilsFichier->setWindowTitle("Fichiers");

    // Ajout des actions dans la barre d'outils
    m_barreOutilsFichier->addAction(m_ouvrir);
    m_barreOutilsFichier->addAction(m_enregistrer);
    m_barreOutilsFichier->addAction(m_imprimer);

    addToolBar(m_barreOutilsFichier);

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
    QObject::connect(m_aPropos, SIGNAL(triggered()), this, SLOT(afficherApropos()));
    QObject::connect(m_quitter, SIGNAL(triggered()), qApp, SLOT(quit()));
    QObject::connect(m_ouvrir, SIGNAL(triggered()), this, SLOT(ouvrirFichier()));
    QObject::connect(m_enregistrer, SIGNAL(triggered()), this, SLOT(enregistrerFichier()));
    QObject::connect(m_imprimer, SIGNAL(triggered()), this, SLOT(imprimerFichier()));
    QObject::connect(m_testSyntaxe, SIGNAL(triggered()), this, SLOT(analyseSyntaxique()));
    QObject::connect(m_testSemantique, SIGNAL(triggered()), this, SLOT(analyseSemantique()));
    QObject::connect(m_executer, SIGNAL(triggered()), this, SLOT(execution()));
    QObject::connect(m_preferences, SIGNAL(triggered()), this, SLOT(afficherPreferences()));
    QObject::connect(m_plugins, SIGNAL(triggered()), this, SLOT(afficherMenuPlugins()));
    QObject::connect(qApp, SIGNAL(aboutToQuit()), this, SLOT(quitter()));
    QObject::connect(this, SIGNAL(sigChangementLigne(int)), m_zoneTexte, SLOT(changementLigne(int)));
}

void Window::erreurMath(MathExp::erreur pCodeErreur)
{
    if(pCodeErreur == MathExp::DivisionParZero)
        QMessageBox::information(this, "Erreur", "Division par zero");
    else
        QMessageBox::information(this, "Erreur", "Erreur inconnue");
}

void Window::execution()
{
    emit executer();
}

void Window::analyseSyntaxique() {
    showMessage(tr("Début de l'analyse syntaxique du fichier %1…").arg(QFileInfo(m_fichier->fileName()).fileName()), 2000);
    emit lancerAnalyseSyntaxique(m_fichier);
}

void Window::analyseSemantique() {
    emit lancerAnalyseSemantique();
}

void Window::afficherApropos()
{
    /* Mise en place de la fenêtre d'à propos */
    m_fenApropos = new Apropos;
    m_fenApropos->setWindowTitle("A propos de Icare");
    m_fenApropos->show();
}

/*! \brief Ouverture d'un fichier.
  Cette fonction sans paramètre ouvre une boîte de dialogue permettant d'ouvrir un fichier existant
  et d'insérer son contenu dans la zone de texte.
*/
void Window::ouvrirFichier()
{
    QString nomFichier = QFileDialog::getOpenFileName(this, tr("Ouvrir un fichier"), ".", "Algorithmes (*.algo);;Tous les fichiers (*);;Fichiers texte (*.txt)");

    ouvrirFichier(nomFichier);
}

/*! \brief Ouverture d'un fichier.
  Cette fonction ouvre le fichier passé en paramètre et insère son contenu dans la zone de texte.
  \param pNomFichier Nom du fichier à ouvrir.
*/
void Window::ouvrirFichier(QString pNomFichier)
{
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

    //On créer un flux de texte
    QTextStream flux(m_fichier);
    m_zoneTexte->setPlainText(flux.readAll());
    m_zoneTexte->setDocumentTitle(m_fichier->fileName());
    m_fichier->close();
}

void Window::afficherPreferences()
{
    m_pref = new Preferences();
    QObject::connect(m_pref, SIGNAL(settingsChanged()), this, SLOT(rechargerPreferences()));
    m_pref->show();
}

void Window::afficherMenuPlugins() {
    m_wPlugins = new WidgetPlugins();
    m_wPlugins->show();
}

void Window::enregistrerFichier() {
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
}

void Window::quitter()
{
    QSettings settings;
    settings.setValue("Size", saveGeometry());
    settings.setValue("Maximized", isMaximized());
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
