#include "preferences.h"

Preferences::Preferences() : QDialog()
{
    setWindowTitle("Préférences");
    setMinimumSize(400,150);
    setModal(true); // La fenêtre de préférences doit être fermée pour que l'on puisse revenir à l'application

    QVBoxLayout *m_layout = new QVBoxLayout(this);
    m_onglets = new QTabWidget();
    m_buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);

    m_layout->addWidget(m_onglets);
    m_layout->addWidget(buttonBox);

    QFormLayout *m_layoutOnglet = new QFormLayout();

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

    m_layoutOnglet->addRow(m_commentairesLabel, m_commentairesBouton);
    m_layoutOnglet->addRow(m_bornesLabel, m_bornesBouton);
    m_layoutOnglet->addRow(m_structuresLabel, m_structuresBouton);
    m_layoutOnglet->addRow(m_numeriqueLabel, m_numeriqueBouton);
    m_layoutOnglet->addRow(m_typeLabel, m_typeBouton);

    m_color = new QWidget(this);
    m_color->setLayout(m_layoutOnglet);

    m_onglets->addTab(m_color, tr("Coloration syntaxique"));

    setLayout(m_layout);

    QObject::connect(m_commentairesBouton, SIGNAL(clicked()), this, SLOT(modifierCouleur()));
    QObject::connect(m_bornesBouton, SIGNAL(clicked()), this, SLOT(modifierCouleur()));
    QObject::connect(m_structuresBouton, SIGNAL(clicked()), this, SLOT(modifierCouleur()));
    QObject::connect(m_numeriqueBouton, SIGNAL(clicked()), this, SLOT(modifierCouleur()));
    QObject::connect(m_typeBouton, SIGNAL(clicked()), this, SLOT(modifierCouleur()));
    QObject::connect(m_buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    QObject::connect(m_buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
}

void Preferences::modifierCouleur()
{
    QPushButton* tmp = (QPushButton*)sender();
    QColorDialog *choix = new QColorDialog(tmp->palette().color(QPalette::Button), this);
    if (choix->exec() == QDialog::Accepted) {
        QPalette pal = tmp->palette();
        pal.setColor(QPalette::Button, choix->selectedColor());
        tmp->setPalette(pal);
        tmp->repaint();
    }
}
