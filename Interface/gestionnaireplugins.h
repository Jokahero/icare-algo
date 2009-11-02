#ifndef GESTIONNAIREPLUGINS_H
#define GESTIONNAIREPLUGINS_H

#include "plugininterface.h"
#include <QtCore>

class GestionnairePlugins {
public:
    GestionnairePlugins();
    bool chargerPlugin(QString pNomPlugin);
    PluginInterface* getPlugin(QString pNomPlugin);

private:
    QList<PluginInterface*> m_listePlugins;
};

#endif // GESTIONNAIREPLUGINS_H
