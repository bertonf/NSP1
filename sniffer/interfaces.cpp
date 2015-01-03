#include <sys/ioctl.h>
#include <net/if.h>

#include <iostream>
#include <fstream>
#include "interfaces.h"

Interfaces::Interfaces()
{
    //ParseInterfaceList();
    ActiveInterfaceList();
}


const std::vector<std::string> &Interfaces::GetInterfaces()
{
    return (_interfaces);
}

void Interfaces::ParseInterfaceList()
{
    std::ifstream fichier("/proc/net/dev", std::ifstream::in);

    if (fichier)
    {
        std::string ligne;
        std::size_t pos;
        std::size_t found;
        while (std::getline(fichier, ligne))
        {
            pos = ligne.find(":");
            if (pos!=std::string::npos)
            {
                ligne = ligne.substr(0, pos);
                found = ligne.find_first_not_of(" ");
                if (found!=std::string::npos)
                {
                    ligne = ligne.substr(found);
                }
                _interfaces.push_back(ligne);
            }
        }
    }
}

void Interfaces::ActiveInterfaceList()
{
    char buf[1024];
    int tmpSock;
    struct ifconf ifc;
    struct ifreq  *ifr;
    int nbrInterface;
    int i;

    tmpSock = socket(AF_INET, SOCK_DGRAM, 0);
    ifc.ifc_len = sizeof(buf);
    ifc.ifc_buf = buf;

    if (ioctl(tmpSock, SIOCGIFCONF, &ifc) < 0)
    {
        perror("ioctl");
        return;
    }

    ifr = ifc.ifc_req;
    nbrInterface = ifc.ifc_len / sizeof(struct ifreq);

    for (i = 0; i < nbrInterface; i++)
        _interfaces.push_back(ifr[i].ifr_name);
}

