#include "analyse.h"
#include "analysesyntaxique.h"
#include "analysesemantique.h"
#include "execution.h"
#include "glossaire.h"

#include <QtCore/QFile>

Analyse *Analyse::_instance = 0;


/** \brief Retourne l'instance en cours si elle existe, sinon, en créé une et la retourne.

  \return Instance actuelle
*/
Analyse *Analyse::getInstance() {
    if (_instance == 0)
        _instance = new Analyse;
    return _instance;
}


/** \brief Détruit l'instance actuelle.
*/
void Analyse::destroy() {
    if (_instance != 0) {
        delete _instance;
        _instance = 0;
    }
}


/** \brief Initialise et connecte les différents modules d'analyse.
*/
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


/** \brief Destructeur.
*/
Analyse::~Analyse() {
    delete m_listeInstruction;
    delete m_glossaire;
    delete m_analyseSyntaxique;
    delete m_analyseSemantique;
    delete m_exec;
}


/** \brief Retourne le glossaire actuel.

  \return Glossaire
*/
Glossaire* Analyse::getGlossaire() const {
    return m_glossaire;
}


/** \brief Retourne la liste d'instructions générée lors de l'analyse syntaxique.

  \return Liste d'instructions
*/
QList<Instruction*>* Analyse::getListeInstruction() const {
    return m_listeInstruction;
}


/** \brief Lance l'analyse syntaxique d'un fichier donné.

  \param pFichier Nom du fichier à analyser
*/
void Analyse::lancerAnalyseSyntaxique(QFile* pFichier) {
    emit sigLancerAnalyseSyntaxique(pFichier);
}


/** \brief Lance l'analyse sémantique du dernier fichier analysé.
*/
void Analyse::lancerAnalyseSemantique() {
    emit sigLancerAnalyseSemantique();
}


/** \brief Lance l'exécution du dernier fichier analysé.

  \param pPasAPas Définit si l'exécution se fait en pas à pas ou non
*/
void Analyse::lancerExecution(bool pPasAPas) {
    emit sigLancerExecution(pPasAPas);
}


/** \brief Indique qu'une saisie a été demandée lors de l'exécution.
*/
void Analyse::emettreSaisie() {
    emit sigSaisir();
}


/** \brief Transmet le résultat de la saisie à l'exécution en cours.

  \param pSaisie Valeur saisie par l'utilisateur
*/
void Analyse::transmettreSaisie(const QString& pSaisie) {
    emit sigSaisie(pSaisie);
}


/** \brief Définit la ligne du début du glossaire, utilisé pour les analyses suivantes.

  \param pNumLigne Numéro de ligne du début du glossaire
*/
void Analyse::setDebutGlossaire(int pNumLigne) {
    m_debutGlossaire = pNumLigne;
}


/** \brief Définit la ligne de fin du glossaire, utilisé pour les analyses suivantes.

  \param pNumLigne Numéro de ligne de fin du glossaire
*/
void Analyse::setFinGlossaire(int pNumLigne) {
    m_finGlossaire = pNumLigne;
}


/** \brief Définit la ligne du début de l'algorithme, utilisé pour les analyses suivantes.

  \param pNumLigne Numéro de ligne du début de l'algorithme
*/
void Analyse::setDebutAlgo(int pNumLigne) {
    m_debutAlgo = pNumLigne;
}


/** \brief Définit la ligne de fin de l'algorithme, utilisé pour les analyses suivantes.

  \param pNumLigne Numéro de ligne de fin de l'algorithme
*/
void Analyse::setFinAlgo(int pNumLigne) {
    m_finAlgo = pNumLigne;
}


/** \brief Retourne la ligne du début du glossaire.

  \return Numéro de ligne du début du glossaire
*/
int Analyse::getDebutGlossaire() const {
    return m_debutGlossaire;
}


/** \brief Retourne la ligne de fin du glossaire.

  \return Numéro de ligne de fin du glossaire
*/
int Analyse::getFinGlossaire() const {
    return m_finGlossaire;
}


/** \brief Retourne la ligne du début de l'algorithme.

  \return Numéro de ligne du début de l'algorithme
*/
int Analyse::getDebutAlgo() const {
    return m_debutAlgo;
}


/** \brief Retourne la ligne de fin de l'algorithme.

  \return Numéro de ligne de fin de l'algorithme
*/
int Analyse::getFinAlgo() const {
    return m_finAlgo;
}

