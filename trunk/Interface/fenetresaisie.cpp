#include "fenetresaisie.h"

#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QVBoxLayout>


/*! \brief Constructeur. Définit la fenêtre comme modale.

  L'objet est supprimé dès que le fenêtre est fermée.
*/
FenetreSaisie::FenetreSaisie() : QDialog() {
    setWindowTitle(tr("Saisie"));
    setModal(true);
    setAttribute(Qt::WA_DeleteOnClose);

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


/*! \brief Appelé lors d'un clic sur Ok ou lors de la validation du QLineEdit

  Envoie le signal saisie(texte), où texte est le texte entré par l'utilisateur.
  Ferme ensuite la fenêtre.
*/
void FenetreSaisie::accept() {
    emit saisie(m_saisie->text());
    QDialog::accept();
}
/*! \brief Redéfinie depuis QDialog pour éviter toute annulation de saisie.
  */
void FenetreSaisie::reject() {
}
