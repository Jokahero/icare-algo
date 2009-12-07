#include "widgetexec.h"

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

void WidgetExec::erreurAnalyse(Analyse::erreur pErreur) {
    m_tabWidget->setCurrentIndex(WidgetExec::Erreurs);
    switch (pErreur) {
    case Analyse::VariableNonDeclaree:
        ajouterTexte(tr("Variable non déclarée"), WidgetExec::Erreurs);
        break;
    case Analyse::VariableDejaDeclaree:
        ajouterTexte(tr("Redéfinition de variable"), WidgetExec::Erreurs);
        break;
    case Analyse::TypeIncorrect:
        ajouterTexte(tr("Type de la variable incorrect"), WidgetExec::Erreurs);
        break;
    default:
        ajouterTexte(tr("Erreur inconnue"), WidgetExec::Erreurs);
        break;
    }
}

Q_EXPORT_PLUGIN2(widgetexec, WidgetExec);
