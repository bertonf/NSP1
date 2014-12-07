#ifndef CAPTURE_H
#define CAPTURE_H

#include <iostream>
#include <string>
#include <queue>
#include <QObject>
#include <QThread>
#include <QMutex>
#include "internetprotocol.h"
#include "mypacket.h"

class Capture : public QThread
{
    Q_OBJECT

private :
    int _rawSocket;
    std::string _networkInterface;
     InternetProtocol IP;
    std::queue<MyPacket> _packetList;
    QMutex _mutex;
    bool InitRawSocket();
public:
    Capture();
    void SetNetworkInterface(std::string);
    void run();
    //void AddPacketToList(MyPacket *);
    /*const MyPacket & GetTopPacketList();
    bool isListEmpty();*/
signals:
    void AddPacketToList(MyPacket*);
};

#endif // CAPTURE_H
