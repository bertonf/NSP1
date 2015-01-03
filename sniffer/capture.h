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
    bool        _captureOn;
    QMutex      _captureMutex;
    int         _rawSocket;
    std::string _networkInterface;
    InternetProtocol IP;
    std::queue<MyPacket> _packetList;
    bool InitRawSocket();
    void CloseRawSocket();
public:
    Capture();
    void SetNetworkInterface(const std::string &);
    const bool & getCaptureOn() const;
    void setCaptureOn(const bool &);
    void run();
    //void AddPacketToList(MyPacket *);
    /*const MyPacket & GetTopPacketList();
    bool isListEmpty();*/
signals:
    void AddPacketToList(MyPacket*);
};

#endif // CAPTURE_H
