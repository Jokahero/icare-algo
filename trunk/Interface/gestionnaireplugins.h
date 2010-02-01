#ifndef GESTIONNAIREPLUGINS_H
#define GESTIONNAIREPLUGINS_H

#include "plugininterface.h"

template <typename T> class QList;
class QString;

/*! \brief Charge et stocke les plugins.
  */
class GestionnairePlugins {
public:
    bool chargerPlugin(QString pNomPlugin);
    PluginInterface* getPlugin(QString pNomPlugin);
    QList<PluginInterface*> getListePlugins();

private:
    QList<PluginInterface*> m_listePlugins;
};

#endif // GESTIONNAIREPLUGINS_H
