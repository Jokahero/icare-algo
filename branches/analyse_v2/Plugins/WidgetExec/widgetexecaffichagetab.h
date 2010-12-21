#ifndef WIDGETEXECAFFICHAGETAB_H
#define WIDGETEXECAFFICHAGETAB_H

#include "widgetexectab.h"

class QTextEdit;

class WidgetExecAffichageTab : public WidgetExecTab {
    Q_OBJECT

public:
    WidgetExecAffichageTab(WidgetExec::onglet pType, QWidget *parent = 0);

public slots:
    virtual void clear();
    void afficher(QString pChaine);

private:
    QTextEdit* m_textEdit;

protected:
    void resizeEvent(QResizeEvent *pE);

};

#endif // WIDGETEXECAFFICHAGETAB_H
