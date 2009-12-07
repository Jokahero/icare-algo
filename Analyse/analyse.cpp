#include "analyse.h"
#include "analysesyntaxique.h"
#include "analysesemantique.h"

Analyse::Analyse() {
    m_listeInstruction = new QList<Instruction*>;
    m_glossaire = new Glossaire;
    m_dictionnaire = new Dictionnaire;
    m_analyseSyntaxique = new AnalyseSyntaxique(this);
    m_analyseSemantique = new AnalyseSemantique(this);

    m_debutGlossaire = -1;
    m_finGlossaire = -1;
    m_debutAlgo = -1;
    m_finAlgo = -1;

    QObject::connect(this, SIGNAL(sigLancerAnalyseSyntaxique(QFile*)), m_analyseSyntaxique, SLOT(lancer(QFile*)));
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

void Analyse::lancerAnalyseSemantique(QFile *pFichier) {
    emit sigLancerAnalyseSemantique(pFichier);
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
    return m_debutGlossaire;
}

int Analyse::getFinAlgo() {
    return m_finAlgo;
}
