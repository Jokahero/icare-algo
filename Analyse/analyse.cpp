#include "analyse.h"
#include "analysesyntaxique.h"
#include "analysesemantique.h"

Analyse::Analyse() {
    m_glossaire = new Glossaire;
    m_dictionnaire = new Dictionnaire;
    m_analyseSyntaxique = new AnalyseSyntaxique(this);
    m_analyseSemantique = new AnalyseSemantique(this);

    QObject::connect(this, SIGNAL(sigLancerAnalyseSyntaxique(QFile*)), m_analyseSyntaxique, SLOT(lancer(QFile*)));
}

Glossaire* Analyse::getGlossaire() {
    return m_glossaire;
}

void Analyse::lancerAnalyseSyntaxique(QFile* pFichier) {
    emit sigLancerAnalyseSyntaxique(pFichier);
}

void Analyse::lancerAnalyseSemantique(QFile *pFichier) {
    emit sigLancerAnalyseSemantique(pFichier);
}
