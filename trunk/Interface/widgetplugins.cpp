#include "widgetplugins.h"

WidgetPlugins::WidgetPlugins()
{
    setWindowTitle("Plugins");

    m_buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);

    m_glossaire = new QCheckBox("Affichage du glossaire", this);
    m_resultat = new QCheckBox("Affichage des resultats", this);

    QVBoxLayout *m_layout = new QVBoxLayout();

    m_layout->addWidget(m_glossaire);
    m_layout->addWidget(m_resultat);
    m_layout->addWidget(m_buttonBox);

    setLayout(m_layout);


    QObject::connect(m_buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    QObject::connect(m_buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
}

void WidgetPlugins::saveSettings() {
    QSettings settings;

    settings.setValue(m_glossaire->text(), m_glossaire->isChecked());
    settings.setValue(m_resultat->text(), m_resultat->isChecked());
}

void WidgetPlugins::accept() {
    saveSettings();
    emit settingsChanged();
    QDialog::accept();
}