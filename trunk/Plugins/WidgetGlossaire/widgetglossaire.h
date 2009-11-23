#ifndef WIDGETGLOSSAIRE_H
#define WIDGETGLOSSAIRE_H

#include <QtCore>
#include <QtGui>

#include "../../Interface/plugininterface.h"

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

private:
    QDockWidget* m_dockWidget;
    QTableWidget* m_tableau;
};

#endif // WIDGETGLOSSAIRE_H
