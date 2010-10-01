#include "editionvariable.h"

#include <QtGui/QComboBox>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QFormLayout>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QVBoxLayout>

EditionVariable::EditionVariable() {
    m_type = new QComboBox(this);
    m_type->addItem("Entier");
    m_type->addItem("Réel");
    m_type->addItem("Chaîne de caractères");

    m_nom = new QLineEdit(this);
    m_valeur = new QLineEdit(this);
    m_description = new QLineEdit(this);

    QFormLayout *formLayout = new QFormLayout();
    formLayout->addRow("Type :", m_type);
    formLayout->addRow("Nom :", m_nom);
    formLayout->addRow("Valeur :", m_valeur);
    formLayout->addRow("Description: ", m_description);

    m_buttonBox = new QDialogButtonBox(QDialogButtonBox::Cancel | QDialogButtonBox::Ok, Qt::Horizontal, this);

    m_errorLabel = new QLabel(this);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addLayout(formLayout);
    layout->addWidget(m_buttonBox);
    layout->addWidget(m_errorLabel);

    connect(m_type, SIGNAL(currentIndexChanged(int)), this, SLOT(changeValidator(int)));

    connect(m_buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(m_buttonBox, SIGNAL(rejected()), this, SLOT(reject()));

    changeValidator(m_type->currentIndex());
}

void EditionVariable::accept() {
    bool valide=true;
    QString error;
    if (m_nom->text().isEmpty()) {
        error = "Le nom de la variable doit être renseigné!";
        valide = false;
    }
    if (m_description->text().isEmpty())
        if (valide) {
            error = "La description de la variable doit être renseignée";
            valide = false;
        } else {
            error += "<br/>";
            error += "La description de la variable doit être renseignée!";
        }


    if (!valide) {
        m_errorLabel->setText("<font color=\"red\"><center>" + error + "</center></font>");
    } else
        QDialog::accept();
}

void EditionVariable::changeValidator(int pIndex) {
    QRegExp regexp;
    switch (pIndex) {
    case 0:
        regexp.setPattern("\\d*");
        break;

    case 1:
        regexp.setPattern("\\d*\\.\\d*");
        break;

    case 2:
        regexp.setPattern(".*");
        break;
    }
    QRegExpValidator * validator  = new QRegExpValidator(regexp,0);
    m_valeur->setValidator(validator);
}
