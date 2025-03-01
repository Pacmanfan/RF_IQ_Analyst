#include "pluginmanager.h"
#include <QDir>
#include <QLibraryInfo>

using namespace libsdrkitplugins;
char StreamItemStrings[5][11] =
{
    "Complex",
    "Float",
    "Int",
    "Short",
    "Byte"
};

PluginManager::PluginManager()
{

}


bool PluginManager::loadPlugins(QString pluginDir)
{
     QDir pluginsDir(pluginDir);
    // "exampleplugins" is the folder where you are exported plugins
    // by Qt macro Q_EXPORT_PLUGIN2(exampleplugins, YourPlugin);
    foreach (QString fileName, pluginsDir.entryList(QDir::Files))
    {
        // Create plugin loader
        QPluginLoader* pluginLoader = new QPluginLoader(pluginsDir.absoluteFilePath(fileName));
        // Store loader to array
        pluginloaders.append(pluginLoader);
        // Load plugin
        bool ret = pluginLoader->load();
        if (ret)
        {
             plugins.append( qobject_cast<iPluginInterface*>(pluginLoader->instance()));
        }
    }
    // Did we find any plugins?
    if (pluginloaders.isEmpty())
        return false;
    else
        return true;
}


void PluginManager::createPlugins()
{
    // Show data of all media plugins in different tabs
    for (int i=0 ; i < pluginloaders.count() ; i++)
    {
        QPluginLoader* pluginLoader = pluginloaders[i];
        // Create plugin instance
        QObject *plugin = pluginLoader->instance();
        if (plugin)
        {
            // Plugin instance created
            // Cast plugin to iPluginInterface,
            iPluginInterface* pluginIF = qobject_cast<iPluginInterface*>(plugin);
            plugins.append(pluginIF);
            // Signal / slot, if needed
            //QObject::connect(this, SIGNAL(send(QString *)),
            //        pluginIF, SLOT(someSlot(QString *)));
        }
        else
        {
            // Could not create plugin instance, delete pluginloader
            delete pluginLoader;
            pluginloaders.removeAt(i);
            i--;
        }
    }
}


void PluginManager::unloadPlugins()
{
    // Unload plugins and clear plugin array
    foreach (QPluginLoader* pluginLoader, pluginloaders)
    {
        pluginLoader->unload();
        delete pluginLoader;
    }
    pluginloaders.clear();
}
