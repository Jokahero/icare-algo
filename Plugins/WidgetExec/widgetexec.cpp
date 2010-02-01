#include "widgetexec.h"

#include <QtCore/QDebug>
#include <QtCore/QString>
#include <QtGui/QDockWidget>
#include <QtGui/QHBoxLayout>
#include <QtGui/QTabWidget>
#include <QtGui/QTextEdit>

/*! \brief Constructeur. Initialise le widget avec un QTextEdit.

  \todo Utiliser un QSettings pour la position des onglets.
*/
WidgetExec::WidgetExec() {
    m_dockWidget = new QDockWidget;
    QWidget* tmp = new QWidget();
    QHBoxLayout *layout = new QHBoxLayout(tmp);
    m_tabWidget = new QTabWidget;
    m_tabWidget->setTabPosition(QTabWidget::West);
    m_tabWidget->addTab(new QTextEdit, "Erreurs");
    m_tabWidget->addTab(new QTextEdit, "Sorties");

    layout->addWidget(m_tabWidget);
    tmp->setLayout(layout);
    m_dockWidget->setWidget(tmp);
    m_dockWidget->setWindowTitle(getNom());
}

/*! \brief Ajoute le texte indiqué à la suite du texte présent dans l'onglet spécifié.

  \param pTexte Texte à ajouter.
  \param pOnglet Onglet auquel ajouter le texte.
*/
void WidgetExec::ajouterTexte(QString pTexte, WidgetExec::onglet pOnglet) {
    qobject_cast<QTextEdit*>(m_tabWidget->widget(pOnglet))->append(pTexte);
}

/*! \brief Efface le contenu d'un onglet.

*/
void WidgetExec::effacerTexte(WidgetExec::onglet pOnglet) {
    qobject_cast<QTextEdit*>(m_tabWidget->widget(pOnglet))->clear();
}

/*! \brief Remplace le texte présent d'un onglet.

  Appelle successivement effacerTexte et ajouterTexte avec le texte passé en paramètre.
  \param pTexte Texte à affecter au widget.
  \param pOnglet Onglet auquel affecter le texte.
*/
void WidgetExec::remplacerTexte(QString pTexte, WidgetExec::onglet pOnglet) {
    effacerTexte(pOnglet);
    ajouterTexte(pTexte, pOnglet);
}

QString WidgetExec::getNom() {
    return QString(tr("WidgetExec"));
}

QDockWidget* WidgetExec::getDockWidget() {
    return m_dockWidget;
}

void WidgetExec::erreurMathematique(MathExp::erreur pErreur) {
    m_tabWidget->setCurrentIndex(WidgetExec::Erreurs);
    switch (pErreur) {
    case MathExp::DivisionParZero:
        ajouterTexte(tr("Division par zéro"), WidgetExec::Erreurs);
        break;
    case MathExp::PositionOperateurs:
        ajouterTexte(tr("Expression mathématique malformée"), WidgetExec::Erreurs);
        break;
    case MathExp::Parentheses:
        ajouterTexte(tr("Nombre de parenthèses incorrect"), WidgetExec::Erreurs);
        break;
    default:
        ajouterTexte(tr("Erreur inconnue"), WidgetExec::Erreurs);
        break;
    }
}

void WidgetExec::erreurAnalyse(Analyse::erreur pErreur, int pNumLigne) {
    m_tabWidget->setCurrentIndex(WidgetExec::Erreurs);
    switch (pErreur) {
    case Analyse::VariableNonDeclaree:
        ajouterTexte(tr("Ligne %1 : Variable non déclarée").arg(QString::number(pNumLigne)), WidgetExec::Erreurs);
        break;
    case Analyse::VariableDejaDeclaree:
        ajouterTexte(tr("Ligne %1 : Redéfinition de variable").arg(QString::number(pNumLigne)), WidgetExec::Erreurs);
        break;
    case Analyse::TypeIncorrect:
        ajouterTexte(tr("Ligne %1 : Type de la variable incorrect").arg(QString::number(pNumLigne)), WidgetExec::Erreurs);
        break;
    case Analyse::Syntaxe:
        ajouterTexte(tr("Ligne %1 : Erreur de syntaxe").arg(QString::number(pNumLigne)), WidgetExec::Erreurs);
        break;
    default:
        ajouterTexte(tr("Ligne %1 : Erreur inconnue").arg(QString::number(pNumLigne)), WidgetExec::Erreurs);
        break;
    }
    qDebug() << "WidgetExec::erreurAnalyse";
}

void WidgetExec::lancerAnalyse(QFile* pFichier) {
    effacerTexte(WidgetExec::Erreurs);
    qDebug() << "WidgetExec::lancerAnalyse";
}

Q_EXPORT_PLUGIN2(widgetexec, WidgetExec);
