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

    /* Mise en place du menu d'aide */
    m_help = new QMenu (m_barreMenu);
    m_aPropos = new QAction (tr("A propos de Icare ..."), this);
    m_help->setTitle(tr("&Aide"));
    m_help->addAction(m_aPropos);

    /* Insertion des menus dans la barre de Menu */
    m_barreMenu->addMenu(m_mainMenu);
    m_barreMenu->addMenu(m_help);

    /* Definition de la barre de Menu de la fenêtre */
    setMenuBar(m_barreMenu);

    /* Mise en place du Widget principal */
    m_widgetPrincipal = new PrincWidget;
    setCentralWidget(m_widgetPrincipal);

    /* Mise en place de la fenêtre d'�  propos */
    m_fenApropos = new Apropos;
    m_fenApropos->setWindowTitle("A propos de Icare");

    /* Boutons de tests */
    m_testSyntaxe = new QAction (tr("Tester la &syntaxe"), this);
    m_testOperation = new QAction (tr("Tester les &operations"), this);
    m_testComplet = new QAction (tr("Test complet"), this);

    m_executer = new QAction (this);
    m_icone = QIcon("go.png");
    m_executer->setIcon(m_icone);
    m_executer->setToolTip(tr("Executer"));

        /* Test de la toolbar */
    m_barreOutilsTests = new QToolBar;
    m_barreOutilsTests->setMovable(1);

    m_barreOutilsTests->addAction(m_testSyntaxe);
    m_barreOutilsTests->addAction(m_testOperation);
    m_barreOutilsTests->addAction(m_testComplet);
    m_barreOutilsTests->addAction(m_executer);

    addToolBar(m_barreOutilsTests);

    QObject::connect(m_aPropos, SIGNAL(triggered()), m_fenApropos, SLOT(show()));
    QObject::connect(m_quitter, SIGNAL(triggered()), qApp, SLOT(quit()));
    QObject::connect(m_ouvrir, SIGNAL(triggered()), m_widgetPrincipal, SLOT(ouvrirFichier()));
    QObject::connect(m_enregistrer, SIGNAL(triggered()), m_widgetPrincipal, SLOT(enregistrerFichier()));
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
