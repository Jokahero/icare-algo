#include "preferences.h"

Preferences::Preferences() : QDialog()
{
    setWindowTitle("Préférences");
    setModal(true);

    QFormLayout *test = new QFormLayout(this);
    m_onglets = new QTabWidget(this);
    test->addWidget(m_onglets);

    QFormLayout *m_layout = new QFormLayout();

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

    m_layout->addRow(m_commentairesLabel, m_commentairesBouton);
    m_layout->addRow(m_bornesLabel, m_bornesBouton);
    m_layout->addRow(m_structuresLabel, m_structuresBouton);
    m_layout->addRow(m_numeriqueLabel, m_numeriqueBouton);
    m_layout->addRow(m_typeLabel, m_typeBouton);

    m_color = new QWidget(this);
    m_color->setLayout(m_layout);

    m_onglets->addTab(m_color, tr("Coloration syntaxique"));

    setLayout(test);

    QObject::connect(m_commentairesBouton, SIGNAL(clicked()), this, SLOT(modifierCouleur()));
    QObject::connect(m_bornesBouton, SIGNAL(clicked()), this, SLOT(modifierCouleur()));
    QObject::connect(m_structuresBouton, SIGNAL(clicked()), this, SLOT(modifierCouleur()));
    QObject::connect(m_numeriqueBouton, SIGNAL(clicked()), this, SLOT(modifierCouleur()));
    QObject::connect(m_typeBouton, SIGNAL(clicked()), this, SLOT(modifierCouleur()));
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
