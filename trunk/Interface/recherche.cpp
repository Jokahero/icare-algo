#include "recherche.h"

#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QVBoxLayout>

Recherche::Recherche(QWidget *parent) : QDialog(parent) {
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



    layoutPrincipal->addLayout(layoutHaut);
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
}

void Recherche::plus(bool pVisible) {
    m_remplacerLa->setVisible(pVisible);
    m_remplacerLe->setVisible(pVisible);
    m_remplacerTout->setVisible(pVisible);
    if (pVisible)
        m_rechercher->setText(tr("Remplacer"));
    else
        m_rechercher->setText(tr("Rechercher"));
}

void Recherche::rec() {
    m_plus->setChecked(false);
    show();
}

void Recherche::rem() {
    m_plus->setChecked(true);
    show();
}

void Recherche::recherche() {
    if (m_rechercher->text() == tr("Rechercher"))
        emit recherche(m_rechercherLe->text());
    else
        emit remplacement(m_rechercherLe->text(), m_remplacerLe->text());
}

void Recherche::remplacerTout() {
    emit remplacerTout(m_rechercherLe->text(), m_remplacerLe->text());
}
