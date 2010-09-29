#include "widgetglossaire.h"

#include <QtCore/QModelIndex>
#include <QtCore/QSettings>
#include <QtCore/QString>
#include <QtGui/QHBoxLayout>
#include <QtGui/QMenu>
#include <QtGui/QPushButton>
#include <QtGui/QStandardItemModel>
#include <QtGui/QTableView>
#include <QtGui/QTableWidget>
#include <QtGui/QVBoxLayout>

#include <QtCore/QDebug>

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
    m_vueGlossaire->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_vueGlossaire->setSelectionMode(QAbstractItemView::SingleSelection);

    m_addVariable = new QPushButton(tmp);
    m_addVariable->setIcon(QIcon(":/images/list-add.png"));
    m_delVariable = new QPushButton(tmp);
    m_delVariable->setIcon(QIcon(":/images/list-remove.png"));

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(m_addVariable);
    buttonLayout->addWidget(m_delVariable);

    QVBoxLayout *layout = new QVBoxLayout(tmp);
    layout->addLayout(buttonLayout);
    layout->addWidget(m_vueGlossaire);

    tmp->setLayout(layout);
    m_dockWidget->setWidget(tmp);
    m_dockWidget->setWindowTitle(getNom());

    connect(m_addVariable, SIGNAL(clicked()), this, SLOT(ajouterVariable()));
    connect(m_delVariable, SIGNAL(clicked()), this, SLOT(supprimerVariable()));
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
    QMenu menu(m_dockWidget);
    QAction *ajouter = new QAction("Ajouter", m_dockWidget);
    // On vérifier si le curseur est sur un objet ou non
    QModelIndex clickedItemIndex = m_vueGlossaire->indexAt(pos);
    if (clickedItemIndex.row() != -1) {
        // Création de actions et ajout dans le menu
        QAction *supprimer = new QAction("Supprimer", m_dockWidget);
        QAction *modifier = new QAction("Modifier", m_dockWidget);
        menu.addAction(supprimer);
        menu.addAction(modifier);
        // Connection des actions au slots correspondants
        connect(supprimer, SIGNAL(triggered()), this, SLOT(supprimerVariable()));
        connect(modifier, SIGNAL(triggered()), this, SLOT(modifierVariable()));
    }
    menu.addAction(ajouter);
    connect(ajouter, SIGNAL(triggered()), this, SLOT(ajouterVariable()));
    //  Affichage du menu sous le curseur
    menu.exec(QCursor::pos());
}

void WidgetGlossaire::ajouterVariable() {

}

void WidgetGlossaire::supprimerVariable() {
    if (m_vueGlossaire->selectionModel()->hasSelection()) {
        QModelIndex index = m_vueGlossaire->selectionModel()->selectedIndexes().at(0);
        emit enleverVariable(m_modeleGlossaire->index(index.row(), 0).data().toString());
        m_modeleGlossaire->removeRow(index.row());
    }
}

void WidgetGlossaire::modifierVariable() {

}

Q_EXPORT_PLUGIN2(widgetglossaire, WidgetGlossaire);
