#ifndef MYPACKET_H
#define MYPACKET_H

#include <sys/socket.h>
#include <linux/if_packet.h>
#include <linux/if_ether.h>
#include <linux/if.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/ip6.h>
#include <string>

class MyPacket
{
    struct sockaddr_ll _packetInfo;
    unsigned char *_buffer;
    struct ethhdr *_ethhdr;
    struct arphrd *_arphdr;
    struct iphdr *_iphdr;
    struct ip6_hdr *_iphdr6;
public:
    MyPacket(unsigned char *packet);
    MyPacket(struct sockaddr_ll packetInfo,unsigned char *buffer);
    ~MyPacket();
    const sockaddr_ll &getPacketInfo() const;
    unsigned char *getBuffer() const;
    const struct ethhdr *getEthHeader() const;
    const struct iphdr *getIpHeader() const;
    const struct ip6_hdr *getIpHeader6() const;
};

#endif // MYPACKET_H
