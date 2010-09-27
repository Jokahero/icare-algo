#include "widgetglossaire.h"

#include <QtCore/QModelIndex>
#include <QtCore/QSettings>
#include <QtCore/QString>
#include <QtGui/QHBoxLayout>
#include <QtGui/QMenu>
#include <QtGui/QStandardItemModel>
#include <QtGui/QTableView>
#include <QtGui/QTableWidget>

#include <QtCore/QDebug>

/*! \brief Constructeur. Initialise le widget avec un QTextEdit.
*/
WidgetGlossaire::WidgetGlossaire() {
    m_dockWidget = new QDockWidget;
    QWidget* tmp = new QWidget();

    m_modeleGlossaire = new QStandardItemModel(this);
    m_modeleGlossaire->insertColumns(0,4);
    m_modeleGlossaire->setHeaderData(0, Qt::Horizontal, "Nom");
    m_modeleGlossaire->setHeaderData(1, Qt::Horizontal, "Type");
    m_modeleGlossaire->setHeaderData(2, Qt::Horizontal, "Valeur");
    m_modeleGlossaire->setHeaderData(3, Qt::Horizontal, "Description");

    m_vueGlossaire = new QTableView(tmp);
    m_vueGlossaire->setModel(m_modeleGlossaire);
    m_vueGlossaire->setContextMenuPolicy(Qt::CustomContextMenu);

    QHBoxLayout *layout = new QHBoxLayout(tmp);
   /* m_tableau = new QTableWidget(0, 4, tmp);
    QStringList headers;
    headers << tr("Nom") << tr("Type") << tr("Valeur") << tr("Description");
    m_tableau->setHorizontalHeaderLabels(headers);*/
    layout->addWidget(m_vueGlossaire);

    tmp->setLayout(layout);
    m_dockWidget->setWidget(tmp);
    m_dockWidget->setWindowTitle(getNom());

    connect(m_vueGlossaire, SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(afficherMenuContextuel(const QPoint&)));
    connect(m_dockWidget, SIGNAL(dockLocationChanged(Qt::DockWidgetArea)), this, SLOT(sauvegarderPosition(Qt::DockWidgetArea)));
    connect(m_dockWidget, SIGNAL(topLevelChanged(bool)), this, SLOT(sauvegarderEtat(bool)));
}

QString WidgetGlossaire::getNom() {
    return QString(tr("Glossaire"));
}

QDockWidget* WidgetGlossaire::getDockWidget() {
    return m_dockWidget;
}

void WidgetGlossaire::variableAjoutee(QString pNomVar, QString pType, QString pDescription) {
    /*QTableWidgetItem *nom = new QTableWidgetItem(pNomVar);
    QTableWidgetItem *type = new QTableWidgetItem(pType);
    QTableWidgetItem *val = new QTableWidgetItem(QChar(0x2205));        // QChar(0x2205) : Symbole de l'ensemble vide (∅)
    QTableWidgetItem *desc = new QTableWidgetItem(pDescription);
    int nbLignes = m_tableau->rowCount();
    m_tableau->insertRow(nbLignes);
    m_tableau->setItem(nbLignes, 0, nom);
    m_tableau->setItem(nbLignes, 1, type);
    m_tableau->setItem(nbLignes, 2, val);
    m_tableau->setItem(nbLignes, 3, desc);*/
    int rc = m_modeleGlossaire->rowCount();
    m_modeleGlossaire->insertRow(rc);
    QModelIndex index = m_modeleGlossaire->index(rc,0);
    m_modeleGlossaire->setData(index, pNomVar);
    index = m_modeleGlossaire->index(rc, 1);
    m_modeleGlossaire->setData(index, pType);
    index = m_modeleGlossaire->index(rc, 2);
    m_modeleGlossaire->setData(index, QChar(0x2205));
    index = m_modeleGlossaire->index(rc, 3);
    m_modeleGlossaire->setData(index, pDescription);
}

void WidgetGlossaire::variableModifiee(QString pNomVar, QString pValeur) {
    bool modifie = false;
    /*for (int i = 0; i < m_tableau->rowCount() && !modifie; i++) {
        if (m_tableau->item(i, 0)->text() == pNomVar) {
            m_tableau->item(i, 2)->setText(pValeur);
            modifie = true;
        }
    }*/
    for (int i=0; i < m_modeleGlossaire->rowCount() && !modifie; i++) {
        if (m_modeleGlossaire->data((m_modeleGlossaire->index(i, 0))).toString() == pNomVar) {
            QModelIndex index = m_modeleGlossaire->index(i, 2);
            m_modeleGlossaire->setData(index, pValeur);
            modifie = true;
        }
    }
}

void WidgetGlossaire::reinitialisationGlossaire() {
    m_modeleGlossaire->clear();
    m_modeleGlossaire->insertColumns(0,4);
    m_modeleGlossaire->setHeaderData(0, Qt::Horizontal, "Nom");
    m_modeleGlossaire->setHeaderData(1, Qt::Horizontal, "Type");
    m_modeleGlossaire->setHeaderData(2, Qt::Horizontal, "Valeur");
    m_modeleGlossaire->setHeaderData(3, Qt::Horizontal, "Description");
}

void WidgetGlossaire::sauvegarderPosition(Qt::DockWidgetArea pPos) {
    QSettings settings;
    settings.setValue(QString(getNom() + "pos"), pPos);
}

void WidgetGlossaire::sauvegarderEtat(bool pEtat) {
    QSettings settings;
    settings.setValue(QString(getNom() + "floating"), pEtat);
}

void WidgetGlossaire::afficherMenuContextuel(const QPoint &pos) {
    qDebug() << "test";
    QMenu menu(m_dockWidget);
    QAction *ajouter = new QAction("Ajouter", m_dockWidget);
    QModelIndex clickedItemIndex = m_vueGlossaire->indexAt(pos);
    if (clickedItemIndex.row() == -1) {
    }
    menu.addAction(ajouter);
    menu.exec(QCursor::pos());
}

Q_EXPORT_PLUGIN2(widgetglossaire, WidgetGlossaire);
