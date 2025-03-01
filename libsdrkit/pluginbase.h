#ifndef PLUGINBASE_H
#define PLUGINBASE_H


#include <iplugininterface.h>
#include <QUdpSocket>
#include <QVector>

#define AUDIO_PORT 7355 // the port used by plugins to stream their audio back to the app to be played / saved
#define START_PORT 10001


class PortEntry
{
public:
    PortEntry();
    QUdpSocket *socket;
    int m_port;
    int m_idx;
};

#endif // PLUGINBASE_H
