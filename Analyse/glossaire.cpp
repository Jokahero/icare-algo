#include "glossaire.h"
#include "erreuranalyse.h"

/*! \brief Constructeur par défaut.
*/
Glossaire::Glossaire() {
    m_listeEntier = new QHash<QString, int>;
    m_listeChaine = new QHash<QString, QString>;
    m_listeDouble = new QHash<QString, double>;
    m_description = new QHash<QString, QString>;
}

/*! \brief Permet de vérifier l'existance d'une variable.

  Indique si la variable pNomVar a été déclarée ou non.

  \param pNomVar Nom de la variable à vérifier.
  \return Vrai si la variable existe, faux sinon.
*/
bool Glossaire::existe(QString pNomVar) {
    if (m_listeEntier->contains(pNomVar) || m_listeChaine->contains(pNomVar) || m_listeDouble->contains(pNomVar))
        return true;
    return false;
}

/*! \brief Ajoute un entier au glossaire.

  \param pNomVar Nom de l'entier à ajouter.
  \param pDescription Description de la variable.
  \return Vrai si l'entier a été ajouté, faux si il y a eu une erreur (une variable portant le même nom a déjà été déclarée, …).
*/
bool Glossaire::ajoutEntier(QString pNomVar, QString pDescription) {
    if (existe(pNomVar)) {
        emit erreur(ErreurAnalyse::VariableDejaDeclaree);
        return false;
    }
    m_listeEntier->insert(pNomVar, 0);
    m_description->insert(pNomVar, pDescription);
    return true;
}

/*! \brief Ajoute une chaîne au glossaire.

  \param pNomVar Nom de l'entier à ajouter.
  \param pDescription Description de la variable.
  \return Vrai si la chaîne a été ajoutée, faux si il y a eu une erreur (une variable portant le même nom a déjà été déclarée, …).
*/
bool Glossaire::ajoutChaine(QString pNomVar, QString pDescription) {
    if (existe(pNomVar)) {
        emit erreur(ErreurAnalyse::VariableDejaDeclaree);
        return false;
    }
    m_listeChaine->insert(pNomVar, QString::null);
    m_description->insert(pNomVar, pDescription);
    return true;
}

/*! \brief Ajoute un double au glossaire.

  \param pNomVar Nom du double à ajouter.
  \param pDescription Description de la variable.
  \return Vrai si le double a été ajouté, faux si il y a eu une erreur (une variable portant le même nom a déjà été déclarée, …).
*/
bool Glossaire::ajoutDouble(QString pNomVar, QString pDescription) {
    if (existe(pNomVar)) {
        emit erreur(ErreurAnalyse::VariableDejaDeclaree);
        return false;
    }
    m_listeDouble->insert(pNomVar, 0);
    m_description->insert(pNomVar, pDescription);
    return true;
}

/*! \brief Récupère la valeur d'un entier.

  \param pNomVar Nom de la variable a récupérer.
  \return La valeur de la variable récupérée.
*/
int Glossaire::getValeurEntier(QString pNomVar) {
    if (!existe(pNomVar)) {
        emit(erreur(ErreurAnalyse::VariableNonDeclaree));
        return 0;
    } else if (!m_listeEntier->contains(pNomVar)) {
        emit(erreur(ErreurAnalyse::TypeIncorrect));
        return 0;
    } else
        return m_listeEntier->value(pNomVar);
}

/*! \brief Récupère la valeur d'une chaîne.

  \param pNomVar Nom de la variable a récupérer.
  \return La valeur de la variable récupérée.
*/
QString Glossaire::getValeurChaine(QString pNomVar) {
    if (!existe(pNomVar)) {
        emit(erreur(ErreurAnalyse::VariableNonDeclaree));
        return 0;
    } else if (!m_listeChaine->contains(pNomVar)) {
        emit(erreur(ErreurAnalyse::TypeIncorrect));
        return 0;
    } else
        return m_listeChaine->value(pNomVar);
}

/*! \brief Récupère la valeur d'un double.

  \param pNomVar Nom de la variable a récupérer.
  \return La valeur de la variable récupérée.
*/
double Glossaire::getValeurDouble(QString pNomVar) {
    if (!existe(pNomVar)) {
        emit(erreur(ErreurAnalyse::VariableNonDeclaree));
        return 0;
    } else if (!m_listeDouble->contains(pNomVar)) {
        emit(erreur(ErreurAnalyse::TypeIncorrect));
        return 0;
    } else
        return m_listeDouble->value(pNomVar);
}

/*! \brief Définit la valeur d'un entier.

  \param pNomVar Nom de la variable a modifier.
  \param pValeur L'entier à lui affecter.
*/
void Glossaire::setValeurEntier(QString pNomVar, int pValeur) {
    if (m_listeEntier->contains(pNomVar))
        (*m_listeEntier)[pNomVar] = pValeur;
    else if (existe(pNomVar))
        emit(erreur(ErreurAnalyse::TypeIncorrect));
    else
        emit(erreur(ErreurAnalyse::VariableNonDeclaree));
}

/*! \brief Définit la valeur d'une chaîne.

  \param pNomVar Nom de la variable a modifier.
  \param pValeur La chaîne à lui affecter.
*/
void Glossaire::setValeurChaine(QString pNomVar, QString pValeur) {
    if (m_listeChaine->contains(pNomVar))
        (*m_listeChaine)[pNomVar] = pValeur;
    else if (existe(pNomVar))
        emit(erreur(ErreurAnalyse::TypeIncorrect));
    else
        emit(erreur(ErreurAnalyse::VariableNonDeclaree));
}

/*! \brief Définit la valeur d'un double.

  \param pNomVar Nom de la variable a modifier.
  \param pValeur Le double à lui affecter.
*/
void Glossaire::setValeurDouble(QString pNomVar, double pValeur) {
    if (m_listeDouble->contains(pNomVar))
        (*m_listeDouble)[pNomVar] = pValeur;
    else if (existe(pNomVar))
        emit(erreur(ErreurAnalyse::TypeIncorrect));
    else
        emit(erreur(ErreurAnalyse::VariableNonDeclaree));
}
