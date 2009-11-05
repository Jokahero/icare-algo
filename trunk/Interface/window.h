#ifndef WINDOW_H
#define WINDOW_H

#include <QtGui>
#include <QtCore>

#include "GUI_global.h"

#include "apropos.h"
#include "princwidget.h"

/*! \brief Fenêtre principale
  */
class Window : public QMainWindow
{
    Q_OBJECT

public:
    Window();

private:
    QMenuBar *m_barreMenu;

    QMenu *m_mainMenu;
    QAction *m_ouvrir;
    QAction *m_enregistrer;
    QAction *m_quitter;

    QMenu *m_help;
    QAction *m_aPropos;

    PrincWidget *m_widgetPrincipal;

    Apropos *m_fenApropos;

    // Tests
    QAction *m_testSyntaxe;
    QAction *m_testOperation;
    QAction *m_testComplet;
    QAction *m_executer;
    QIcon m_icone;

    QToolBar *m_barreOutilsTests;

    public slots:
       void erreurMath(int);

       void execution();

    signals:
       void executer(QFile*);
};
#endif // WINDOW_H
