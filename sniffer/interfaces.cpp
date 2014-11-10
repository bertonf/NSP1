#include <iostream>
#include <fstream>
#include "interfaces.h"

Interfaces::Interfaces()
{
    ParseInterfaceList();
}


const std::list<std::string>& Interfaces::GetInterfaces()
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
