#include "widgetglossaire.h"

#include <QtCore/QSettings>
#include <QtCore/QString>
#include <QtGui/QHBoxLayout>
#include <QtGui/QTableWidget>

/*! \brief Constructeur. Initialise le widget avec un QTextEdit.
*/
WidgetGlossaire::WidgetGlossaire() {
    m_dockWidget = new QDockWidget;
    QWidget* tmp = new QWidget();

    QHBoxLayout *layout = new QHBoxLayout(tmp);
    m_tableau = new QTableWidget(0, 4, tmp);
    QStringList headers;
    headers << tr("Nom") << tr("Type") << tr("Valeur") << tr("Description");
    m_tableau->setHorizontalHeaderLabels(headers);
    layout->addWidget(m_tableau);

    tmp->setLayout(layout);
    m_dockWidget->setWidget(tmp);
    m_dockWidget->setWindowTitle(getNom());

    connect(m_dockWidget, SIGNAL(dockLocationChanged(Qt::DockWidgetArea)), this, SLOT(sauvegarderPosition(Qt::DockWidgetArea)));
    connect(m_dockWidget, SIGNAL(topLevelChanged(bool)), this, SLOT(sauvegarderEtat(bool)));
}

QString WidgetGlossaire::getNom() {
    return QString(tr("WidgetGlossaire"));
}

QDockWidget* WidgetGlossaire::getDockWidget() {
    return m_dockWidget;
}

void WidgetGlossaire::variableAjoutee(QString pNomVar, QString pType, QString pDescription) {
    QTableWidgetItem *nom = new QTableWidgetItem(pNomVar);
    QTableWidgetItem *type = new QTableWidgetItem(pType);
    QTableWidgetItem *val = new QTableWidgetItem(QChar(0x2205));        // QChar(0x2205) : Symbole de l'ensemble vide (∅)
    QTableWidgetItem *desc = new QTableWidgetItem(pDescription);
    int nbLignes = m_tableau->rowCount();
    m_tableau->insertRow(nbLignes);
    m_tableau->setItem(nbLignes, 0, nom);
    m_tableau->setItem(nbLignes, 1, type);
    m_tableau->setItem(nbLignes, 2, val);
    m_tableau->setItem(nbLignes, 3, desc);
}

void WidgetGlossaire::variableModifiee(QString pNomVar, QString pValeur) {
    bool modifie = false;
    for (int i = 0; i < m_tableau->rowCount() && !modifie; i++) {
        if (m_tableau->item(i, 0)->text() == pNomVar) {
            m_tableau->item(i, 2)->setText(pValeur);
            modifie = true;
        }
    }
}

void WidgetGlossaire::reinitialisationGlossaire() {
    m_tableau->clearContents();
    m_tableau->setRowCount(0);
}

void WidgetGlossaire::sauvegarderPosition(Qt::DockWidgetArea pPos) {
    QSettings settings;
    settings.setValue(QString(getNom() + "pos"), pPos);
}

void WidgetGlossaire::sauvegarderEtat(bool pEtat) {
    QSettings settings;
    settings.setValue(QString(getNom() + "floating"), pEtat);
}

Q_EXPORT_PLUGIN2(widgetglossaire, WidgetGlossaire);