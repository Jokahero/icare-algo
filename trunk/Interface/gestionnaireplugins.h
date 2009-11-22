#ifndef GESTIONNAIREPLUGINS_H
#define GESTIONNAIREPLUGINS_H

#include "plugininterface.h"
#include <QtCore>

/*! \brief Charge et stocke les plugins.
  */
class GestionnairePlugins {
public:
    bool chargerPlugin(QString pNomPlugin);
    PluginInterface* getPlugin(QString pNomPlugin);

private:
    QList<PluginInterface*> m_listePlugins;
};

#endif // GESTIONNAIREPLUGINS_H
