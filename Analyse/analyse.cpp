#include "analyse.h"
#include "analysesyntaxique.h"
#include "analysesemantique.h"
#include "glossaire.h"

#include <QtCore/QFile>

Analyse *Analyse::_instance = 0;

Analyse *Analyse::getInstance() {
        if (_instance == 0)
                _instance = new Analyse;
        return _instance;
}

Analyse::Analyse() {
    m_listeInstruction = new QList<Instruction*>;
    m_glossaire = new Glossaire;
    m_analyseSyntaxique = new AnalyseSyntaxique(this);
    m_analyseSemantique = new AnalyseSemantique(this);

    m_debutGlossaire = -1;
    m_finGlossaire = -1;
    m_debutAlgo = -1;
    m_finAlgo = -1;

    QObject::connect(this, SIGNAL(sigLancerAnalyseSyntaxique(QFile*)), m_analyseSyntaxique, SLOT(lancer(QFile*)));
    QObject::connect(this, SIGNAL(sigLancerAnalyseSemantique()), m_analyseSemantique, SLOT(lancer()));
    QObject::connect(m_glossaire, SIGNAL(erreur(Analyse::erreur, int)), this, SIGNAL(sigErreur(Analyse::erreur, int)));
    QObject::connect(m_analyseSyntaxique, SIGNAL(erreur(Analyse::erreur, int)), this, SIGNAL(sigErreur(Analyse::erreur, int)));
    QObject::connect(m_analyseSemantique, SIGNAL(erreur(Analyse::erreur, int)), this, SIGNAL(sigErreur(Analyse::erreur, int)));
}

Glossaire* Analyse::getGlossaire() {
    return m_glossaire;
}

QList<Instruction*>* Analyse::getListeInstruction() {
    return m_listeInstruction;
}

void Analyse::lancerAnalyseSyntaxique(QFile* pFichier) {
    emit sigLancerAnalyseSyntaxique(pFichier);
}

void Analyse::lancerAnalyseSemantique() {
    emit sigLancerAnalyseSemantique();
}

void Analyse::setDebutGlossaire(int pNumLigne) {
    m_debutGlossaire = pNumLigne;
}

void Analyse::setFinGlossaire(int pNumLigne) {
    m_finGlossaire = pNumLigne;
}

void Analyse::setDebutAlgo(int pNumLigne) {
    m_debutAlgo = pNumLigne;
}

void Analyse::setFinAlgo(int pNumLigne) {
    m_finAlgo = pNumLigne;
}

int Analyse::getDebutGlossaire() {
    return m_debutGlossaire;
}

int Analyse::getFinGlossaire() {
    return m_finGlossaire;
}

int Analyse::getDebutAlgo() {
    return m_debutAlgo;
}

int Analyse::getFinAlgo() {
    return m_finAlgo;
}
