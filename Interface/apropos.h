#ifndef APROPOS_H
#define APROPOS_H

#include <QWidget>
#include <QtGui>

class Apropos : public QWidget
{
    Q_OBJECT

public:
    Apropos();

private:

    QLabel *m_texte;
    QPushButton *m_close;
};

#endif // APROPOS_H
