#ifndef READPCAP_H
#define READPCAP_H

#include <string>
#include <pcap.h>
#include <QObject>
#include "mypacket.h"

class ReadPcap : public QObject
{
    Q_OBJECT

public:
    ReadPcap();
    void run(std::string fileName);
 signals:
    void AddPacketFromFileToList(MyPacket*);
};


#endif // READPCAP_H
