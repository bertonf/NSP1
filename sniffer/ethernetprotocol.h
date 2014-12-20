#ifndef ETHERNETPROTOCOL_H
#define ETHERNETPROTOCOL_H

#include <stdio.h>
#include <string>
#include <map>

class EthernetProtocol : public EthernetProtocol
{
    std::map<unsigned char, std::string> _protocolEther;

public:
    EthernetProtocol();
    void InitEtherProt();
    std::string getProtocolName(unsigned int protocolNumber);
};

#endif // ETHERNETPROTOCOL_H
