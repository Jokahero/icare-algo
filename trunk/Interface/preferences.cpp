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


/*! \brief Constructeur. L'objet est détruit immédiatement à sa fermeture.
*/
Preferences::Preferences() : QDialog() {
    setWindowTitle("Préférences");
    setMinimumSize(300, 150);
    setModal(true); // La fenêtre de préférences doit être fermée pour que l'on puisse revenir à l'application
    setAttribute(Qt::WA_DeleteOnClose);

    QVBoxLayout *layout = new QVBoxLayout(this);
    m_onglets = new QTabWidget();
    m_buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);

    layout->addWidget(m_onglets);
    layout->addWidget(m_buttonBox);

    QFormLayout *layoutOngletColoration = new QFormLayout();

    m_commentairesLabel = new QLabel(tr("Couleur des commentaires:"));
    m_commentairesBouton = new BoutonCouleur(this);

    m_chainesLabel = new QLabel(tr("Couleur des chaînes de caractères:"));
    m_chainesBouton = new BoutonCouleur(this);

    m_bornesLabel = new QLabel(tr("Couleur des bornes:"));
    m_bornesBouton = new BoutonCouleur(this);

    m_structuresLabel = new QLabel(tr("Couleur des structures de contrôle:"));
    m_structuresBouton = new BoutonCouleur(this);

    m_numeriqueLabel = new QLabel(tr("Couleur des nombres:"));
    m_numeriqueBouton = new BoutonCouleur(this);

    m_typeLabel = new QLabel(tr("Couleur des types:"));
    m_typeBouton = new BoutonCouleur(this);

    layoutOngletColoration->addRow(m_commentairesLabel, m_commentairesBouton);
    layoutOngletColoration->addRow(m_chainesLabel, m_chainesBouton);
    layoutOngletColoration->addRow(m_bornesLabel, m_bornesBouton);
    layoutOngletColoration->addRow(m_structuresLabel, m_structuresBouton);
    layoutOngletColoration->addRow(m_numeriqueLabel, m_numeriqueBouton);
    layoutOngletColoration->addRow(m_typeLabel, m_typeBouton);

    m_color = new QWidget(this);
    m_color->setLayout(layoutOngletColoration);

    m_edit = new QWidget(this);
    QFormLayout *layoutOngletZoneEdition = new QFormLayout();

    m_numerotation = new QCheckBox(tr("Numérotation des lignes"), this);
    m_retourLigne = new QCheckBox(tr("Retour à la ligne automatique"), this);
    m_tailleTab = new QSpinBox(this);
    m_surligneBouton = new BoutonCouleur(this);

    layoutOngletZoneEdition->addRow(m_numerotation);
    layoutOngletZoneEdition->addRow(m_retourLigne);
    layoutOngletZoneEdition->addRow(tr("Taille des tabulations (en espaces)"), m_tailleTab);
    layoutOngletZoneEdition->addRow(tr("Coloration de la ligne actuelle:"), m_surligneBouton);
    m_edit->setLayout(layoutOngletZoneEdition);

    m_onglets->addTab(m_color, tr("Coloration syntaxique"));
    m_onglets->addTab(m_edit, tr("Zone d'édition"));

    setLayout(layout);

    loadSettings();

    connect(m_commentairesBouton, SIGNAL(clicked()), this, SLOT(modifierCouleur()));
    connect(m_chainesBouton, SIGNAL(clicked()), this, SLOT(modifierCouleur()));
    connect(m_bornesBouton, SIGNAL(clicked()), this, SLOT(modifierCouleur()));
    connect(m_structuresBouton, SIGNAL(clicked()), this, SLOT(modifierCouleur()));
    connect(m_numeriqueBouton, SIGNAL(clicked()), this, SLOT(modifierCouleur()));
    connect(m_typeBouton, SIGNAL(clicked()), this, SLOT(modifierCouleur()));
    connect(m_surligneBouton, SIGNAL(clicked()), this, SLOT(modifierCouleur()));
    connect(m_buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(m_buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
}

/*! \brief Destructeur.
*/
Preferences::~Preferences() {
    delete m_onglets;
    delete m_color;
    delete m_commentairesLabel;
    delete m_commentairesBouton;
    delete m_chainesLabel;
    delete m_chainesBouton;
    delete m_bornesLabel;
    delete m_bornesBouton;
    delete m_structuresLabel;
    delete m_structuresBouton;
    delete m_numeriqueLabel;
    delete m_numeriqueBouton;
    delete m_typeLabel;
    delete m_typeBouton;
    delete m_edit;
    delete m_numerotation;
    delete m_retourLigne;
    delete m_tailleTab;
    delete m_surligneBouton;
    delete m_buttonBox;
}

/*! \brief Modifie la couleur du bouton modifié.
*/
void Preferences::modifierCouleur() {
    BoutonCouleur* tmp = (BoutonCouleur*)sender();
    QColorDialog *choix = new QColorDialog(tmp->getCouleur(), this);
    if (choix->exec() == QDialog::Accepted) {
        tmp->setCouleur(choix->selectedColor());
    }
}


/*! \brief Sauvegarde les changements de paramètres dans le fichier de configuration.
*/
void Preferences::changeSettings() {
    GestionnaireParametres::getInstance()->setCouleurCommentaires(m_commentairesBouton->getCouleur());
    GestionnaireParametres::getInstance()->setCouleurChaines(m_chainesBouton->getCouleur());
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
    m_chainesBouton->setCouleur(GestionnaireParametres::getInstance()->getCouleurChaines());
    m_bornesBouton->setCouleur(GestionnaireParametres::getInstance()->getCouleurBornes());
    m_structuresBouton->setCouleur(GestionnaireParametres::getInstance()->getCouleurStructures());
    m_numeriqueBouton->setCouleur(GestionnaireParametres::getInstance()->getCouleurNombres());
    m_typeBouton->setCouleur(GestionnaireParametres::getInstance()->getCouleurTypes());

    m_numerotation->setChecked(GestionnaireParametres::getInstance()->getNumerotationLignes());
    m_retourLigne->setChecked(GestionnaireParametres::getInstance()->getRetourLigne());
    m_tailleTab->setValue(GestionnaireParametres::getInstance()->getTailleTab());

    m_surligneBouton->setCouleur(GestionnaireParametres::getInstance()->getCouleurLigneActuelle());
}


/*! \brief Sauvegarde les modifications, envoie le signal settingsChanged et ferme la fenêtre.
*/
void Preferences::accept() {
    changeSettings();
    emit settingsChanged();
    QDialog::accept();
}
