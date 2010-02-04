#include "widgetexectab.h"

#include <QtCore/QDebug>

WidgetExecTab::WidgetExecTab(WidgetExec::onglet pType, QWidget *pParent) : QWidget(pParent) {
    m_type = pType;
}

void WidgetExecTab::clear() {
    qDebug() << "Onglet " << m_type << " : clear";
}
