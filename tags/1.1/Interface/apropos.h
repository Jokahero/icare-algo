#ifndef APROPOS_H
#define APROPOS_H

#include <QtGui/QDialog>

class QDialogButtonBox;
class QLabel;
class QPixmap;
class QPushButton;

/*! \brief Fenêtre «À propos»
*/
class Apropos : public QDialog {
    Q_OBJECT

public:
    Apropos();
    ~Apropos();

private:
    QLabel *m_version;
    QLabel *m_Qt;
    QLabel *m_noms;
    QLabel *m_site;
    QPushButton *m_close;
    QLabel *m_icone;
    QDialogButtonBox *m_buttonBox;

};

#endif // APROPOS_H
