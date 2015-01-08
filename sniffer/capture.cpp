#include <ostream>
#include <unistd.h>
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
    _captureOn = false;
}

void Capture::SetNetworkInterface(const std::string &networkInterface)
{
    _networkInterface = networkInterface;
}

const bool & Capture::getCaptureOn() const
{
    return (_captureOn);
}

void Capture::setCaptureOn(const bool &b)
{
    _captureMutex.lock();
    _captureOn = b;
    _captureMutex.unlock();
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

    if (bind(_rawSocket, reinterpret_cast<struct sockaddr *>(&sll), sizeof(sll)) == -1)
    {
        std::cerr << "Error : bind()." << std::endl;
        return (false);
    }
    return (true);
}

void Capture::CloseRawSocket()
{
    close(_rawSocket);
}

void Capture::run()
{
    unsigned char *buffer;
    struct sockaddr_ll packetInfo;
    socklen_t packetInfoSize = sizeof(packetInfo);
    int len;
    MyPacket *packet;

    try
    {
        if (InitRawSocket() != true)
        {
            std::cerr << "Error : Raw socket init failed." << std::endl;
            return;
        }
        setCaptureOn(true);
        while (getCaptureOn())
        {
            //buffer = reinterpret_cast<unsigned char*>(malloc(2048));
            buffer = new unsigned char[2048];
            memset(buffer, 0, 2048);
            len = recvfrom(_rawSocket, buffer, 2048, 0, reinterpret_cast<struct sockaddr*>(&packetInfo), &packetInfoSize);
            if (len > 0)
            {
                packet = new MyPacket(packetInfo, buffer, len);
                emit AddPacketToList(packet);
            }
            usleep(100);
        }
        CloseRawSocket();
    }
    catch(std::exception ex)
    {
        std::cerr << "Erreur durant la capture : " << ex.what() << std::endl;
        CloseRawSocket();
    }
}

