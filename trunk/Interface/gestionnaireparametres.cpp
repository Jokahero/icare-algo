#include "gestionnaireparametres.h"

#include <QtCore/QByteArray>
#include <QtCore/QSettings>
#include <QtGui/QColor>

GestionnaireParametres *GestionnaireParametres::_instance = 0;

GestionnaireParametres::GestionnaireParametres() {
    m_set = new QSettings;
}

GestionnaireParametres::~GestionnaireParametres() {
    m_set->sync();
    delete m_set;
}

GestionnaireParametres *GestionnaireParametres::getInstance() {
    if (_instance == 0)
        _instance = new GestionnaireParametres;
    return _instance;
}

void GestionnaireParametres::destroy() {
    delete _instance;
    _instance = 0;
}

bool GestionnaireParametres::getNumerotationLignes() {
    return m_set->value("Editeur/NumerotationLignes", true).toBool();
}

void GestionnaireParametres::setNumerotationLignes(bool pNum) {
    m_set->beginGroup("Editeur");
    m_set->setValue("NumerotationLignes", pNum);
    m_set->endGroup();
}

bool GestionnaireParametres::getRetourLigne() {
    return m_set->value("Editeur/RetourLigne", false).toBool();
}

void GestionnaireParametres::setRetourLigne(bool pRet) {
    m_set->beginGroup("Editeur");
    m_set->setValue("RetourLigne", pRet);
    m_set->endGroup();
}

int GestionnaireParametres::getTailleTab() {
    return m_set->value("Editeur/TailleTab", 8).toInt();
}

void GestionnaireParametres::setTailleTab(int pTaille) {
    m_set->beginGroup("Editeur");
    m_set->setValue("TailleTab", pTaille);
    m_set->endGroup();
}

QColor GestionnaireParametres::getCouleurLigneActuelle() {
    return QColor(m_set->value("Couleurs/LigneActuelle", "#f0f0f0").toString());
}

void GestionnaireParametres::setCouleurLigneActuelle(QColor pCol) {
    m_set->beginGroup("Couleurs");
    m_set->setValue("LigneActuelle", pCol.name());
    m_set->endGroup();
}

QColor GestionnaireParametres::getCouleurCommentaires() {
    return QColor(m_set->value("Couleurs/Commentaires", "#d00000").toString());
}

void GestionnaireParametres::setCouleurCommentaires(QColor pCol) {
    m_set->beginGroup("Couleurs");
    m_set->setValue("Commentaires", pCol.name());
    m_set->endGroup();
}

QColor GestionnaireParametres::getCouleurTypes() {
    return QColor(m_set->value("Couleurs/Types", "#00007f").toString());
}

void GestionnaireParametres::setCouleurTypes(QColor pCol) {
    m_set->beginGroup("Couleurs");
    m_set->setValue("Types", pCol.name());
    m_set->endGroup();
}

QColor GestionnaireParametres::getCouleurNombres() {
    return QColor(m_set->value("Couleurs/Nombres", "#007f00").toString());
}

void GestionnaireParametres::setCouleurNombres(QColor pCol) {
    m_set->beginGroup("Couleurs");
    m_set->setValue("Nombres", pCol.name());
    m_set->endGroup();
}

QColor GestionnaireParametres::getCouleurStructures() {
    return QColor(m_set->value("Couleurs/Structures", "#00007f").toString());
}

void GestionnaireParametres::setCouleurStructures(QColor pCol) {
    m_set->beginGroup("Couleurs");
    m_set->setValue("Structures", pCol.name());
    m_set->endGroup();
}

QColor GestionnaireParametres::getCouleurBornes() {
    return QColor(m_set->value("Couleurs/Bornes", "#7f0000").toString());
}

void GestionnaireParametres::setCouleurBornes(QColor pCol) {
    m_set->beginGroup("Couleurs");
    m_set->setValue("Bornes", pCol.name());
    m_set->endGroup();
}

bool GestionnaireParametres::getPluginActif(QString pNom) {
    return m_set->value("Plugins/" + pNom + "/Actif", true).toBool();
}

void GestionnaireParametres::setPluginActif(QString pNom, bool pActif) {
    m_set->beginGroup("Plugins");
    m_set->beginGroup(pNom);
    m_set->setValue("Actif", pActif);
    m_set->endGroup();
    m_set->endGroup();
}

bool GestionnaireParametres::getFenetreMax() {
    return m_set->value("Fenetre/Max", true).toBool();
}

void GestionnaireParametres::setFenetreMax(bool pMax) {
    m_set->beginGroup("Fenetre");
    m_set->setValue("Max", pMax);
    m_set->endGroup();
}

QByteArray GestionnaireParametres::getFenetreGeo() {
    return m_set->value("Fenetre/Geo").toByteArray();
}

void GestionnaireParametres::setFenetreGeo(QByteArray pGeo) {
    m_set->beginGroup("Fenetre");
    m_set->setValue("Geo", pGeo);
    m_set->endGroup();
}
