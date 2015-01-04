#include "forger.h"

Forger::Forger()
{

}

struct ethhdr *CreateEthHdr(unsigned long dest_mac, char *proto)
{
    struct ethhdr ethhdr;
    //si addresse null -> broadcast
    if (dest == 0)
    {
        memset(ethhdr.h_dest, 0xff, 6);
    }
    else
    {
        ethhdr.h_dest = dest;
    }
        memcpy(&tmp, ifr->ifr_ifru.ifru_hwaddr.sa_data, 6);
        tmp = htobe64((tmp<<16));
        memcpy(ethhdr.h_source, &tmp, 6);
        ethhdr.h_proto = htobe16(*proto);
    return ethhdr;
}

unsigned char *CreateARP(unsigned long dest_ip, char operation, struct ethhdr ethhdr)
{
struct arphdr arphdr;
char macsrc[6];
char ipsrc[4];
char macdest[6];
char ipdest[4];
char *packet;
long tmp;

arphdr.ar_hrd = htobe16(1);
arphdr.ar_pro = htobe16(ethhdr.h_proto); /* ETHERTYPE_IP 0x0800*/
arphdr.ar_hln = 6;
arphdr.ar_pln = ethhdr.h_proto;
arphdr.ar_op = htobe16(operation); /*Demande arp = 1, Reponse arp = 2*/
memcpy(macsrc, &tmp, 6);
memcpy(ipsrc, &((struct sockaddr_in *)&(ifr->ifr_ifru.ifru_addr))->sin_addr.s_addr, 4);
*ipsrc = htobe32(*ipsrc);
memset(macdest, 0, 6);
memcpy(ipdest, &dest_ip, 4);
*ipdest = htobe32(*ipdest);

packet = (char*)malloc(sizeof(struct ethhdr)+sizeof(struct arphdr)+20);
memcpy(packet, &ethhdr, sizeof(struct ethhdr));
memcpy(packet + sizeof(struct ethhdr), &arphdr, sizeof(struct arphdr));
memcpy(packet + sizeof(struct ethhdr) + sizeof(struct arphdr), &macsrc, 6);
memcpy(packet + sizeof(struct ethhdr) + sizeof(struct arphdr) + 6, &ipsrc, 4);
memcpy(packet + sizeof(struct ethhdr) + sizeof(struct arphdr) + 10, &macdest, 6);
memcpy(packet + sizeof(struct ethhdr) + sizeof(struct arphdr) + 16, &ipdest, 4);
return (packet);
}