#include "preferences.h"

#include <QtCore/QSettings>
#include <QtGui/QCheckBox>
#include <QtGui/QColorDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QFormLayout>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QTabWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

Preferences::Preferences() : QDialog()
{
    setWindowTitle("Préférences");
    setMinimumSize(400,150);
    setModal(true); // La fenêtre de préférences doit être fermée pour que l'on puisse revenir à l'application

    QVBoxLayout *m_layout = new QVBoxLayout(this);
    m_onglets = new QTabWidget();
    m_buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);

    m_layout->addWidget(m_onglets);
    m_layout->addWidget(m_buttonBox);

    QFormLayout *m_layoutOngletColoration = new QFormLayout();

    m_commentairesLabel = new QLabel(tr("Couleur des commentaires et des chaînes:"));
    m_commentairesBouton = new QPushButton(tr("Modifier"));

    m_bornesLabel = new QLabel(tr("Couleur des bornes:"));
    m_bornesBouton = new QPushButton(tr("Modifier"));

    m_structuresLabel = new QLabel(tr("Couleur des structures de contrôle:"));
    m_structuresBouton = new QPushButton(tr("Modifier"));

    m_numeriqueLabel = new QLabel(tr("Couleur des nombres:"));
    m_numeriqueBouton = new QPushButton(tr("Modifier"));

    m_typeLabel = new QLabel(tr("Couleur des types:"));
    m_typeBouton = new QPushButton(tr("Modifier"));

    m_layoutOngletColoration->addRow(m_commentairesLabel, m_commentairesBouton);
    m_layoutOngletColoration->addRow(m_bornesLabel, m_bornesBouton);
    m_layoutOngletColoration->addRow(m_structuresLabel, m_structuresBouton);
    m_layoutOngletColoration->addRow(m_numeriqueLabel, m_numeriqueBouton);
    m_layoutOngletColoration->addRow(m_typeLabel, m_typeBouton);

    m_color = new QWidget(this);
    m_color->setLayout(m_layoutOngletColoration);

    m_edit = new QWidget(this);
    QFormLayout *m_layoutOngletZoneEdition = new QFormLayout();

    m_numerotation = new QCheckBox("Numérotation des lignes", this);

    m_layoutOngletZoneEdition->addRow(m_numerotation);
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
    QPushButton* tmp = (QPushButton*)sender();
    QColorDialog *choix = new QColorDialog(tmp->palette().color(QPalette::Button), this);
    if (choix->exec() == QDialog::Accepted) {
        QPalette pal = tmp->palette();
        pal.setColor(QPalette::Button, choix->selectedColor());
        tmp->setPalette(pal);
        tmp->repaint();
//        changeSettings(/*"Coloration"*/);
    }
}

/*! \brief Sauvegarde les changements de paramètres dans le fichier de configuration.
*/
void Preferences::changeSettings(/*QString pCategorie*/) {
    QSettings settings;
    //settings.beginGroup(pCategorie);
    settings.setValue(m_commentairesLabel->text(), m_commentairesBouton->palette().color(QPalette::Button).name());
    settings.setValue(m_bornesLabel->text(), m_bornesBouton->palette().color(QPalette::Button).name());
    settings.setValue(m_structuresLabel->text(), m_structuresBouton->palette().color(QPalette::Button).name());
    settings.setValue(m_numeriqueLabel->text(), m_numeriqueBouton->palette().color(QPalette::Button).name());
    settings.setValue(m_typeLabel->text(), m_typeBouton->palette().color(QPalette::Button).name());
    //settings.endGroup();
    settings.setValue(m_numerotation->text(), m_numerotation->isChecked());
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
    QString str;
    QPalette pal;

    tmp = recupCouleur(settings.value(m_commentairesLabel->text()).toString());
    pal = m_commentairesBouton->palette();
    pal.setColor(QPalette::Button, tmp);
    m_commentairesBouton->setPalette(pal);

    tmp = recupCouleur(settings.value(m_bornesLabel->text()).toString());
    pal = m_bornesBouton->palette();
    pal.setColor(QPalette::Button, tmp);
    m_bornesBouton->setPalette(pal);

    tmp = recupCouleur(settings.value(m_structuresLabel->text()).toString());
    pal = m_structuresBouton->palette();
    pal.setColor(QPalette::Button, tmp);
    m_structuresBouton->setPalette(pal);

    tmp = recupCouleur(settings.value(m_numeriqueLabel->text()).toString());
    pal = m_numeriqueBouton->palette();
    pal.setColor(QPalette::Button, tmp);
    m_numeriqueBouton->setPalette(pal);

    tmp = recupCouleur(settings.value(m_typeLabel->text()).toString());
    pal = m_typeBouton->palette();
    pal.setColor(QPalette::Button, tmp);
    m_typeBouton->setPalette(pal);

    m_numerotation->setChecked(settings.value(m_numerotation->text()).toBool());
}

void Preferences::accept() {
    changeSettings();
    emit settingsChanged();
    QDialog::accept();
}
