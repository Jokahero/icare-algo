#ifndef APROPOS_H
#define APROPOS_H

#include <QtGui/QWidget>

class QLabel;
class QPixmap;
class QPushButton;

/*! \brief Fenêtre «À propos»
*/
class Apropos : public QWidget {
    Q_OBJECT

public:
    Apropos();
    ~Apropos();

private:
    QLabel *m_texte;
    QPushButton *m_close;
    QLabel *m_icone;
    QPixmap m_image;

};

#endif // APROPOS_H
