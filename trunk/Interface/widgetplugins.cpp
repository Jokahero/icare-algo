#include "widgetplugins.h"

#include "gestionnaireparametres.h"
#include "gestionnaireplugins.h"

#include <QtCore/QList>
#include <QtGui/QCheckBox>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QScrollArea>
#include <QtGui/QVBoxLayout>

WidgetPlugins::WidgetPlugins() {
    setWindowTitle("Plugins");

    m_buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    m_gestionnairePlugins = new GestionnairePlugins();
    m_listeCheck = new QList<QCheckBox*>;

    QVBoxLayout *layout = new QVBoxLayout;
    QWidget *tmp = new QWidget(this);
    tmp->setLayout(layout);

    QList<PluginInterface*> pluginsDispo = m_gestionnairePlugins->getListePluginsDispo();
    for (int i = 0; i < pluginsDispo.length(); i++) {
        QCheckBox *cb = new QCheckBox(pluginsDispo.at(i)->getNom());
        layout->addWidget(cb);
        m_listeCheck->append(cb);
    }

    QVBoxLayout *layoutFinal = new QVBoxLayout;
    QScrollArea *sa = new QScrollArea;
    sa->setWidget(tmp);
    sa->setAlignment(Qt::AlignLeft);
    layoutFinal->addWidget(sa);
    layoutFinal->addWidget(m_buttonBox);
    setLayout(layoutFinal);

    loadSettings();

    QObject::connect(m_buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    QObject::connect(m_buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
}

void WidgetPlugins::saveSettings() {
    for (int i = 0; i < m_listeCheck->length(); i++)
        GestionnaireParametres::getInstance()->setPluginActif(m_listeCheck->at(i)->text(), m_listeCheck->at(i)->isChecked());
}

void WidgetPlugins::accept() {
    saveSettings();
    emit settingsChanged();
    QDialog::accept();
}

void WidgetPlugins::loadSettings() {
    for (int i = 0; i < m_listeCheck->length(); i++)
        m_listeCheck->at(i)->setChecked(GestionnaireParametres::getInstance()->getPluginActif(m_listeCheck->at(i)->text()));
}

GestionnairePlugins* WidgetPlugins::getGestionnairePlugins() {
    return m_gestionnairePlugins;
}
