#include "mypacket.h"

MyPacket::MyPacket(struct sockaddr_ll packetInfo, unsigned char *buffer)
{
    _packetInfo = packetInfo;
    _buffer = buffer;
    _ethhdr = reinterpret_cast<struct ethhdr*>(buffer);
    _iphdr = reinterpret_cast<struct iphdr*>(buffer + sizeof(struct ethhdr));
    if (_iphdr->version == 6)
        _iphdr6 = reinterpret_cast<struct ip6_hdr*>(buffer + sizeof(struct ethhdr));
    else
        _iphdr6 = NULL;

}

struct sockaddr_ll const & MyPacket::getPacketInfo() const
{
    return (_packetInfo);
}

unsigned char * MyPacket::getBuffer() const
{
    return (_buffer);
}

const struct ethhdr * MyPacket::getEthHeader() const
{
    return (_ethhdr);
}

const struct iphdr * MyPacket::getIpHeader() const
{
    if (_iphdr != NULL)
        return (_iphdr);
    else
        return (NULL);
}

const struct ip6_hdr * MyPacket::getIpHeader6() const
{
    if (_iphdr6 != NULL)
        return (_iphdr6);
    else
        return (NULL);
}
