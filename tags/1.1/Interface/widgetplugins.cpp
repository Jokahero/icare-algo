#include "widgetplugins.h"

#include "gestionnaireparametres.h"
#include "gestionnaireplugins.h"

#include <QtCore/QDebug>
#include <QtCore/QList>
#include <QtGui/QCheckBox>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QLabel>
#include <QtGui/QScrollArea>
#include <QtGui/QVBoxLayout>


/*! \brief Constructeur. La fenêtre est modale.
*/
WidgetPlugins::WidgetPlugins() {
    setWindowTitle(tr("Plugins"));
    setModal(true);

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

    QHBoxLayout *layoutInfos = new QHBoxLayout();
    m_infoLabel = new QLabel(tr("Les changements ne seront effectifs qu'au prochain lancement de l'application."));
    m_imgLabel = new QLabel();
    m_imgLabel->setPixmap(QPixmap(":/Icônes/dialog-warning.png"));
    layoutInfos->addWidget(m_imgLabel);
    layoutInfos->addWidget(m_imgLabel);
    layoutInfos->addWidget(m_infoLabel);


    QVBoxLayout *layoutFinal = new QVBoxLayout;
    QScrollArea *sa = new QScrollArea;
    sa->setWidget(tmp);
    sa->setAlignment(Qt::AlignLeft);
    layoutFinal->addWidget(sa);
    layoutFinal->addLayout(layoutInfos);
    layoutFinal->addWidget(m_buttonBox);
    setLayout(layoutFinal);

    loadSettings();

    QObject::connect(m_buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    QObject::connect(m_buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
}


/*! \brief Destructeur.
*/
WidgetPlugins::~WidgetPlugins() {
    delete m_gestionnairePlugins;
    delete m_buttonBox;
    for (int i = 0; i < m_listeCheck->length(); i++)
        delete m_listeCheck->at(i);
    delete m_listeCheck;
}


/*! \brief Sauvegarde pour chaque plugin si il est actif ou non.
*/
void WidgetPlugins::saveSettings() {
    for (int i = 0; i < m_listeCheck->length(); i++)
        GestionnaireParametres::getInstance()->setPluginActif(m_listeCheck->at(i)->text(), m_listeCheck->at(i)->isChecked());
}


/*! \brief Sauvegarde les paramètres, envoie le signal settingsChanged et ferme la fenêtre.
*/
void WidgetPlugins::accept() {
    saveSettings();
    emit settingsChanged();
    QDialog::accept();
}


/*! \brief Charge l'état d'activation de chaque plugin depuis les préférences.
*/
void WidgetPlugins::loadSettings() {
    for (int i = 0; i < m_listeCheck->length(); i++)
        m_listeCheck->at(i)->setChecked(GestionnaireParametres::getInstance()->getPluginActif(m_listeCheck->at(i)->text()));
}


/*! \brief Accesseur du gestionnaire de plugins.

  \return Gestionnaire de plugins
*/
GestionnairePlugins* WidgetPlugins::getGestionnairePlugins() {
    return m_gestionnairePlugins;
}
