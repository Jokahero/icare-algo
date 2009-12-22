#ifndef WIDGETEXEC_H
#define WIDGETEXEC_H

#include <QtCore>
#include <QtGui>

#include "../../Interface/plugininterface.h"

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

private slots:
    void ajouterTexte(QString pTexte, WidgetExec::onglet);
    void effacerTexte(WidgetExec::onglet);
    void remplacerTexte(QString pTexte, WidgetExec::onglet);

private:
    QTabWidget* m_tabWidget;
    QDockWidget* m_dockWidget;
};

#endif // WIDGETEXEC_H
