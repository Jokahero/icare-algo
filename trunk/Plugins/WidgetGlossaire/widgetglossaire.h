#ifndef WIDGETGLOSSAIRE_H
#define WIDGETGLOSSAIRE_H

#include "../../Interface/plugininterface.h"

class QDockWidget;
class QStandardItemModel;
class QString;
class QTableView;
class QTableWidget;

/*! \brief Widget affichant la liste des variables.

  Affiche leurs noms, types et descriptions.
*/
class WidgetGlossaire : public PluginInterface {

    Q_OBJECT
    Q_INTERFACES(PluginInterface)

public:
    WidgetGlossaire();
    QString getNom();
    QDockWidget* getDockWidget();

public slots:
    void variableAjoutee(QString pNomVar, QString pType, QString pDescription);
    void variableModifiee(QString pNomVar, QString pValeur);
    void reinitialisationGlossaire();

private:
    QDockWidget* m_dockWidget;
    QTableWidget* m_tableau;

    QStandardItemModel *m_modeleGlossaire;
    QTableView *m_vueGlossaire;

private slots:
    void sauvegarderPosition(Qt::DockWidgetArea pPos);
    void sauvegarderEtat(bool pEtat);
};

#endif // WIDGETGLOSSAIRE_H
