#include "fenetresaisie.h"
#include <QtGui/QLabel>
#include <QtGui/QTextEdit>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QVBoxLayout>

FenetreSaisie::FenetreSaisie() : QDialog()
{
    m_message = new QLabel(tr("Veuillez saisir une valeur: "));
    m_saisie = new QTextEdit(this);
    m_boutons = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(m_message);
    layout->addWidget(m_saisie);
    layout->addWidget(m_boutons);

    setLayout(layout);

    QObject::connect(m_boutons, SIGNAL(accepted()), this, SLOT(accept()));
    QObject::connect(m_boutons, SIGNAL(rejected()), this, SLOT(reject()));
}

void FenetreSaisie::accept() {

    QDialog::accept();
}
