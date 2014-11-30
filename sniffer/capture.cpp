#include <errno.h>
#include <stdio.h>
#include <sys/socket.h>
#include <linux/if_packet.h>
#include <linux/if_ether.h>
#include <linux/if.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <string.h>
#include <QMessageBox>
#include "capture.h"

Capture::Capture()
{
    _networkInterface = "";
    _rawSocket = -1;
}

void Capture::SetNetworkInterface(std::string networkInterface)
{
    _networkInterface = networkInterface;
}

bool Capture::InitRawSocket()
{
    struct sockaddr_ll sll;
    struct ifreq ifr;

    _rawSocket = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
    /*Verifier que ce protocol (ETH_P_ALL = eth protocol ALL (udp, tcp, etc....)) marche aussi avec le wifi*/
    if (_rawSocket == -1)
    {
        perror("Error : ");
        std::cerr << "Error : socket() -> Initialisation error." << std::endl;
        return (false);
    }

    memset(&sll, 0, sizeof(sll));
    memset(&ifr, 0, sizeof(ifr));

    strncpy(ifr.ifr_name, _networkInterface.c_str(), IFNAMSIZ);
    /*IFNAMSIZ : Define sur la taille de la chaine (ifr_name[IFNAMSIZ]).*/
    if (ioctl(_rawSocket, SIOCGIFINDEX, &ifr) == -1)
    {
        std::cerr << "Error : ioctl() -> Network interface not found." << std::endl;
        return (false);
    }

    sll.sll_family = AF_PACKET;
    sll.sll_ifindex = ifr.ifr_ifindex;
    sll.sll_protocol = htons(ETH_P_ALL);

    if (bind(_rawSocket, (struct sockaddr *)&sll, sizeof(sll)) == -1)
    {
        std::cerr << "Error : bind()." << std::endl;
        return (false);
    }
    return (true);
}

void Capture::run()
{
    char buffer[2048];
    struct sockaddr_ll packetInfo;
    socklen_t packetInfoSize = sizeof(packetInfo);
    int len;
    MyPacket *packet;

    if (InitRawSocket() != true)
    {
        std::cerr << "Error : Raw socket init failed." << std::endl;
        return;
    }
    std::cout << "Init done" << std::endl;
    std::cout << "### packet content ###" << std::endl;
    while (1) /*faudra mettre un bool pour pouvoir sortir de la boucle quand on quitte le program ou qu'on change d'interface reseau.*/
    {
        memset(buffer, 0, 2048);
        len = recvfrom(_rawSocket, buffer, 2048, 0, (struct sockaddr*)&packetInfo, &packetInfoSize);
        /*pour analyser le packet ya des infos dans la structure "packetinfo" et le buffer*/
        /*le but est d'alimenter une fifo de pcappacket (structure pcap)*/
        /*Et ensuite d'afficher le contenu dans l'ihm*/
        packet = new MyPacket(packetInfo, buffer);
        AddPacketToList(packet);
    if (len > 0)
        std::cout << "size : " << len << " :: "
                  << " :: Protocol : " << IP.getProtocolName(packetInfo.sll_hatype)
                  << " :: Buffer :" << buffer << std::endl;
    }
}

void Capture::AddPacketToList(MyPacket* packet)
{
    _mutex.lock();
    _packetList.push(*packet);
    _mutex.unlock();
}

const MyPacket & Capture::GetTopPacketList()
{
    _mutex.lock();
    MyPacket const & packet = _packetList.front();
    _packetList.pop();
    _mutex.unlock();
    return (packet);
}

bool Capture::isListEmpty()
{
    return (_packetList.empty());
}
