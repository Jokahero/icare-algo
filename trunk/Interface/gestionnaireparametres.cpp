#include "gestionnaireparametres.h"

#include <QtCore/QByteArray>
#include <QtCore/QSettings>
#include <QtCore/QStringList>
#include <QtGui/QColor>

GestionnaireParametres *GestionnaireParametres::_instance = 0;


/*! \brief Constructeur. Initialise le QSettings.
*/
GestionnaireParametres::GestionnaireParametres() {
    m_set = new QSettings;
}


/*! \brief Destructeur. Synchronise les paramètres avant la fermeture.
*/
GestionnaireParametres::~GestionnaireParametres() {
    m_set->sync();
    delete m_set;
}


/*! \brief Retourne l'instance de la classe, en créé une si il n'y en a pas.

  \return Instance existante ou nouvelle instance.
*/
GestionnaireParametres *GestionnaireParametres::getInstance() {
    if (_instance == 0)
        _instance = new GestionnaireParametres;
    return _instance;
}


/*! \brief Détruit l'instance actuelle.
*/
void GestionnaireParametres::destroy() {
    delete _instance;
    _instance = 0;
}


/*! \brief Indique si la numérotation des lignes est activée ou non.

  Elle est activée par défaut.
  \return Vrai si elle est activée, faux sinon
*/
bool GestionnaireParametres::getNumerotationLignes() const {
    return m_set->value("Editeur/NumerotationLignes", true).toBool();
}


/*! \brief Définit si la numérotation des lignes est activée ou non.

  \param pNum État d'activation
*/
void GestionnaireParametres::setNumerotationLignes(bool pNum) {
    m_set->beginGroup("Editeur");
    m_set->setValue("NumerotationLignes", pNum);
    m_set->endGroup();
}


/*! \brief Indique si les lignes retournent automatiquement au début de l'éditeur ou non.

  Par défaut, aucun retour à la ligne n'est effectué.
  \return Vrai si un retour à la ligne est effectué, faux sinon
*/
bool GestionnaireParametres::getRetourLigne() const {
    return m_set->value("Editeur/RetourLigne", false).toBool();
}


/*! \brief Définit si les lignes retournent automatiquement au début de l'éditeur ou non.

  \param pRet Vrai si un retour à la ligne est effectué, faux sinon
*/
void GestionnaireParametres::setRetourLigne(bool pRet) {
    m_set->beginGroup("Editeur");
    m_set->setValue("RetourLigne", pRet);
    m_set->endGroup();
}


/*! \brief Retourne la taille (en espaces) d'une tabulation.

  Par défaut, une tabulation est de la même taille que 8 espaces.
  \return Taille d'une tabulation
*/
int GestionnaireParametres::getTailleTab() const {
    return m_set->value("Editeur/TailleTab", 8).toInt();
}


/*! \brief Définit la taille (en espaces) d'une tabulation.

  \param pTaille Taille d'une tabulation en espaces
*/
void GestionnaireParametres::setTailleTab(int pTaille) {
    m_set->beginGroup("Editeur");
    m_set->setValue("TailleTab", pTaille);
    m_set->endGroup();
}


/*! \brief Retourne la couleur de surlignage de la ligne actuelle dans l'éditeur.

  Par défaut, il s'agit d'un gris clair (#f0f0f0).
  \return Couleur de surlignage
*/
QColor GestionnaireParametres::getCouleurLigneActuelle() const {
    return QColor(m_set->value("Couleurs/LigneActuelle", "#f0f0f0").toString());
}


/*! \brief Définit la couleur de surlignage de la ligne actuelle dans l'éditeur.

  \param pCol Couleur de surlignage
*/
void GestionnaireParametres::setCouleurLigneActuelle(const QColor& pCol) {
    m_set->beginGroup("Couleurs");
    m_set->setValue("LigneActuelle", pCol.name());
    m_set->endGroup();
}


/*! \brief Retourne la couleur de coloration des commentaires.

  Par défaut, ils sont en rouge (#d00000).
  \return Couleur des commentaires
*/
QColor GestionnaireParametres::getCouleurCommentaires() const {
    return QColor(m_set->value("Couleurs/Commentaires", "#d00000").toString());
}


/*! \brief Définit la couleur des commentaires.

  \param pCol Couleur des commentaires
*/
void GestionnaireParametres::setCouleurCommentaires(const QColor& pCol) {
    m_set->beginGroup("Couleurs");
    m_set->setValue("Commentaires", pCol.name());
    m_set->endGroup();
}

/*! \brief Retourne la couleur de coloration des chaînes de caractères.

  Par défaut, elles sont en vert (#00ff00).
  \return Couleur des chaînes de caractères.
*/
QColor GestionnaireParametres::getCouleurChaines() const {
    return QColor(m_set->value("Couleurs/Chaines", "#00ff00").toString());
}

/*! \brief Définit la couleur des chaînes de caractères.

  \param pCol Couleur des chaînes de caractères.
*/
void GestionnaireParametres::setCouleurChaines(const QColor& pCol) {
    m_set->beginGroup("Couleurs");
    m_set->setValue("Chaines", pCol.name());
    m_set->endGroup();
}

/*! \brief Retourne la couleur de coloration des différents types.

  Par défaut, ils sont en bleu (#00007f).
  \return Couleur des types
*/
QColor GestionnaireParametres::getCouleurTypes() const {
    return QColor(m_set->value("Couleurs/Types", "#00007f").toString());
}


/*! \brief Définit la couleur des types.

  \param pCol Couleur des types
*/
void GestionnaireParametres::setCouleurTypes(const QColor& pCol) {
    m_set->beginGroup("Couleurs");
    m_set->setValue("Types", pCol.name());
    m_set->endGroup();
}


/*! \brief Retourne la couleur de coloration des nombres.

  Par défaut, ils sont en vert (#007f00).
  \return Couleur des nombres
*/
QColor GestionnaireParametres::getCouleurNombres() const {
    return QColor(m_set->value("Couleurs/Nombres", "#007f00").toString());
}


/*! \brief Définit la couleur des nombres.

  \param pCol Couleur des nombres
*/
void GestionnaireParametres::setCouleurNombres(const QColor& pCol) {
    m_set->beginGroup("Couleurs");
    m_set->setValue("Nombres", pCol.name());
    m_set->endGroup();
}


/*! \brief Retourne la couleur de coloration des structures de contrôle.

  Par défaut, ils sont en bleu (#00007f).
  \return Couleur des structures de contrôle
*/
QColor GestionnaireParametres::getCouleurStructures() const {
    return QColor(m_set->value("Couleurs/Structures", "#00007f").toString());
}


/*! \brief Définit la couleur des structures de contrôle.

  \param pCol Couleur des structures de contrôle
*/
void GestionnaireParametres::setCouleurStructures(const QColor& pCol) {
    m_set->beginGroup("Couleurs");
    m_set->setValue("Structures", pCol.name());
    m_set->endGroup();
}


/*! \brief Retourne la couleur des bornes de l'algorithme.

  Par défaut, elles sont en rouge (#7f0000).
  \return Couleur des bornes de l'algorithme
*/
QColor GestionnaireParametres::getCouleurBornes() const {
    return QColor(m_set->value("Couleurs/Bornes", "#7f0000").toString());
}


/*! \brief Définit la couleur des bornes de l'algorithme.

  \param pCol Couleur des bornes de l'algorithme
*/
void GestionnaireParametres::setCouleurBornes(const QColor& pCol) {
    m_set->beginGroup("Couleurs");
    m_set->setValue("Bornes", pCol.name());
    m_set->endGroup();
}


/*! \brief Retourne l'état d'activation d'un plugin.

  \param pNom Nom du plugin à vérifier
  \return Vrai si le plugin est activé, faux sinon
*/
bool GestionnaireParametres::getPluginActif(const QString& pNom) const {
    return m_set->value("Plugins/" + pNom + "/Actif", true).toBool();
}


/*! \brief Définit si un plugin est actif.

  \param pNom Nom du plugin à (dés)activer
  \param pActif État d'activation du plugin
*/
void GestionnaireParametres::setPluginActif(const QString& pNom, bool pActif) {
    m_set->beginGroup("Plugins");
    m_set->beginGroup(pNom);
    m_set->setValue("Actif", pActif);
    m_set->endGroup();
    m_set->endGroup();
}


/*! \brief Retourne l'état de maximisation de la fenêtre principale.

  \return Vrai si elle est maximisée, faux sinon
*/
bool GestionnaireParametres::getFenetreMax() const {
    return m_set->value("Fenetre/Max", true).toBool();
}


/*! \brief Définit l'état de maximisation de la fenêtre principale.

  \param pMax État de maximisation
*/
void GestionnaireParametres::setFenetreMax(bool pMax) {
    m_set->beginGroup("Fenetre");
    m_set->setValue("Max", pMax);
    m_set->endGroup();
}


/*! \brief Retourne la géométrie de la fenêtre principale.

  \return Géométrie de la fenêtre principale
*/
QByteArray GestionnaireParametres::getFenetreGeo() const {
    return m_set->value("Fenetre/Geo").toByteArray();
}


/*! \brief Définit la géométrie de la fenêtre principale.

  \param pGeo Géométrie de la fenêtre principale
*/
void GestionnaireParametres::setFenetreGeo(const QByteArray& pGeo) {
    m_set->beginGroup("Fenetre");
    m_set->setValue("Geo", pGeo);
    m_set->endGroup();
}


/*! \brief Retourne la liste des fichiers récemment ouverts.

  \return Liste des fichiers récemment ouverts
*/
QStringList GestionnaireParametres::getListeFichiersRecents() const {
    return m_set->value("Fichiers/FichiersRecents").toStringList();
}

/*! \brief Définit la liste des fichiers récemment ouverts.

  \param pListe Liste des fichiers
*/
void GestionnaireParametres::setListeFichiersRecents(const QStringList& pListe) {
    m_set->beginGroup("Fichiers");
    m_set->setValue("FichiersRecents", pListe);
    m_set->endGroup();
}
