#ifndef PRINCWIDGET_H
#define PRINCWIDGET_H

#include <QtGui>
#include <QWidget>

#include "textedit.h"

class PrincWidget : public QWidget
{

public:
    PrincWidget();

    // Tests
    QPushButton *m_testSyntaxe;
    QPushButton *m_testOperation;
    QPushButton *m_testComplet;

    // Selection du fichier
    QLineEdit *m_fichier;
    QPushButton *m_parcourir;

    // Modification du fichier
    TextEdit *m_zoneTexte;

    QPushButton *m_quitter;


};

#endif // PRINCWIDGET_H
