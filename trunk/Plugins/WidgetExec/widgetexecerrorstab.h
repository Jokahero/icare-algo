#ifndef WIDGETEXECERRORSTAB_H
#define WIDGETEXECERRORSTAB_H

#include "widgetexectab.h"

class QListWidget;

class WidgetExecErrorsTab : public WidgetExecTab {
    Q_OBJECT

public:
    WidgetExecErrorsTab(WidgetExec::onglet pType, QWidget *pParent = 0);

public slots:
    void erreurMathematique(MathExp::erreur pErreur);
    void erreurAnalyse(Analyse::erreur pErreur, int pNumLigne);
    void clear();

protected:
    void resizeEvent(QResizeEvent *pE);

private:
    QListWidget* m_liste;
};

#endif // WIDGETEXECERRORSTAB_H
