#include "widgetexec.h"
#include "widgetexecaffichagetab.h"
#include "widgetexecerrorstab.h"

#include <QtCore/QDebug>
#include <QtCore/QSettings>
#include <QtCore/QString>
#include <QtGui/QDockWidget>
#include <QtGui/QHBoxLayout>
#include <QtGui/QTabBar>
#include <QtGui/QTabWidget>

/*! \brief Constructeur. Initialise le widget avec un QTextEdit.

  \todo Utiliser un QSettings pour la position des onglets.
*/
WidgetExec::WidgetExec() {
    m_dockWidget = new QDockWidget;
    QWidget* tmp = new QWidget();
    QHBoxLayout *layout = new QHBoxLayout(tmp);
    m_tabWidget = new QTabWidget;
    m_tabWidget->setTabPosition(QTabWidget::West);
    WidgetExecErrorsTab* errTab = new WidgetExecErrorsTab(WidgetExec::Erreurs, m_tabWidget);
    m_tabWidget->addTab(errTab, "Erreurs");
    m_tabWidget->addTab(new WidgetExecAffichageTab(WidgetExec::Sorties, m_tabWidget), "Sorties");

    layout->addWidget(m_tabWidget);
    tmp->setLayout(layout);
    m_dockWidget->setWidget(tmp);
    m_dockWidget->setWindowTitle(getNom());

    connect(m_dockWidget, SIGNAL(dockLocationChanged(Qt::DockWidgetArea)), this, SLOT(sauvegarderPosition(Qt::DockWidgetArea)));
    connect(m_dockWidget, SIGNAL(topLevelChanged(bool)), this, SLOT(sauvegarderEtat(bool)));
    connect(errTab, SIGNAL(changementLigne(int)), this, SIGNAL(changementLigne(int)));
}

QString WidgetExec::getNom() {
    return QString(tr("Sortie de compilation/exécution"));
}

QDockWidget* WidgetExec::getDockWidget() {
    return m_dockWidget;
}

void WidgetExec::erreurLogique(ExpressionLogique::erreur pErreur, int pNumLigne) {
    m_tabWidget->setCurrentIndex(WidgetExec::Erreurs);
    qobject_cast<WidgetExecErrorsTab*>(m_tabWidget->widget(WidgetExec::Erreurs))->erreurLogique(pErreur, pNumLigne);
}

void WidgetExec::erreurMathematique(MathExp::erreur pErreur, int pNumLigne) {
    m_tabWidget->setCurrentIndex(WidgetExec::Erreurs);
    qobject_cast<WidgetExecErrorsTab*>(m_tabWidget->widget(WidgetExec::Erreurs))->erreurMathematique(pErreur, pNumLigne);
}

void WidgetExec::erreurAnalyse(Analyse::erreur pErreur, int pNumLigne) {
    m_tabWidget->setCurrentIndex(WidgetExec::Erreurs);
    qobject_cast<WidgetExecErrorsTab*>(m_tabWidget->widget(WidgetExec::Erreurs))->erreurAnalyse(pErreur, pNumLigne);
}

void WidgetExec::lancerExecution() {
    qDebug() << "WidgetExec::lancerExecution";
    for (int i = 0; i < m_tabWidget->count(); i++) {
        qobject_cast<WidgetExecTab*>(m_tabWidget->widget(i))->clear();
    }
}

void WidgetExec::lancerAnalyse(QFile* /*pFichier*/) {
    for (int i = 0; i < m_tabWidget->count(); i++) {
        qobject_cast<WidgetExecTab*>(m_tabWidget->widget(i))->clear();
    }
}

void WidgetExec::sauvegarderPosition(Qt::DockWidgetArea pPos) {
    QSettings settings;
    settings.setValue(QString(getNom() + "pos"), pPos);
}

void WidgetExec::sauvegarderEtat(bool pEtat) {
    QSettings settings;
    settings.setValue(QString(getNom() + "floating"), pEtat);
}

void WidgetExec::afficher(QString pChaine) {
    m_tabWidget->setCurrentIndex(WidgetExec::Sorties);
    qobject_cast<WidgetExecAffichageTab*>(m_tabWidget->widget(WidgetExec::Sorties))->afficher(pChaine);
}

void WidgetExec::analyseSyntaxiqueTerminee(bool pOk) {
    if (pOk) {
        qobject_cast<WidgetExecTab*>(m_tabWidget->widget(WidgetExec::Sorties))->clear();
        afficher(tr("Analyse syntaxique terminée avec succès."));
    }
}

void WidgetExec::analyseSemantiqueTerminee(bool pOk) {
    if (pOk) {
        qobject_cast<WidgetExecTab*>(m_tabWidget->widget(WidgetExec::Sorties))->clear();
        afficher(tr("Analyse semantique terminée avec succès."));
    }
}

Q_EXPORT_PLUGIN2(widgetexec, WidgetExec);
