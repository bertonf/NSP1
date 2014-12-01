#ifndef INTERNETPROTOCOL_H
#define INTERNETPROTOCOL_H

#include <stdio.h>
#include <string>
#include <map>

class InternetProtocol
{
    std::map<unsigned char, std::string> _protocolNumbersv4;
    std::map<unsigned char, std::string> _protocolNumbersv6;
public:
    InternetProtocol();
    void initProtoIPV4();
    void initProtoIPV6();
    std::string getProtocolName(unsigned char protocolNumber);
};

#endif // INTERNETPROTOCOL_H
