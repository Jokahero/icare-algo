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
    void erreurMathematique(MathExp::erreur pErreur);
    void erreurAnalyse(Analyse::erreur pErreur, int pNumLigne);
    void clear();

signals:
    void changementLigne(int pNumLigne);

private slots:
    void ligneChangee(int pLigne);

protected:
    void resizeEvent(QResizeEvent *pE);

private:
    QListWidget* m_liste;
    QList<int>* m_listeNumLignes;
};

#endif // WIDGETEXECERRORSTAB_H
