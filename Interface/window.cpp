#include "window.h"

Window::Window() : QMainWindow()
{
    //setMinimumSize(500, 500);
    setWindowTitle(tr("Icare"));

    /* On instancie la barre de Menu */
    m_barreMenu = new QMenuBar (this);

    /* Mise en place du menu principal */
    m_mainMenu = new QMenu (m_barreMenu);
    m_quitter = new QAction (tr("Quitter"), this);
    m_quitter->setShortcut(tr("Ctrl+Q"));
    m_mainMenu->setTitle(tr("&Fichier"));
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

    /* Mise en place de la fenêtre d'à propos */
    m_fenApropos = new Apropos;
    m_fenApropos->setWindowTitle("A propos de Icare");

    QObject::connect(m_aPropos, SIGNAL(triggered()), m_fenApropos, SLOT(show()));
    QObject::connect(m_quitter, SIGNAL(triggered()), qApp, SLOT(quit()));
}

// Window::~Window() {}
