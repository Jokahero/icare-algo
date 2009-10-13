#include "window.h"

Window::Window() : QMainWindow()
{
    //setMinimumSize(500, 500);
    setWindowTitle(tr("???"));

    m_barreMenu = new QMenuBar (this);

    m_mainMenu = new QMenu (m_barreMenu); // Menu principal
    m_quitter = new QAction (tr("Quitter"), this);
    m_quitter->setShortcut(tr("Ctrl+Q"));

    m_mainMenu->setTitle(tr("&Fichier"));
    m_mainMenu->addAction(m_quitter);

    m_help = new QMenu (m_barreMenu); // Menu d'aide
    m_aPropos = new QAction (tr("A propos de ??? ..."), this);

    m_help->setTitle(tr("&Aide"));
    m_help->addAction(m_aPropos);

    //On met les menus dans la barre de menu
    m_barreMenu->addMenu(m_mainMenu);
    m_barreMenu->addMenu(m_help);

    setMenuBar(m_barreMenu);

    m_widgetPrincipal = new PrincWidget;
    setCentralWidget(m_widgetPrincipal);

    m_fenApropos = new Apropos;
    m_fenApropos->setWindowTitle("A propos de ???");

    QObject::connect(m_aPropos, SIGNAL(triggered()), m_fenApropos, SLOT(show()));

    QObject::connect(m_quitter, SIGNAL(triggered()), qApp, SLOT(quit()));
}

// Window::~Window() {}
