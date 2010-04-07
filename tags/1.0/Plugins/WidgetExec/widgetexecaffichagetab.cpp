#include "widgetexecaffichagetab.h"

#include <QtGui/QTextEdit>
#include <QtGui/QWidget>

WidgetExecAffichageTab::WidgetExecAffichageTab(WidgetExec::onglet pType, QWidget *parent) : WidgetExecTab(pType, parent) {
    m_textEdit = new QTextEdit(this);
    m_textEdit->setReadOnly(true);
}

void WidgetExecAffichageTab::resizeEvent(QResizeEvent *pE) {
    QWidget::resizeEvent(pE);
    m_textEdit->resize(size());
}

void WidgetExecAffichageTab::clear() {
    m_textEdit->clear();
}

void WidgetExecAffichageTab::afficher(QString pChaine) {
    m_textEdit->append(pChaine);
}
