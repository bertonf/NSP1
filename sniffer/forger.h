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

class Forger
{
public:
    Forger();
    struct ethhdr *CreateEthHdr(unsigned long, char *);
    unsigned char *CreateARP(unsigned long, char, struct ethhdr*);
};

#endif // FORGER_H
