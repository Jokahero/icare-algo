#ifndef APROPOS_H
#define APROPOS_H

#include <QWidget>
#include <QtGui>
/*! \brief Fenêtre «A propos»
*/
class Apropos : public QWidget
{
    Q_OBJECT

public:
    Apropos();

private:

    QLabel *m_texte;
    QPushButton *m_close;
    QLabel *m_icone;
    QPixmap m_image;

};

#endif // APROPOS_H
