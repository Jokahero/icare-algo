#include "recherche.h"

#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QVBoxLayout>
#include <QtGui/QCheckBox>

/*! \brief Constructeur. La fenêtre n'est pas modale.

  \param pParent Widget parent
*/
Recherche::Recherche(QWidget *pParent) : QDialog(pParent) {
    m_rechercherLa = new QLabel(tr("Rechercher : "));
    m_rechercherLe = new QLineEdit;
    m_remplacerLa = new QLabel(tr("Remplacer : "));
    m_remplacerLa->setVisible(false);
    m_remplacerLe = new QLineEdit;
    m_remplacerLe->setVisible(false);
    m_rechercher = new QPushButton(tr("Rechercher"));
    m_fermer = new QPushButton(tr("Fermer"));
    m_plus = new QPushButton(tr("Plus…"));
    m_plus->setCheckable(true);
    m_plus->setChecked(false);
    m_remplacerTout = new QPushButton(tr("Remplacer tout"));
    m_remplacerTout->setVisible(false);

    m_caseSensitive = new QCheckBox(tr("Sensible à la casse"), this);
    m_regExp = new QCheckBox(tr("Utiliser des expressions régulières"), this);
    m_motEntier = new QCheckBox(tr("Correspondre seulement avec un mot entier"), this);
    m_debutMot = new QCheckBox(tr("Correspondre avec le début du mot"), this);

    QVBoxLayout* layoutPrincipal = new QVBoxLayout;
    QHBoxLayout* layoutHaut = new QHBoxLayout;
    QGridLayout* layoutRec = new QGridLayout;
    layoutRec->addWidget(m_rechercherLa, 0, 0);
    layoutRec->addWidget(m_rechercherLe, 0, 1);
    layoutRec->addWidget(m_remplacerLa, 1, 0);
    layoutRec->addWidget(m_remplacerLe, 1, 1);

    QVBoxLayout* layoutBoutons = new QVBoxLayout;
    layoutBoutons->addWidget(m_rechercher);
    layoutBoutons->addWidget(m_remplacerTout);
    layoutBoutons->addWidget(m_plus);
    layoutBoutons->addWidget(m_fermer);

    layoutHaut->addLayout(layoutRec);
    layoutHaut->addLayout(layoutBoutons);

    QGridLayout *layoutBas = new QGridLayout;
    layoutBas->addWidget(m_caseSensitive, 0, 0);
    layoutBas->addWidget(m_regExp, 1, 0);
    layoutBas->addWidget(m_motEntier, 0, 1);
    layoutBas->addWidget(m_debutMot, 1, 1);

    layoutPrincipal->addLayout(layoutHaut);
    layoutPrincipal->addLayout(layoutBas);
    setLayout(layoutPrincipal);

    connect(m_plus, SIGNAL(toggled(bool)), this, SLOT(plus(bool)));
    connect(m_fermer, SIGNAL(clicked()), this, SLOT(close()));
    connect(m_rechercher, SIGNAL(clicked()), this, SLOT(recherche()));
    connect(m_rechercherLe, SIGNAL(returnPressed()), m_rechercher, SLOT(click()));
    connect(m_remplacerLe, SIGNAL(returnPressed()), m_rechercher, SLOT(click()));
    connect(m_remplacerTout, SIGNAL(clicked()), this, SLOT(remplacerTout()));
}

Recherche::~Recherche() {
    delete m_rechercherLa;
    delete m_rechercherLe;
    delete m_remplacerLa;
    delete m_remplacerLe;
    delete m_rechercher;
    delete m_fermer;
    delete m_plus;
    delete m_remplacerTout;
    delete m_caseSensitive;
    delete m_regExp;
    delete m_motEntier;
    delete m_debutMot;
}


/*! \brief Affiche/masque une partie de la fenêtre.

  Lorsque pVisible est défini à vrai, le champ et les boutons de remplacement sont affichés. Lorsqu'il est à faux, ils sont masqués.
  \param pVisible Visibilité des widgets de recherche
*/
void Recherche::plus(bool pVisible) {
    m_remplacerLa->setVisible(pVisible);
    m_remplacerLe->setVisible(pVisible);
    m_remplacerTout->setVisible(pVisible);
    if (pVisible)
        m_rechercher->setText(tr("Remplacer"));
    else
        m_rechercher->setText(tr("Rechercher"));
}


/*! \brief Affiche la fenêtre en mode recherche.
*/
void Recherche::rec() {
    m_plus->setChecked(false);
    show();
}


/*! \brief Affiche la fenêtre en mode remplacement.
*/
void Recherche::rem() {
    m_plus->setChecked(true);
    show();
}


/*! \brief Lance une recherche ou un remplacement.

  Si la fenêtre est en mode recherche, le signal recherche(texte) est émit. Sinon, c'est le signal remplacement(texte, texte) qui est émit.
*/
void Recherche::recherche() {
    if (!m_plus->isChecked()) {
        TRecherche t;
        t.recherche = m_rechercherLe->text();
        t.casse = m_caseSensitive->isChecked();
        t.debutMot = m_debutMot->isChecked();
        t.motEntier = m_motEntier->isChecked();
        t.regexp = m_motEntier->isChecked();
        emit recherche(t);
    } else {
        TRecherche t;
        t.recherche = m_rechercherLe->text();
        t.remplacement = m_remplacerLe->text();
        t.casse = m_caseSensitive->isChecked();
        t.debutMot = m_debutMot->isChecked();
        t.motEntier = m_motEntier->isChecked();
        t.regexp = m_motEntier->isChecked();
        emit remplacement(t);
    }
}


/*! \brief Lance un remplacement sur tout l'algorithme.

  Le signal remplacerTout(texte, texte) est émit.
*/
void Recherche::remplacerTout() {
    TRecherche t;
    t.recherche = m_rechercherLe->text();
    t.remplacement = m_remplacerLe->text();
    t.casse = m_caseSensitive->isChecked();
    t.debutMot = m_debutMot->isChecked();
    t.motEntier = m_motEntier->isChecked();
    t.regexp = m_motEntier->isChecked();
    emit remplacerTout(t);
}
