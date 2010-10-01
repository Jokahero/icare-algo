#ifndef EDITIONVARIABLE_H
#define EDITIONVARIABLE_H

#include <QtGui/QDialog>

class QComboBox;
class QDialogButtonBox;
class QLabel;
class QLineEdit;

class EditionVariable : public QDialog {
    Q_OBJECT

public:
    EditionVariable();

private:
    QDialogButtonBox* m_buttonBox;

    QComboBox* m_type;
    QLineEdit* m_nom;
    QLineEdit* m_valeur;
    QLineEdit* m_description;
    QLabel* m_errorLabel;

private slots:
    void accept();

    void changeValidator(int pIndex);
};

#endif // EDITIONVARIABLE_H
