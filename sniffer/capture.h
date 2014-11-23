#ifndef CAPTURE_H
#define CAPTURE_H

#include <iostream>
#include <string>
#include <QThread>

class Capture : public QThread
{
private :
    int _rawSocket;
    std::string _networkInterface;
    //std::list<pcappacket> _packetList;
    bool InitRawSocket();
public:
    Capture();
    void SetNetworkInterface(std::string);
    void run();
};

#endif // CAPTURE_H
