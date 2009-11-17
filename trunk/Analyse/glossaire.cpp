#include "glossaire.h"

/*! \brief Constructeur par défaut.
*/
Glossaire::Glossaire() {
    m_listeInt = new QHash<QString, int>;
    m_listeChaine = new QHash<QString, QString>;
    m_listeDouble = new QHash<QString, double>;
}

/*! \brief Permet de vérifier l'existance d'une variable.

  Indique si la variable pNomVar a été déclarée ou non.

  \param pNomVar Nom de la variable à vérifier.
  \return Vrai si la variable existe, faux sinon.
*/
bool Glossaire::existe(QString pNomVar) {
    if (m_listeInt->contains(pNomVar) || m_listeChaine->contains(pNomVar) || m_listeDouble->contains(pNomVar))
        return true;
    return false;
}

/*! \brief Ajoute un entier au glossaire.

  \param pNomVar Nom de l'entier à ajouter.
  \param pValeur Valeur à lui attribuer.
  \return Vrai si l'entier a été ajouté, faux si il y a eu une erreur (une variable portant le même nom a déjà été déclarée, …).
*/
bool Glossaire::ajout(QString pNomVar, int pValeur) {
    if (existe(pNomVar))
        return false;
    m_listeInt->insert(pNomVar, pValeur);
    return true;
}

/*! \brief Ajoute une chaîne au glossaire.

  \param pNomVar Nom de l'entier à ajouter.
  \param pValeur Valeur à lui attribuer.
  \return Vrai si la chaîne a été ajoutée, faux si il y a eu une erreur (une variable portant le même nom a déjà été déclarée, …).
*/
bool Glossaire::ajout(QString pNomVar, QString pValeur) {
    if (existe(pNomVar))
        return false;
    m_listeChaine->insert(pNomVar, pValeur);
    return true;
}

/*! \brief Ajoute un double au glossaire.

  \param pNomVar Nom du double à ajouter.
  \param pValeur Valeur à lui attribuer.
  \return Vrai si le double a été ajouté, faux si il y a eu une erreur (une variable portant le même nom a déjà été déclarée, …).
*/
bool Glossaire::ajout(QString pNomVar, double pValeur) {
    if (existe(pNomVar))
        return false;
    m_listeDouble->insert(pNomVar, pValeur);
    return true;
}
