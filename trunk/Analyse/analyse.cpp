#include "analyse.h"
#include "analysesyntaxique.h"
#include "analysesemantique.h"
#include "execution.h"
#include "glossaire.h"

#include <QtCore/QFile>

Analyse *Analyse::_instance = 0;

Analyse *Analyse::getInstance() {
        if (_instance == 0)
                _instance = new Analyse;
        return _instance;
}

void Analyse::destroy() {
    delete _instance;
    _instance = 0;
}

Analyse::Analyse() {
    m_listeInstruction = new QList<Instruction*>;
    m_glossaire = new Glossaire;
    m_analyseSyntaxique = new AnalyseSyntaxique(this);
    m_analyseSemantique = new AnalyseSemantique(this);
    m_exec = new Execution(this);

    m_debutGlossaire = -1;
    m_finGlossaire = -1;
    m_debutAlgo = -1;
    m_finAlgo = -1;

    connect(this, SIGNAL(sigLancerAnalyseSyntaxique(QFile*)), m_analyseSyntaxique, SLOT(lancer(QFile*)));
    connect(this, SIGNAL(sigLancerAnalyseSemantique()), m_analyseSemantique, SLOT(lancer()));
    connect(m_analyseSyntaxique, SIGNAL(terminee(bool)), this, SIGNAL(analyseSyntaxiqueTerminee(bool)));
    connect(m_analyseSemantique, SIGNAL(terminee(bool)), this, SIGNAL(analyseSemantiqueTerminee(bool)));
    connect(this, SIGNAL(sigLancerExecution(bool)), m_exec, SLOT(lancer(bool)));
    connect(this, SIGNAL(execPas()), m_exec, SLOT(pas()));
    connect(this, SIGNAL(execStop()), m_exec, SLOT(stop()));
    connect(this, SIGNAL(execStop()), this, SIGNAL(execPas()));
    connect(m_glossaire, SIGNAL(erreur(Analyse::erreur, int)), this, SIGNAL(sigErreur(Analyse::erreur, int)));
    connect(m_analyseSyntaxique, SIGNAL(erreur(Analyse::erreur, int)), this, SIGNAL(sigErreur(Analyse::erreur, int)));
    connect(m_analyseSemantique, SIGNAL(erreur(Analyse::erreur, int)), this, SIGNAL(sigErreur(Analyse::erreur, int)));
    connect(m_exec, SIGNAL(afficher(QString)), this, SIGNAL(sigAfficher(QString)));
    connect(m_exec, SIGNAL(erreurLogique(ExpressionLogique::erreur, int)), this, SIGNAL(sigErreurLogique(ExpressionLogique::erreur, int)));
    connect(m_exec, SIGNAL(erreurMathematique(MathExp::erreur, int)), this, SIGNAL(sigErreurMathematique(MathExp::erreur, int)));
    connect(m_exec, SIGNAL(terminee()), this, SIGNAL(executionTerminee()));
    connect(m_exec, SIGNAL(changementLigne(int)), this, SIGNAL(changementLigne(int)));
    connect(this, SIGNAL(sigSaisie(QString)), m_exec, SLOT(enregistrerSaisie(QString)));
}

Analyse::~Analyse() {
    delete m_listeInstruction;
    delete m_glossaire;
    delete m_analyseSyntaxique;
    delete m_analyseSemantique;
    delete m_exec;
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

void Analyse::lancerExecution(bool pPasAPas) {
    emit sigLancerExecution(pPasAPas);
}

void Analyse::emettreSaisie() {
    emit sigSaisir();
}

void Analyse::transmettreSaisie(QString pSaisie) {
    emit sigSaisie(pSaisie);
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

