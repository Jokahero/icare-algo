#include "gestionnaireplugins.h"

GestionnairePlugins::GestionnairePlugins() {
}

bool GestionnairePlugins::chargerPlugin(QString pNomPlugin) {
    QDir pluginsDir(qApp->applicationDirPath());
#if defined(Q_OS_WIN)
    if (pluginsDir.dirName().toLower() == "debug" || pluginsDir.dirName().toLower() == "release")
        pluginsDir.cdUp();
#elif defined(Q_OS_MAC)
    if (pluginsDir.dirName() == "MacOS") {
        pluginsDir.cdUp();
        pluginsDir.cdUp();
        pluginsDir.cdUp();
    }
#endif
    pluginsDir.cd("Plugins");
    foreach (QString nomFichier, pluginsDir.entryList(QDir::Files)) {
        QPluginLoader pluginLoader(pluginsDir.absoluteFilePath(nomFichier));
        QObject *plugin = pluginLoader.instance();
        if (plugin) {
            PluginInterface* pluginInt = qobject_cast<PluginInterface*>(plugin);
            if (pluginInt) {
                if (pluginInt->getNom() == pNomPlugin) {
                    m_listePlugins.append(pluginInt);
                    qDebug() << "Plugin " << pNomPlugin << " chargé.";
                    return true;
                }
            }
        }
    }

    return false;
}

PluginInterface* GestionnairePlugins::getPlugin(QString pNomPlugin) {
    for (int i = 0; i < m_listePlugins.size(); i++)
        if (m_listePlugins.at(i)->getNom() == pNomPlugin)
            return m_listePlugins.at(i);
    return NULL;
}
