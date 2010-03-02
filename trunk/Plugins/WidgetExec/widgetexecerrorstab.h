#ifndef WIDGETEXECERRORSTAB_H
#define WIDGETEXECERRORSTAB_H

#include "widgetexectab.h"

template <typename T> class QList;
class QListWidget;

class WidgetExecErrorsTab : public WidgetExecTab {
    Q_OBJECT

public:
    WidgetExecErrorsTab(WidgetExec::onglet pType, QWidget *pParent = 0);

public slots:
    void erreurLogique(ExpressionLogique::erreur pErreur, int pNumLigne);
    void erreurMathematique(MathExp::erreur pErreur, int pNumLigne);
    void erreurAnalyse(Analyse::erreur pErreur, int pNumLigne);
    void clear();

signals:
    void changementLigne(int pNumLigne);

private slots:
    void ligneChangee();

protected:
    void resizeEvent(QResizeEvent *pE);

private:
    QListWidget* m_liste;
    QList<int>* m_listeNumLignes;
};

#endif // WIDGETEXECERRORSTAB_H
