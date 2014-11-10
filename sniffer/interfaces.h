#ifndef INTERFACES_H
#define INTERFACES_H

#include <iostream>
#include <list>
#include <string>
class Interfaces
{
private :
    std::list<std::string> _interfaces;
    void ParseInterfaceList();
public:
    Interfaces();
    const std::list<std::string>& GetInterfaces();
};

#endif // INTERFACES_H
