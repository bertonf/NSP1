#include "mypacket.h"

MyPacket::MyPacket(unsigned char *packet, int length)
{
    _buffer = packet;
    _length = length;
    Init();
}

MyPacket::MyPacket(struct sockaddr_ll packetInfo, unsigned char *buffer, int length)
{
    _packetInfo = packetInfo;
    _buffer = buffer;
    _length = length;
    Init();
}

MyPacket::~MyPacket()
{
    delete _buffer;
}

void MyPacket::Init()
{
    _ethhdr = reinterpret_cast<struct ethhdr*>(_buffer);
    _iphdr = NULL;
    _iphdr6 = NULL;
    _arphdr = NULL;

    if (htobe16(_ethhdr->h_proto) == 0x0800) /*IPV4*/
        _iphdr = reinterpret_cast<struct iphdr*>(_buffer + sizeof(struct ethhdr));
    else if (htobe16(_ethhdr->h_proto) == 0x86DD) /*IPV6*/
        _iphdr6 = reinterpret_cast<struct ip6_hdr*>(_buffer + sizeof(struct ethhdr));
    else if (htobe16(_ethhdr->h_proto) == 0x0806) /*ARP*/
        _arphdr = reinterpret_cast<struct arphdr*>(_buffer + sizeof(struct ethhdr));
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
    return (_iphdr);
}

const struct ip6_hdr * MyPacket::getIpHeader6() const
{
    return (_iphdr6);
}

const struct arphdr * MyPacket::getArpHeader() const
{
    return (_arphdr);
}
