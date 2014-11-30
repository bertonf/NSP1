#ifndef MYPACKET_H
#define MYPACKET_H

#include <sys/socket.h>
#include <linux/if_packet.h>
#include <linux/if_ether.h>
#include <linux/if.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <string>

class MyPacket
{
    struct sockaddr_ll _packetInfo;
    std::string _buffer;
public:
    MyPacket(struct sockaddr_ll packetInfo,char *buffer);
    const sockaddr_ll &getPacketInfo();
    const std::string &getBuffer();
};

#endif // MYPACKET_H
