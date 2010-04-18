#include "glossaire.h"

#include <QtCore/QHash>
#include <QtCore/QStringList>

#include <QtCore/QDebug>


/*! \brief Constructeur par défaut.
*/
Glossaire::Glossaire() {
    m_listeBools = new QHash<QString, bool>;
    m_listeEntier = new QHash<QString, int>;
    m_listeChaine = new QHash<QString, QString>;
    m_listeReel = new QHash<QString, double>;
    m_description = new QHash<QString, QString>;
    m_initialisations = new QHash<QString, bool>;
}

Glossaire::~Glossaire() {
    delete m_listeBools;
    delete m_listeEntier;
    delete m_listeChaine;
    delete m_listeReel;
    delete m_description;
    delete m_initialisations;
}


/*! \brief Permet de vérifier l'existance d'une variable.

  Indique si la variable pNomVar a été déclarée ou non.

  \param pNomVar Nom de la variable à vérifier.
  \return Vrai si la variable existe, faux sinon.
*/
bool Glossaire::existe(const QString& pNomVar) const {
    if (m_listeBools->contains(pNomVar) || m_listeEntier->contains(pNomVar) || m_listeChaine->contains(pNomVar) || m_listeReel->contains(pNomVar))
        return true;
    return false;
}


/*! \brief Ajoute un booléen au glossaire.

  \param pNomVar Nom du booléen à ajouter.
  \param pDescription Description de la variable.
  \return Vrai si le booléen a été ajouté, faux si il y a eu une erreur (une variable portant le même nom a déjà été déclarée, …).
*/
bool Glossaire::ajoutBool(const QString& pNomVar, const QString& pDescription, int pNumLigne) {
    if (existe(pNomVar)) {
        emit erreur(Analyse::VariableDejaDeclaree, pNumLigne);
        return false;
    }
    m_listeBools->insert(pNomVar, 0);
    m_description->insert(pNomVar, pDescription);
    m_initialisations->insert(pNomVar, false);
    emit variableAjoutee(pNomVar, "Booléen", pDescription);
    return true;
}


/*! \brief Ajoute un entier au glossaire.

  \param pNomVar Nom de l'entier à ajouter.
  \param pDescription Description de la variable.
  \return Vrai si l'entier a été ajouté, faux si il y a eu une erreur (une variable portant le même nom a déjà été déclarée, …).
*/
bool Glossaire::ajoutEntier(const QString& pNomVar, const QString& pDescription, int pNumLigne) {
    if (existe(pNomVar)) {
        emit erreur(Analyse::VariableDejaDeclaree, pNumLigne);
        return false;
    }
    m_listeEntier->insert(pNomVar, 0);
    m_description->insert(pNomVar, pDescription);
    m_initialisations->insert(pNomVar, false);
    emit variableAjoutee(pNomVar, "Entier", pDescription);
    return true;
}


/*! \brief Ajoute une chaîne au glossaire.

  \param pNomVar Nom de l'entier à ajouter.
  \param pDescription Description de la variable.
  \return Vrai si la chaîne a été ajoutée, faux si il y a eu une erreur (une variable portant le même nom a déjà été déclarée, …).
*/
bool Glossaire::ajoutChaine(const QString& pNomVar, const QString& pDescription, int pNumLigne) {
    if (existe(pNomVar)) {
        emit erreur(Analyse::VariableDejaDeclaree, pNumLigne);
        return false;
    }
    m_listeChaine->insert(pNomVar, QString::null);
    m_description->insert(pNomVar, pDescription);
    m_initialisations->insert(pNomVar, false);
    emit variableAjoutee(pNomVar, "Chaîne", pDescription);
    return true;
}


/*! \brief Ajoute un réel au glossaire.

  \param pNomVar Nom du réel à ajouter.
  \param pDescription Description de la variable.
  \return Vrai si le réel a été ajouté, faux si il y a eu une erreur (une variable portant le même nom a déjà été déclarée, …).
*/
bool Glossaire::ajoutReel(const QString& pNomVar, const QString& pDescription, int pNumLigne) {
    if (existe(pNomVar)) {
        emit erreur(Analyse::VariableDejaDeclaree, pNumLigne);
        return false;
    }
    m_listeReel->insert(pNomVar, 0);
    m_description->insert(pNomVar, pDescription);
    m_initialisations->insert(pNomVar, false);
    emit variableAjoutee(pNomVar, "Réel", pDescription);
    return true;
}


/*! \brief Récupère la valeur d'un booléen.

  \param pNomVar Nom de la variable à récupérer.
  \return La valeur de la variable récupérée.
*/
bool Glossaire::getValeurBool(const QString& pNomVar) const {
    if (!existe(pNomVar)) {
        emit erreur(Analyse::VariableNonDeclaree);
        return 0;
    } else if (!m_listeBools->contains(pNomVar)) {
        emit erreur(Analyse::TypeIncorrect);
        return 0;
    } else if (!m_initialisations->value(pNomVar)) {
        emit erreur(Analyse::VariableNonInitialisee);
        return 0;
    } else
        return m_listeBools->value(pNomVar);
}


/*! \brief Récupère la valeur d'un entier.

  \param pNomVar Nom de la variable à récupérer.
  \return La valeur de la variable récupérée.
*/
int Glossaire::getValeurEntier(const QString& pNomVar) const {
    if (!existe(pNomVar)) {
        emit erreur(Analyse::VariableNonDeclaree);
        return 0;
    } else if (!m_listeEntier->contains(pNomVar)) {
        emit erreur(Analyse::TypeIncorrect);
        return 0;
    } else if (!m_initialisations->value(pNomVar)) {
        emit erreur(Analyse::VariableNonInitialisee);
        return 0;
    } else
        return m_listeEntier->value(pNomVar);
}


/*! \brief Récupère la valeur d'une chaîne.

  \param pNomVar Nom de la variable à récupérer.
  \return La valeur de la variable récupérée.
*/
QString Glossaire::getValeurChaine(const QString& pNomVar) const {
    if (!existe(pNomVar)) {
        emit erreur(Analyse::VariableNonDeclaree);
        return 0;
    } else if (!m_listeChaine->contains(pNomVar)) {
        emit erreur(Analyse::TypeIncorrect);
        return 0;
    } else if (!m_initialisations->value(pNomVar)) {
        emit erreur(Analyse::VariableNonInitialisee);
        return 0;
    } else
        return m_listeChaine->value(pNomVar);
}


/*! \brief Récupère la valeur d'un réel.

  \param pNomVar Nom de la variable à récupérer.
  \return La valeur de la variable récupérée.
*/
double Glossaire::getValeurReel(const QString& pNomVar) const {
    if (!existe(pNomVar)) {
        emit erreur(Analyse::VariableNonDeclaree);
        return 0;
    } else if (!m_listeReel->contains(pNomVar)) {
        emit erreur(Analyse::TypeIncorrect);
        return 0;
    } else if (!m_initialisations->value(pNomVar)) {
        emit erreur(Analyse::VariableNonInitialisee);
        return 0;
    } else
        return m_listeReel->value(pNomVar);
}


/*! \brief Récupère la valeur d'une variable.

  \param pNomVar Nom de la variable à récupérer.
  \return La valeur de la variable récupérée.
*/
QString Glossaire::getValeur(const QString& pNomVar) const {
    if (!existe(pNomVar)) {
        emit erreur(Analyse::VariableNonDeclaree);
        return QString::null;
    } else if (!m_initialisations->value(pNomVar)) {
        emit erreur(Analyse::VariableNonInitialisee);
        return 0;
    } else if (m_listeEntier->contains(pNomVar))
        return QString::number((*m_listeEntier)[pNomVar]);
    else if (m_listeChaine->contains(pNomVar))
        return (*m_listeChaine)[pNomVar];
    else if (m_listeReel->contains(pNomVar))
        return QString::number((*m_listeReel)[pNomVar]);
    else if (m_listeBools->contains(pNomVar))
        return QString::number((*m_listeBools)[pNomVar]);
    else
        return QString::null;
}


/*! \brief Définit la valeur d'un booléen.

  \param pNomVar Nom de la variable à modifier.
  \param pValeur L'entier à lui affecter.
*/
void Glossaire::setValeurBool(const QString& pNomVar, bool pValeur) {
    if (m_listeBools->contains(pNomVar)) {
        (*m_initialisations)[pNomVar] = true;
        (*m_listeBools)[pNomVar] = pValeur;
        emit variableModifiee(pNomVar, QString::number(pValeur));
    } else if (existe(pNomVar))
        emit erreur(Analyse::TypeIncorrect);
    else
        emit erreur(Analyse::VariableNonDeclaree);
}


/*! \brief Définit la valeur d'un entier.

  \param pNomVar Nom de la variable à modifier.
  \param pValeur L'entier à lui affecter.
*/
void Glossaire::setValeurEntier(const QString& pNomVar, int pValeur) {
    if (m_listeEntier->contains(pNomVar)) {
        (*m_initialisations)[pNomVar] = true;
        (*m_listeEntier)[pNomVar] = pValeur;
        emit variableModifiee(pNomVar, QString::number(pValeur));
    } else if (existe(pNomVar))
        emit erreur(Analyse::TypeIncorrect);
    else
        emit erreur(Analyse::VariableNonDeclaree);
}


/*! \brief Définit la valeur d'une chaîne.

  \param pNomVar Nom de la variable à modifier.
  \param pValeur La chaîne à lui affecter.
*/
void Glossaire::setValeurChaine(const QString& pNomVar, const QString& pValeur) {
    if (m_listeChaine->contains(pNomVar)) {
        (*m_initialisations)[pNomVar] = true;
        (*m_listeChaine)[pNomVar] = pValeur;
        emit variableModifiee(pNomVar, pValeur);
    } else if (existe(pNomVar))
        emit erreur(Analyse::TypeIncorrect);
    else
        emit erreur(Analyse::VariableNonDeclaree);
}


/*! \brief Définit la valeur d'un réel.

  \param pNomVar Nom de la variable à modifier.
  \param pValeur Le réel à lui affecter.
*/
void Glossaire::setValeurReel(const QString& pNomVar, double pValeur) {
    if (m_listeReel->contains(pNomVar)) {
        (*m_initialisations)[pNomVar] = true;
        (*m_listeReel)[pNomVar] = pValeur;
        emit variableModifiee(pNomVar, QString::number(pValeur));
    } else if (existe(pNomVar))
        emit erreur(Analyse::TypeIncorrect);
    else
        emit erreur(Analyse::VariableNonDeclaree);
}


/*! \brief Définit la valeur d'une variable.

  \param pNomVar Nom de la variable à modifier.
  \param pValeur La valeur à lui affecter.
*/
bool Glossaire::setValeur(const QString& pNomVar, const QString& pValeur) {
    bool ok = false;
    if (m_listeEntier->contains(pNomVar)) {
        (*m_initialisations)[pNomVar] = true;
        (*m_listeEntier)[pNomVar] = pValeur.toInt(&ok);
        if (ok)
            emit variableModifiee(pNomVar, pValeur);
    } else if (m_listeChaine->contains(pNomVar)) {
        (*m_initialisations)[pNomVar] = true;
        (*m_listeChaine)[pNomVar] = pValeur;
        ok = true;
        emit variableModifiee(pNomVar, pValeur);
    } else if (m_listeReel->contains(pNomVar)) {
        (*m_initialisations)[pNomVar] = true;
        (*m_listeReel)[pNomVar] = pValeur.toFloat(&ok);
        if (ok)
            emit variableModifiee(pNomVar, pValeur);
    } else if (m_listeBools->contains(pNomVar)) {
        (*m_initialisations)[pNomVar] = true;
        (*m_listeBools)[pNomVar] = pValeur.toInt(&ok);
        if (ok)
            emit variableModifiee(pNomVar, pValeur);
    } else
        emit erreur(Analyse::VariableNonDeclaree);
    return ok;
}


/*! \brief Retourne la liste des noms de variables.

  \return Les noms de toutes les variables.
*/
QStringList Glossaire::getListeVariables() const {
    return m_description->keys();
}


/*! \brief Supprime toutes les entrées du glossaire.
*/
void Glossaire::reinit() {
    m_listeBools->clear();
    m_listeEntier->clear();
    m_listeReel->clear();
    m_listeChaine->clear();
    m_description->clear();
    m_initialisations->clear();
    emit sigReinit();
}
