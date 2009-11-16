#ifndef PLUGININTERFACE_H
#define PLUGININTERFACE_H

#include <QtCore/QString>
#include <QtPlugin>
#include <QtGui/QDockWidget>

class PluginInterface {
public:
    virtual ~PluginInterface() {}
    virtual QString getNom() = 0;
    virtual QDockWidget* getDockWidget() { return NULL; };
};

Q_DECLARE_INTERFACE(PluginInterface,
                    "com.icare.Plugin.ModuleInterface/1.0");

#endif // PLUGININTERFACE_H
