#ifndef PLUGINMANAGER_H
#define PLUGINMANAGER_H

#include <QObject>
#include <QPluginLoader>
#include <iplugininterface.h>
namespace libsdrkitplugins
{
    class PluginManager
    {
    public:
        PluginManager();
        // Array to store all plugin loaders and loaded plugins
        QList<QPluginLoader*>   pluginloaders;
        QList<iPluginInterface *> plugins;
        bool loadPlugins(QString pluginDir);
        void createPlugins();
        void unloadPlugins();
    };
}
#endif // PLUGINMANAGER_H
