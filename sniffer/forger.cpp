#include "forger.h"

Forger::Forger()
{

}


int InitSocket()
{
  int sock;

  printf("Initialisation du socket.\n");
  sock = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
  if (-1 == sock)
    {
      perror("socket()");
      return (-1);
    }
  return (sock);
}

int BindSocket(int sock, struct sockaddr_ll *sll, struct ifreq *ifr)
{
  sll->sll_family = AF_PACKET;
  sll->sll_ifindex = ifr->ifr_ifindex;
  sll->sll_protocol = htons(ETH_P_ALL);

  if (-1 == bind(sock, (struct sockaddr*)sll, sizeof(*sll)))
    {
      perror("bind");
      return (-1);
    }
  return (0);
}


unsigned long GetMacSrc()
{
    unsigned long macsrc;
    memcpy(ipsrc, &((struct sockaddr_in *)&(ifr->ifr_ifru.ifru_addr))->sin_addr.s_addr, 4);

    return macsrc;
}

struct ethhdr *CreateEthHdr(unsigned long dest_mac, char *proto)
{
    struct ethhdr *ethhdr;
    long tmp;
    //si addresse null -> broadcast
    ethhdr = new struct ethhdr;
    if (dest_mac == 0)
    {
        memset(ethhdr->h_dest, 0xff, 6);
    }
    else
    {
        memcpy(ethhdr->h_dest, dest_mac, 6);
        ethhdr->h_dest = htobe64r(ethhdr->h_dest);
    }
        memcpy(&tmp, ifr->ifr_ifru.ifru_hwaddr.sa_data, 6);
        tmp = htobe64((tmp<<16));
        memcpy(ethhdr->h_source, &tmp, 6);
        memcpy(ethhdr->h_proto, proto, 2); // up
        ethhdr->h_proto = htobe16(ethhdr->h_proto); // up
    return ethhdr;
}

unsigned char *CreateARP(unsigned long dest_ip, char operation, struct ethhdr *ethhdr, char *iface)
{
struct arphdr arphdr;

char macsrc[6];
char ipsrc[4];
char macdest[6];
char ipdest[4];
unsigned char *packet;
long tmp;

arphdr.ar_hrd = htobe16(1);
arphdr.ar_pro = 0x0806; /*a test*/
arphdr.ar_hln = 6;
arphdr.ar_pln = 4;  /* ipv4 en dur pour le moment*/
arphdr.ar_op = htobe16(operation); /*Demande arp = 1, Reponse arp = 2*/
memcpy(macsrc, &tmp, 6);
//memcpy(ipsrc, &((struct sockaddr_in *)&(ifr->ifr_ifru.ifru_addr))->sin_addr.s_addr, 4);
isprc = GetMacSrc();
*ipsrc = htobe32(*ipsrc);
memset(macdest, 0, 6);
memcpy(ipdest, &dest_ip, 4);
*ipdest = htobe32(*ipdest);

packet = (unsigned char*)malloc(sizeof(struct ethhdr)+sizeof(struct arphdr)+20);
memcpy(packet, ethhdr, sizeof(struct ethhdr));
memcpy(packet + sizeof(struct ethhdr), &arphdr, sizeof(struct arphdr));
memcpy(packet + sizeof(struct ethhdr) + sizeof(struct arphdr), &macsrc, 6);
memcpy(packet + sizeof(struct ethhdr) + sizeof(struct arphdr) + 6, &ipsrc, 4);
memcpy(packet + sizeof(struct ethhdr) + sizeof(struct arphdr) + 10, &macdest, 6);
memcpy(packet + sizeof(struct ethhdr) + sizeof(struct arphdr) + 16, &ipdest, 4);
return (packet);
}
