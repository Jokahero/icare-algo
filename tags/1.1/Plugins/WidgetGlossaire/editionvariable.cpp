#include "editionvariable.h"

#include <QtGui/QComboBox>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QFormLayout>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QVBoxLayout>

EditionVariable::EditionVariable(int pType, QString pName, QString pValeur, QString pDesc, QWidget* parent/*=0*/) : QDialog(parent) {
    m_type = new QComboBox(this);
    m_type->addItem("Entier");
    m_type->addItem("Réel");
    m_type->addItem("Chaîne de caractères");
    m_type->setCurrentIndex(pType);

    m_nom = new QLineEdit(this);
    m_nom->setText(pName);
    m_valeur = new QLineEdit(this);
    m_valeur->setText(pValeur);
    m_description = new QLineEdit(this);
    m_description->setText(pDesc);

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

    if (pName == "")
        m_modification = false;
    else
        m_modification = true;
}

/*! Redéfinition de la méthode accept() héritée de QDialog.
  Elle permet de vérifier que les champs nécessaires soient renseignés.

  \brief Redéfinition de la méthode accept() héritée de QDialog.
*/
void EditionVariable::accept() {
    bool valide=true;
    QString error;

    // On vérifie si le nom est renseigné
    if (m_nom->text().isEmpty()) {
        error = "Le nom de la variable doit être renseigné!";
        valide = false;
    }
    // On vérifie si la description est renseignée
    if (m_description->text().isEmpty()) {
        if (valide) {
            error = "La description de la variable doit être renseignée";
            valide = false;
        } else {
            error += "<br/>";
            error += "La description de la variable doit être renseignée!";
        }
    }

    if (!valide) {
        m_errorLabel->setText("<font color=\"red\"><center>" + error + "</center></font>");
    } else {
        // On regarde si l'on est en modification ou en ajout et on envoi le signal approprié
        if (m_modification)
            emit modifier(m_nom->text(), m_valeur->text(), m_type->currentText(), m_description->text(), true);
        else
            emit ajouter(m_nom->text(), m_type->currentText(), m_description->text(), m_valeur->text(), true);

        // On quitte ensuite à l'aide de la méthode accept() de QDialog
        QDialog::accept();
    }
}

/*! Applique un controle de saisie sur champ "valeur" à l'aide d'une expression régulière différente selon le type de la variable actuellement sélectionné.

  \brief Applique une contrôle de saisie sur le champ "valeur".

  \param pIndex Index actuel dans la combobox du type.
*/
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
