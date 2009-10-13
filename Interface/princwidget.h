#ifndef PRINCWIDGET_H
#define PRINCWIDGET_H

#include <QtGui>
#include <QWidget>

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



};

#endif // PRINCWIDGET_H
