#include "mypacket.h"

MyPacket::MyPacket(struct sockaddr_ll packetInfo, char *buffer)
{
    _packetInfo = packetInfo;
    _buffer = buffer;
}

struct sockaddr_ll const & MyPacket::getPacketInfo()
{
    return (_packetInfo);
}

std::string const & MyPacket::getBuffer()
{
    return (_buffer);
}
