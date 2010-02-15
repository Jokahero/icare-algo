#ifndef FENETRESAISIE_H
#define FENETRESAISIE_H

#include <QtGui/QDialog>

class QLabel;
class QTextEdit;
class QDialogButtonBox;

class FenetreSaisie : public QDialog
{
public:
    FenetreSaisie();

private:
    QLabel *m_message;
    QTextEdit *m_saisie;
    QDialogButtonBox *m_boutons;

public slots:
    void accept();

};

#endif // FENETRESAISIE_H
