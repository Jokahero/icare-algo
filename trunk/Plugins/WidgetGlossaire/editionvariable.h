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
    EditionVariable(int pType=0, QString pName="", QString pValeur="", QString pDesc="", QWidget* parent=0);

private:
    QDialogButtonBox* m_buttonBox;

    QComboBox* m_type;
    QLineEdit* m_nom;
    QLineEdit* m_valeur;
    QLineEdit* m_description;
    QLabel* m_errorLabel;

    bool m_modification;

private slots:
    void accept();

    void changeValidator(int pIndex);

signals:
    void ajouter(QString, QString, QString, QString);
    void modifier(QString, QString, QString, QString);
};

#endif // EDITIONVARIABLE_H
