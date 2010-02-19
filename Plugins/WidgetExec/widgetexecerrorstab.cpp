#include "widgetexecerrorstab.h"

#include <QtCore/QList>
#include <QtGui/QListWidget>

WidgetExecErrorsTab::WidgetExecErrorsTab(WidgetExec::onglet pType, QWidget *pParent) : WidgetExecTab(pType, pParent) {
    m_liste = new QListWidget(this);
    m_listeNumLignes = new QList<int>;
    connect(m_liste, SIGNAL(currentRowChanged(int)), this, SLOT(ligneChangee(int)));
}

void WidgetExecErrorsTab::erreurLogique(ExpressionLogique::erreur pErreur, int pNumLigne) {
    switch (pErreur) {
    case ExpressionLogique::PositionOperateurs:
        m_liste->addItem(tr("Ligne %1 : Expression logique malformée").arg(QString::number(pNumLigne)));
        break;
    case ExpressionLogique::Parentheses:
        m_liste->addItem(tr("Ligne %1 : Nombre de parenthèses incorrect").arg(QString::number(pNumLigne)));
        break;
    default:
        m_liste->addItem(tr("Ligne %1 : Erreur inconnue").arg(QString::number(pNumLigne)));
        break;
    }
    m_listeNumLignes->append(pNumLigne);
}

void WidgetExecErrorsTab::erreurMathematique(MathExp::erreur pErreur, int pNumLigne) {
    switch (pErreur) {
    case MathExp::DivisionParZero:
        m_liste->addItem(tr("Ligne %1 : Division par zéro").arg(QString::number(pNumLigne)));
        break;
    case MathExp::PositionOperateurs:
        m_liste->addItem(tr("Ligne %1 : Expression mathématique malformée").arg(QString::number(pNumLigne)));
        break;
    case MathExp::Parentheses:
        m_liste->addItem(tr("Ligne %1 : Nombre de parenthèses incorrect").arg(QString::number(pNumLigne)));
        break;
    default:
        m_liste->addItem(tr("Ligne %1 : Erreur inconnue").arg(QString::number(pNumLigne)));
        break;
    }
    m_listeNumLignes->append(pNumLigne);
}

void WidgetExecErrorsTab::erreurAnalyse(Analyse::erreur pErreur, int pNumLigne) {
    switch (pErreur) {
    case Analyse::VariableNonDeclaree:
        m_liste->addItem(tr("Ligne %1 : Variable non déclarée").arg(QString::number(pNumLigne)));
        break;
    case Analyse::VariableDejaDeclaree:
        m_liste->addItem(tr("Ligne %1 : Redéfinition de variable").arg(QString::number(pNumLigne)));
        break;
    case Analyse::VariableNonInitialisee:
        m_liste->addItem(tr("Ligne %1 : Variable non initialisée").arg(QString::number(pNumLigne)));
        break;
    case Analyse::TypeIncorrect:
        m_liste->addItem(tr("Ligne %1 : Type de la variable incorrect").arg(QString::number(pNumLigne)));
        break;
    case Analyse::Syntaxe:
        m_liste->addItem(tr("Ligne %1 : Erreur de syntaxe").arg(QString::number(pNumLigne)));
        break;
    case Analyse::Struct:
        m_liste->addItem(tr("Ligne %1 : Structures de contrôles mal imbriquées/non fermées").arg(QString::number(pNumLigne)));
        break;
    default:
        m_liste->addItem(tr("Ligne %1 : Erreur inconnue").arg(QString::number(pNumLigne)));
        break;
    }
    m_listeNumLignes->append(pNumLigne);
}

void WidgetExecErrorsTab::clear() {
    m_liste->clear();
    m_listeNumLignes->clear();
}

void WidgetExecErrorsTab::resizeEvent(QResizeEvent *pE) {
    QWidget::resizeEvent(pE);
    m_liste->resize(size());
}

void WidgetExecErrorsTab::ligneChangee(int pLigne) {
    emit changementLigne(m_listeNumLignes->at(pLigne));
}
