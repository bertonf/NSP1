#ifndef INTERNETPROTOCOL_H
#define INTERNETPROTOCOL_H

#include <stdio.h>
#include <string>
#include <map>

class InternetProtocol
{
    std::map<unsigned char, std::string> _protocolNumbers;
public:
    InternetProtocol();
    std::string getProtocolName(unsigned char protocolNumber);
};

#endif // INTERNETPROTOCOL_H
