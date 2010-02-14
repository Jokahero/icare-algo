#include "preferences.h"

#include "boutoncouleur.h"
#include "gestionnaireparametres.h"

#include <QtGui/QCheckBox>
#include <QtGui/QColorDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QFormLayout>
#include <QtGui/QLabel>
#include <QtGui/QSpinBox>
#include <QtGui/QTabWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

Preferences::Preferences() : QDialog() {
    setWindowTitle("Préférences");
    setMinimumSize(300, 150);
    setModal(true); // La fenêtre de préférences doit être fermée pour que l'on puisse revenir à l'application

    QVBoxLayout *m_layout = new QVBoxLayout(this);
    m_onglets = new QTabWidget();
    m_buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);

    m_layout->addWidget(m_onglets);
    m_layout->addWidget(m_buttonBox);

    QFormLayout *m_layoutOngletColoration = new QFormLayout();

    m_commentairesLabel = new QLabel(tr("Couleur des commentaires et des chaînes:"));
    m_commentairesBouton = new BoutonCouleur(this);

    m_bornesLabel = new QLabel(tr("Couleur des bornes:"));
    m_bornesBouton = new BoutonCouleur(this);

    m_structuresLabel = new QLabel(tr("Couleur des structures de contrôle:"));
    m_structuresBouton = new BoutonCouleur(this);

    m_numeriqueLabel = new QLabel(tr("Couleur des nombres:"));
    m_numeriqueBouton = new BoutonCouleur(this);

    m_typeLabel = new QLabel(tr("Couleur des types:"));
    m_typeBouton = new BoutonCouleur(this);

    m_layoutOngletColoration->addRow(m_commentairesLabel, m_commentairesBouton);
    m_layoutOngletColoration->addRow(m_bornesLabel, m_bornesBouton);
    m_layoutOngletColoration->addRow(m_structuresLabel, m_structuresBouton);
    m_layoutOngletColoration->addRow(m_numeriqueLabel, m_numeriqueBouton);
    m_layoutOngletColoration->addRow(m_typeLabel, m_typeBouton);

    m_color = new QWidget(this);
    m_color->setLayout(m_layoutOngletColoration);

    m_edit = new QWidget(this);
    QFormLayout *m_layoutOngletZoneEdition = new QFormLayout();

    m_numerotation = new QCheckBox(tr("Numérotation des lignes"), this);
    m_retourLigne = new QCheckBox(tr("Retour à la ligne automatique"), this);
    m_tailleTab = new QSpinBox(this);
    m_surligneBouton = new BoutonCouleur(this);

    m_layoutOngletZoneEdition->addRow(m_numerotation);
    m_layoutOngletZoneEdition->addRow(m_retourLigne);
    m_layoutOngletZoneEdition->addRow(tr("Taille des tabulations (en espaces)"), m_tailleTab);
    m_layoutOngletZoneEdition->addRow(tr("Coloration de la ligne actuelle:"), m_surligneBouton);
    m_edit->setLayout(m_layoutOngletZoneEdition);

    m_onglets->addTab(m_color, tr("Coloration syntaxique"));
    m_onglets->addTab(m_edit, tr("Zone d'édition"));

    setLayout(m_layout);

    loadSettings();

    QObject::connect(m_commentairesBouton, SIGNAL(clicked()), this, SLOT(modifierCouleur()));
    QObject::connect(m_bornesBouton, SIGNAL(clicked()), this, SLOT(modifierCouleur()));
    QObject::connect(m_structuresBouton, SIGNAL(clicked()), this, SLOT(modifierCouleur()));
    QObject::connect(m_numeriqueBouton, SIGNAL(clicked()), this, SLOT(modifierCouleur()));
    QObject::connect(m_typeBouton, SIGNAL(clicked()), this, SLOT(modifierCouleur()));
    QObject::connect(m_surligneBouton, SIGNAL(clicked()), this, SLOT(modifierCouleur()));
    QObject::connect(m_buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    QObject::connect(m_buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
    // connect avec le slot load settings de la coloration
}

/*! \brief Modifie la couleur du bouton modifié.
*/
void Preferences::modifierCouleur()
{
    BoutonCouleur* tmp = (BoutonCouleur*)sender();
    QColorDialog *choix = new QColorDialog(tmp->getCouleur(), this);
    if (choix->exec() == QDialog::Accepted) {
        tmp->setCouleur(choix->selectedColor());
//        changeSettings(/*"Coloration"*/);
    }
}

/*! \brief Sauvegarde les changements de paramètres dans le fichier de configuration.
*/
void Preferences::changeSettings() {
    GestionnaireParametres::getInstance()->setCouleurCommentaires(m_commentairesBouton->getCouleur());
    GestionnaireParametres::getInstance()->setCouleurBornes(m_bornesBouton->getCouleur());
    GestionnaireParametres::getInstance()->setCouleurStructures(m_structuresBouton->getCouleur());
    GestionnaireParametres::getInstance()->setCouleurNombres(m_numeriqueBouton->getCouleur());
    GestionnaireParametres::getInstance()->setCouleurTypes(m_typeBouton->getCouleur());
    GestionnaireParametres::getInstance()->setNumerotationLignes(m_numerotation->isChecked());
    GestionnaireParametres::getInstance()->setRetourLigne(m_retourLigne->isChecked());
    GestionnaireParametres::getInstance()->setTailleTab(m_tailleTab->value());
    GestionnaireParametres::getInstance()->setCouleurLigneActuelle(m_surligneBouton->getCouleur());
}

/*! \brief Charge les paramètres sauvegardés dans le fichier de configuration.
*/
void Preferences::loadSettings() {
    m_commentairesBouton->setCouleur(GestionnaireParametres::getInstance()->getCouleurCommentaires());
    m_bornesBouton->setCouleur(GestionnaireParametres::getInstance()->getCouleurBornes());
    m_structuresBouton->setCouleur(GestionnaireParametres::getInstance()->getCouleurStructures());
    m_numeriqueBouton->setCouleur(GestionnaireParametres::getInstance()->getCouleurNombres());
    m_typeBouton->setCouleur(GestionnaireParametres::getInstance()->getCouleurTypes());

    m_numerotation->setChecked(GestionnaireParametres::getInstance()->getNumerotationLignes());
    m_retourLigne->setChecked(GestionnaireParametres::getInstance()->getRetourLigne());
    m_tailleTab->setValue(GestionnaireParametres::getInstance()->getTailleTab());

    m_surligneBouton->setCouleur(GestionnaireParametres::getInstance()->getCouleurLigneActuelle());
}

void Preferences::accept() {
    changeSettings();
    emit settingsChanged();
    QDialog::accept();
}