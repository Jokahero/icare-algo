#include "window.h"
#include "../ExpressionsMathematiques/erreur.h"

Window::Window() : QMainWindow()
{
    //setMinimumSize(500, 500);
    setWindowTitle(tr("Icare"));

    /* On instancie la barre de Menu */
    m_barreMenu = new QMenuBar (this);

    /* Mise en place du menu principal */
    m_mainMenu = new QMenu (m_barreMenu);
    m_ouvrir = new QAction(tr("Ouvrir"), this);
    m_ouvrir->setShortcut(tr("Ctrl+O"));
    m_enregistrer = new QAction(tr("Enregistrer"), this);
    m_enregistrer->setShortcut(tr("Ctrl+S"));
    m_quitter = new QAction (tr("Quitter"), this);
    m_quitter->setShortcut(tr("Ctrl+Q"));
    m_mainMenu->setTitle(tr("&Fichier"));
    m_mainMenu->addAction(m_ouvrir);
    m_mainMenu->addSeparator();
    m_mainMenu->addAction(m_enregistrer);
    m_mainMenu->addAction(m_quitter);

    /* Mise en place du menu d'options */
    m_menuOptions= new QMenu (m_barreMenu);
    m_plugins = new QAction(tr("Plu&gins..."), this);
    m_preferences = new QAction(tr("&Préférences..."), this);

    /* Mise en place du menu d'aide */
    m_help = new QMenu (m_barreMenu);
    m_aPropos = new QAction (tr("A propos de Icare ..."), this);
    m_help->setTitle(tr("&Aide"));
    m_help->addAction(m_aPropos);

    /* Insertion des menus dans la barre de Menu */
    m_barreMenu->addMenu(m_mainMenu);
    m_barreMenu->addMenu(m_menuOptions);
    m_barreMenu->addMenu(m_help);

    /* Definition de la barre de Menu de la fenÃªtre */
    setMenuBar(m_barreMenu);

    /* Mise en place du Widget principal */
    m_zoneTexte = new TextEdit;
    setCentralWidget(m_zoneTexte);
    m_fichier = new QFile(this);

    /* Boutons de tests */
    m_testSyntaxe = new QAction (tr("Tester la &syntaxe"), this);
    m_testOperation = new QAction (tr("Tester les &opérations"), this);
    m_testComplet = new QAction (tr("Test complet"), this);

    m_executer = new QAction (this);
    m_icone = QIcon("go.png");
    m_executer->setIcon(m_icone);
    m_executer->setToolTip(tr("Exécuter"));

    /* Mise en place de la barre d'outils des fichiers */
    m_barreOutilsFichier = new QToolBar;
    m_barreOutilsFichier->setMovable(1);

    // Ajout des actions dans la barre d'outils
    m_barreOutilsFichier->addAction(m_ouvrir);
    m_barreOutilsFichier->addAction(m_enregistrer);

    addToolBar(m_barreOutilsFichier);

    /* Mise en place de la barre d'outils des tests */
    m_barreOutilsTests = new QToolBar;
    m_barreOutilsTests->setMovable(1);

    // Ajout des actions dans la barre d'outils
    m_barreOutilsTests->addAction(m_testSyntaxe);
    m_barreOutilsTests->addAction(m_testOperation);
    m_barreOutilsTests->addAction(m_testComplet);
    m_barreOutilsTests->addAction(m_executer);

    addToolBar(m_barreOutilsTests);

    QObject::connect(m_aPropos, SIGNAL(triggered()), this, SLOT(afficherApropos()));
    QObject::connect(m_quitter, SIGNAL(triggered()), qApp, SLOT(quit()));
    QObject::connect(m_ouvrir, SIGNAL(triggered()), this, SLOT(ouvrirFichier()));
    QObject::connect(m_enregistrer, SIGNAL(triggered()), this, SLOT(enregistrerFichier()));
    QObject::connect(m_executer, SIGNAL(triggered()), this, SLOT(execution()));

}

void Window::erreurMath(int pCodeErreur)
{
    if(pCodeErreur == Erreur::DivisionParZero)
        QMessageBox::information(this, "Erreur", "Division par zero");
    else
        QMessageBox::information(this, "Erreur", "Erreur inconnue");
}

void Window::execution()
{
    //emit executer()
}

void Window::afficherApropos()
{
    /* Mise en place de la fenêtre d'Ã  propos */
    m_fenApropos = new Apropos;
    m_fenApropos->setWindowTitle("A propos de Icare");
    m_fenApropos->show();
}


void Window::ouvrirFichier()
{
    QString nomFichier = QFileDialog::getOpenFileName(this, tr("Ouvrir un fichier"), ".", "Algorithmes (*.algo);;Tous les fichiers (*);;Fichiers texte (*.txt)");

    ouvrirFichier(nomFichier);
}

void Window::ouvrirFichier(QString pNomFichier)
{
    m_fichier->setFileName(pNomFichier);

    if(!m_fichier->open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    //On créer un flux de texte
    QTextStream flux(m_fichier);
    m_zoneTexte->setPlainText(flux.readAll());
    m_fichier->close();
}

void Window::enregistrerFichier()
{
    if(!m_fichier->open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QString texte = m_zoneTexte->toPlainText();
    m_fichier->write(texte.toLocal8Bit());
    m_fichier->close();
}
