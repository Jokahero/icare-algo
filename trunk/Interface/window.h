#ifndef WINDOW_H
#define WINDOW_H

#include <QtGui>
#include <QtCore>

#include "apropos.h"
#include "princwidget.h"

class Window : public QMainWindow
{
    Q_OBJECT

public:
    Window();
    // ~Window();

private:

    QMenuBar *m_barreMenu;

    QMenu *m_mainMenu;
    QAction *m_quitter;

    QMenu *m_help;
    QAction *m_aPropos;

    PrincWidget *m_widgetPrincipal;

    Apropos *m_fenApropos;
};
#endif // WINDOW_H
