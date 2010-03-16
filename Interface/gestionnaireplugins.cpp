#include "gestionnaireplugins.h"

#include <QtCore/QDebug>
#include <QtCore/QDir>
#include <QtCore/QList>
#include <QtCore/QPluginLoader>
#include <QtCore/QString>
#include <QtGui/QApplication>


/*! \brief Détruit tous les plugins chargés.
*/
GestionnairePlugins::~GestionnairePlugins() {
    for (int i = 0; i < m_listePlugins.length(); i++)
        delete m_listePlugins.at(i);
}


/*! \brief Charge le plugin de nom pNomPlugin.

  \param pNomPlugin Nom du plugin à charger.
  \return Vrai si le plugin a été chargé, faux sinon.
*/
bool GestionnairePlugins::chargerPlugin(QString pNomPlugin) {
    QStringList paths;
    paths << "/usr/lib/icare-algo" << qApp->applicationDirPath() + "/Plugins";
    for (int i = 0; i < paths.size(); i++) {
        qDebug() << paths.at(i);
        QDir pluginsDir(paths.at(i));
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
    }

    return false;
}


/*! \brief Renvoie un pointeur vers l'instance du plugin de nom pNomPlugin.

  \param pNomPlugin Nom du plugin recherché.
  \return Un pointeur vers l'instance du plugin, NULL si il n'a pas été trouvé.
*/
PluginInterface* GestionnairePlugins::getPlugin(QString pNomPlugin) {
    for (int i = 0; i < m_listePlugins.size(); i++)
        if (m_listePlugins.at(i)->getNom() == pNomPlugin)
            return m_listePlugins.at(i);
    return NULL;
}


/*! \brief Renvoie la liste de tous les plugins disponibles, chargés ou non.

  \return Liste des plugins disponibles
*/
QList<PluginInterface*> GestionnairePlugins::getListePluginsDispo() {
    QList<PluginInterface*> liste;
    QStringList paths;
    paths << "/usr/lib/icare-algo" << qApp->applicationDirPath() + "/Plugins";
    for (int i = 0; i < paths.size(); i++) {
        qDebug() << paths.at(i);
        QDir pluginsDir(paths.at(i));
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
        foreach (QString nomFichier, pluginsDir.entryList(QDir::Files)) {
            QPluginLoader pluginLoader(pluginsDir.absoluteFilePath(nomFichier));
            QObject *plugin = pluginLoader.instance();
            if (plugin) {
                PluginInterface* pluginInt = qobject_cast<PluginInterface*>(plugin);
                if (pluginInt)
                    liste.append(pluginInt);
            }
        }
    }
    return liste;
}


/*! \brief Renvoie la liste des plugins chargés.

  \return Liste des plugins chargés
*/
QList<PluginInterface*> GestionnairePlugins::getListePlugins() {
    return m_listePlugins;
}
