#ifndef FENETRESAISIE_H
#define FENETRESAISIE_H

#include <QtGui/QDialog>

class QDialogButtonBox;
class QLabel;
class QLineEdit;

/*! \brief Fenêtre permettant la saisie d'une variable par l'utilisateur.
*/
class FenetreSaisie : public QDialog {
    Q_OBJECT

public:
    FenetreSaisie(bool pBonType);
    ~FenetreSaisie();

private:
    QLabel *m_message;
    QLabel *m_warning;
    QLineEdit *m_saisie;
    QDialogButtonBox *m_boutons;

public slots:
    void accept();
    void reject();

signals:
    void saisie(QString);
};

#endif // FENETRESAISIE_H
