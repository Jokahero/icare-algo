#include "glossaire.h"

/*! \brief Constructeur par défaut.
*/
Glossaire::Glossaire() {
    m_listeEntier = new QHash<QString, int>;
    m_listeChaine = new QHash<QString, QString>;
    m_listeReel = new QHash<QString, double>;
    m_description = new QHash<QString, QString>;
}

/*! \brief Permet de vérifier l'existance d'une variable.

  Indique si la variable pNomVar a été déclarée ou non.

  \param pNomVar Nom de la variable �  vérifier.
  \return Vrai si la variable existe, faux sinon.
*/
bool Glossaire::existe(QString pNomVar) {
    if (m_listeEntier->contains(pNomVar) || m_listeChaine->contains(pNomVar) || m_listeReel->contains(pNomVar))
        return true;
    return false;
}

/*! \brief Ajoute un entier au glossaire.

  \param pNomVar Nom de l'entier �  ajouter.
  \param pDescription Description de la variable.
  \return Vrai si l'entier a été ajouté, faux si il y a eu une erreur (une variable portant le même nom a déj�  été déclarée, …).
*/
bool Glossaire::ajoutEntier(QString pNomVar, QString pDescription) {
    if (existe(pNomVar)) {
        emit erreur(Analyse::VariableDejaDeclaree);
        qDebug() << "Variable déj�  déclarée";
        return false;
    }
    m_listeEntier->insert(pNomVar, 0);
    m_description->insert(pNomVar, pDescription);
    emit variableAjoutee(pNomVar, "Entier", pDescription);
    return true;
}

/*! \brief Ajoute une chaîne au glossaire.

  \param pNomVar Nom de l'entier �  ajouter.
  \param pDescription Description de la variable.
  \return Vrai si la chaîne a été ajoutée, faux si il y a eu une erreur (une variable portant le même nom a déj�  été déclarée, …).
*/
bool Glossaire::ajoutChaine(QString pNomVar, QString pDescription) {
    if (existe(pNomVar)) {
        emit erreur(Analyse::VariableDejaDeclaree);
        qDebug() << "Variable déj�  déclarée";
        return false;
    }
    m_listeChaine->insert(pNomVar, QString::null);
    m_description->insert(pNomVar, pDescription);
    emit variableAjoutee(pNomVar, "Chaîne", pDescription);
    return true;
}

/*! \brief Ajoute un réel au glossaire.

  \param pNomVar Nom du réel �  ajouter.
  \param pDescription Description de la variable.
  \return Vrai si le réel a été ajouté, faux si il y a eu une erreur (une variable portant le même nom a déj�  été déclarée, …).
*/
bool Glossaire::ajoutReel(QString pNomVar, QString pDescription) {
    if (existe(pNomVar)) {
        emit erreur(Analyse::VariableDejaDeclaree);
        qDebug() << "Variable déj�  déclarée";
        return false;
    }
    m_listeReel->insert(pNomVar, 0);
    m_description->insert(pNomVar, pDescription);
    emit variableAjoutee(pNomVar, "Réel", pDescription);
    return true;
}

/*! \brief Récupère la valeur d'un entier.

  \param pNomVar Nom de la variable a récupérer.
  \return La valeur de la variable récupérée.
*/
int Glossaire::getValeurEntier(QString pNomVar) {
    if (!existe(pNomVar)) {
        emit(erreur(Analyse::VariableNonDeclaree));
        return 0;
    } else if (!m_listeEntier->contains(pNomVar)) {
        emit(erreur(Analyse::TypeIncorrect));
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
        emit(erreur(Analyse::VariableNonDeclaree));
        return 0;
    } else if (!m_listeChaine->contains(pNomVar)) {
        emit(erreur(Analyse::TypeIncorrect));
        return 0;
    } else
        return m_listeChaine->value(pNomVar);
}

/*! \brief Récupère la valeur d'un réel.

  \param pNomVar Nom de la variable a récupérer.
  \return La valeur de la variable récupérée.
*/
double Glossaire::getValeurReel(QString pNomVar) {
    if (!existe(pNomVar)) {
        emit(erreur(Analyse::VariableNonDeclaree));
        return 0;
    } else if (!m_listeReel->contains(pNomVar)) {
        emit(erreur(Analyse::TypeIncorrect));
        return 0;
    } else
        return m_listeReel->value(pNomVar);
}

/*! \brief Définit la valeur d'un entier.

  \param pNomVar Nom de la variable a modifier.
  \param pValeur L'entier �  lui affecter.
*/
void Glossaire::setValeurEntier(QString pNomVar, int pValeur) {
    if (m_listeEntier->contains(pNomVar)) {
        emit variableModifiee(pNomVar, QString::number(pValeur));
        (*m_listeEntier)[pNomVar] = pValeur;
    } else if (existe(pNomVar))
        emit(erreur(Analyse::TypeIncorrect));
    else
        emit(erreur(Analyse::VariableNonDeclaree));
}

/*! \brief Définit la valeur d'une chaîne.

  \param pNomVar Nom de la variable a modifier.
  \param pValeur La chaîne �  lui affecter.
*/
void Glossaire::setValeurChaine(QString pNomVar, QString pValeur) {
    if (m_listeChaine->contains(pNomVar)) {
        emit variableModifiee(pNomVar, pValeur);
        (*m_listeChaine)[pNomVar] = pValeur;
    } else if (existe(pNomVar))
        emit(erreur(Analyse::TypeIncorrect));
    else
        emit(erreur(Analyse::VariableNonDeclaree));
}

/*! \brief Définit la valeur d'un réel.

  \param pNomVar Nom de la variable a modifier.
  \param pValeur Le réel �  lui affecter.
*/
void Glossaire::setValeurReel(QString pNomVar, double pValeur) {
    if (m_listeReel->contains(pNomVar)) {
        emit variableModifiee(pNomVar, QString::number(pValeur));
        (*m_listeReel)[pNomVar] = pValeur;
    } else if (existe(pNomVar))
        emit(erreur(Analyse::TypeIncorrect));
    else
        emit(erreur(Analyse::VariableNonDeclaree));
}






QStringList Glossaire::getListeVariables() {

    return (m_description->keys());
}


















