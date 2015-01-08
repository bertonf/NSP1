#ifndef FORGER_H
#define FORGER_H

#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <linux/if_packet.h>
//#include <linux/if_ether.h>
//#include <linux/if_arp.h>
#include <linux/ip.h>
#include <linux/if.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <net/ethernet.h>
#include <string.h>
#include <unistd.h>
#include <features.h>
//#include <net/if.h>
#include <netinet/ether.h>
#include <linux/tcp.h>
#include <sys/time.h>
#include <iostream>

class Forger
{
public:
    Forger();
int createRawSocket();
int bindRawSocketToInterface(const char *, int);
int sendRawPacket(int rawsock, unsigned char *, int);
unsigned short computeChecksum(unsigned char *, int);
struct ethhdr* createEthHeader(const char *, const char *, int);
struct iphdr *createIPHeader(const char *, const char *, int);
struct tcphdr *createTCPHeader(int, int);
void createPseudoHeaderAndComputeTcpChecksum(struct tcphdr *, struct iphdr *, char *, int);
int sendARPpacket(char *, char *, char *, char *, char , char *);
int sendTCPpacket(const char *ipSrc, const char *ipDest, int srcPort, int destPort, const char *src_ipmac, const char *dest_ipmac, const char *device, char *data);
};

#endif // FORGER_H
