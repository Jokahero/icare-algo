#include "fenetresaisie.h"
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QVBoxLayout>

FenetreSaisie::FenetreSaisie() : QDialog() {
    setWindowTitle(tr("Saisie"));
    setModal(true);

    m_message = new QLabel(tr("Veuillez saisir une valeur: "));
    m_saisie = new QLineEdit(this);
    m_boutons = new QDialogButtonBox(QDialogButtonBox::Ok);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(m_message);
    layout->addWidget(m_saisie);
    layout->addWidget(m_boutons);

    setLayout(layout);

    connect(m_boutons, SIGNAL(accepted()), this, SLOT(accept()));
    connect(m_boutons, SIGNAL(rejected()), this, SLOT(reject()));
    connect(m_saisie, SIGNAL(returnPressed()), this, SLOT(accept()));
}

void FenetreSaisie::accept() {
    emit saisie(m_saisie->text());
    QDialog::accept();
}

void FenetreSaisie::reject() {
}
