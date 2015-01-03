#ifndef INTERFACES_H
#define INTERFACES_H

#include <iostream>
#include <vector>
#include <string>
class Interfaces
{
private :
    std::vector<std::string> _interfaces;
    void ParseInterfaceList();
    void ActiveInterfaceList();
public:
    Interfaces();
    const std::vector<std::string>& GetInterfaces();
};

#endif // INTERFACES_H
