#ifndef FORGER_H
#define FORGER_H

#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <linux/if_packet.h>
#include <linux/if_ether.h>
#include <linux/if_arp.h>
#include <linux/if.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <net/ethernet.h>
#include <string.h>
#include<unistd.h>
#include<features.h>
#include<errno.h>
#include<net/if.h>
#include<netinet/ether.h>
#include<linux/ip.h>
#include<linux/tcp.h>
#include<sys/time.h>
#include<iostream>

class Forger
{
public:
    Forger();
int createRawSocket();
int bindRawSocketToInterface(char *, int);
int sendRawPacket(int rawsock, unsigned char *, int);
unsigned short computeChecksum(unsigned char *, int);
struct ethhdr* createEthHeader(char *, char *, int);
struct iphdr *createIPHeader(char *, char *, int);
struct tcphdr *createTCPHeader(int, int);
void createPseudoHeaderAndComputeTcpChecksum(struct tcphdr *, struct iphdr *, unsigned char *, int);
int SendARPpacket(char *, char *, unsigned long, unsigned long, char, char *);
int sendTCPpacket(char *, char *, char *, char *, char *, int, int, string);
};

#endif // FORGER_H
