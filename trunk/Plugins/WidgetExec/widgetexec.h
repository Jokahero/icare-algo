#ifndef WIDGETEXEC_H
#define WIDGETEXEC_H

#include "../../Interface/plugininterface.h"

class QDockWidget;
class QString;
class QTabWidget;

/*! \brief Widget affichant le résultat des analyses, les sorties d'exécutions et permet la saisie lors des exécutions.
*/
class WidgetExec : public PluginInterface {

    Q_OBJECT
    Q_INTERFACES(PluginInterface)

public:
    WidgetExec();
    QString getNom();
    QDockWidget* getDockWidget();

    enum onglet {
        Erreurs = 0,
        Sorties = 1,
    };

public slots:
    void erreurMathematique(MathExp::erreur pErreur);
    void erreurAnalyse(Analyse::erreur pErreur, int pNumLigne);
    void lancerAnalyse(QFile* pFichier);

signals:
    void changementLigne(int pNumLigne);

private:
    QTabWidget* m_tabWidget;
    QDockWidget* m_dockWidget;
};

#endif // WIDGETEXEC_H
