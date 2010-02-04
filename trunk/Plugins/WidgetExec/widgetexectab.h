#ifndef WIDGETEXECTAB_H
#define WIDGETEXECTAB_H

#include "widgetexec.h"
#include <QtGui/QWidget>

class WidgetExecTab : public QWidget {
    Q_OBJECT

public:
    WidgetExecTab(WidgetExec::onglet pType, QWidget *pParent = 0);
    WidgetExec::onglet getType();

public slots:
    void clear();

private:
    WidgetExec::onglet m_type;
};

#endif // WIDGETEXECTAB_H
