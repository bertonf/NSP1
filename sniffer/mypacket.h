#ifndef MYPACKET_H
#define MYPACKET_H

#include <sys/socket.h>
#include <linux/if_packet.h>
#include <linux/if_ether.h>
#include <linux/if_arp.h>
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
    int _length;
    struct ethhdr *_ethhdr;
    struct arphdr *_arphdr;
    struct iphdr *_iphdr;
    struct ip6_hdr *_iphdr6;
public:
    MyPacket(unsigned char *packet, int length);
    MyPacket(struct sockaddr_ll packetInfo,unsigned char *buffer, int length);
    ~MyPacket();
    void Init();
    const sockaddr_ll &getPacketInfo() const;
    unsigned char *getBuffer() const;
    int getLength() const;
    const struct ethhdr *getEthHeader() const;
    const struct iphdr *getIpHeader() const;
    const struct ip6_hdr *getIpHeader6() const;
    const struct arphdr *getArpHeader() const;
};

#endif // MYPACKET_H
