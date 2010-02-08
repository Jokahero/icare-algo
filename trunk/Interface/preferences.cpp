#include "preferences.h"
#include "boutoncouleur.h"

#include <QtCore/QSettings>
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

    m_layoutOngletZoneEdition->addRow(m_numerotation);
    m_layoutOngletZoneEdition->addRow(m_retourLigne);
    m_layoutOngletZoneEdition->addRow(tr("Taille des tabulations (en espaces)"), m_tailleTab);
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
    QObject::connect(m_buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    QObject::connect(m_buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
    // connect ac le slot load settings de la coloration
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
void Preferences::changeSettings(/*QString pCategorie*/) {
    QSettings settings;
    //settings.beginGroup(pCategorie);
    settings.setValue("CouleurCommentaires", m_commentairesBouton->getCouleur().name());
    settings.setValue("CouleurBornes", m_bornesBouton->getCouleur().name());
    settings.setValue("CouleurStructures", m_structuresBouton->getCouleur().name());
    settings.setValue("CouleurNombres", m_numeriqueBouton->getCouleur().name());
    settings.setValue("CouleurTypes", m_typeBouton->getCouleur().name());
    //settings.endGroup();
    settings.setValue("NumerotationLignes", m_numerotation->isChecked());
    settings.setValue("RetourLigne", m_retourLigne->isChecked());
    settings.setValue("TailleTab", m_tailleTab->value());

    settings.sync();
}

/*! \brief Permet de récupérer une couleur à partir de son nom.
  \param pNomCouleur Nom de la couleur
  \return couleur Couleur souhaitée
*/
QColor Preferences::recupCouleur(QString pNomCouleur) {
    QColor couleur;
    couleur.setNamedColor(pNomCouleur);
    return couleur;
}

/*! \brief Charge les paramètres sauvegardés dans le fichier de configuration.
*/
void Preferences::loadSettings() {
    QSettings settings;
    QColor tmp;

    tmp = recupCouleur(settings.value("CouleurCommentaires").toString());
    m_commentairesBouton->setCouleur(tmp);

    tmp = recupCouleur(settings.value("CouleurBornes").toString());
    m_bornesBouton->setCouleur(tmp);

    tmp = recupCouleur(settings.value("CouleurStructures").toString());
    m_structuresBouton->setCouleur(tmp);

    tmp = recupCouleur(settings.value("CouleurNombres").toString());
    m_numeriqueBouton->setCouleur(tmp);

    tmp = recupCouleur(settings.value("CouleurTypes").toString());
    m_typeBouton->setCouleur(tmp);

    m_numerotation->setChecked(settings.value("NumerotationLignes").toBool());
    m_retourLigne->setChecked(settings.value("RetourLigne").toBool());
    m_tailleTab->setValue(settings.value("TailleTab").toInt());
}

void Preferences::accept() {
    changeSettings();
    emit settingsChanged();
    QDialog::accept();
}
