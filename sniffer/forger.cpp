#include "forger.h"

Forger::Forger()
{

}

/*
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
*/


/*
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
*/

int createRawSocket()
{
  int rawsock;

  if((rawsock = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL)))== -1)
    {
      perror("Error creating raw socket: ");
      exit(-1);
    }

  return rawsock;
}

int bindRawSocketToInterface(char *device, int rawsock)
{
  struct sockaddr_ll sll;
  struct ifreq ifr;

  bzero(&sll, sizeof(sll));
  bzero(&ifr, sizeof(ifr));

  strncpy((char *)ifr.ifr_name, device, IFNAMSIZ);
  if((ioctl(rawsock, SIOCGIFINDEX, &ifr)) == -1)
    {
      printf("Error getting Interface index !\n");
      return(-1);
    }

  sll.sll_family = AF_PACKET;
  sll.sll_ifindex = ifr.ifr_ifindex;
  sll.sll_protocol = htons(ETH_P_ALL);

  if((bind(rawsock, (struct sockaddr *)&sll, sizeof(sll)))== -1)
    {
      perror("Error binding raw socket to interface\n");
      return(-1);
    }

  return 1;
}

int sendRawPacket(int rawsock, unsigned char *pkt, int pkt_len)
{
  int sent= 0;

  if((sent = write(rawsock, pkt, pkt_len)) != pkt_len)
    {
      printf("Could only send %d bytes of packet of length %d\n", sent, pkt_len);
      return 0;
    }

  return 1;
}



unsigned short computeChecksum(unsigned char *data, int len)
{
  long sum = 0;
  unsigned short *temp = (unsigned short *)data;

  while(len > 1)
    {
      sum += *temp++;
      if(sum & 0x80000000)
    sum = (sum & 0xFFFF) + (sum >> 16);
      len -= 2;
    }

  if(len)
    sum += (unsigned short) *((unsigned char *)temp);

  while(sum>>16)
    sum = (sum & 0xFFFF) + (sum >> 16);

  return ~sum;
}

struct ethhdr* createEthHeader(char *src_mac, char *dst_mac, int protocol)
{
  struct ethhdr *ethernet_header;

  ethernet_header = (struct ethhdr *)malloc(sizeof(struct ethhdr));

  memcpy(ethernet_header->h_source, (void *)ether_aton(src_mac), 6);
  memcpy(ethernet_header->h_dest, (void *)ether_aton(dst_mac), 6);

  ethernet_header->h_proto = htons(protocol);

  return (ethernet_header);
}

struct iphdr *createIPHeader(char *ipSrc, char *ipDest, int dataSize)
{
  struct iphdr *ip_header;

  ip_header = (struct iphdr *)malloc(sizeof(struct iphdr));

  ip_header->version = 4;
  ip_header->ihl = (sizeof(struct iphdr))/4 ;
  ip_header->tos = 0;
  ip_header->tot_len = htons(sizeof(struct iphdr) + sizeof(struct tcphdr) + dataSize);
  ip_header->id = htons(111);
  ip_header->frag_off = 0;
  ip_header->ttl = 111;
  ip_header->protocol = IPPROTO_TCP;
  ip_header->check = 0;
  ip_header->saddr = inet_addr(ipSrc);
  ip_header->daddr = inet_addr(ipDest);

  ip_header->check = computeChecksum((unsigned char *)ip_header, ip_header->ihl*4);

  return (ip_header);
}

struct tcphdr *createTCPHeader(int srcPort, int destPort)
{
  struct tcphdr *tcp_header;

  tcp_header = (struct tcphdr *)malloc(sizeof(struct tcphdr));

  tcp_header->source = htons(srcPort);
  tcp_header->dest = htons(destPort);
  tcp_header->seq = htonl(111);
  tcp_header->ack_seq = htonl(111);
  tcp_header->res1 = 0;
  tcp_header->doff = (sizeof(struct tcphdr))/4;
  tcp_header->syn = 1;
  tcp_header->window = htons(100);
  tcp_header->check = 0;
  tcp_header->urg_ptr = 0;

  return (tcp_header);
}

void createPseudoHeaderAndComputeTcpChecksum(struct tcphdr *tcp_header, struct iphdr *ip_header, unsigned char *data, int dataSize)
{
  int segment_len = ntohs(ip_header->tot_len) - ip_header->ihl*4;

  int header_len = sizeof(PseudoHeader) + segment_len;

  unsigned char *hdr = (unsigned char *)malloc(header_len);

  PseudoHeader *pseudo_header = (PseudoHeader *)hdr;

  pseudo_header->source_ip = ip_header->saddr;
  pseudo_header->dest_ip = ip_header->daddr;
  pseudo_header->reserved = 0;
  pseudo_header->protocol = ip_header->protocol;
  pseudo_header->tcp_length = htons(segment_len);

  memcpy((hdr + sizeof(PseudoHeader)), (void *)tcp_header, tcp_header->doff*4);
  memcpy((hdr + sizeof(PseudoHeader) + tcp_header->doff*4), data, dataSize);

  tcp_header->check = computeChecksum(hdr, header_len);

  free(hdr);
  return;
}

int SendARPpacket(char *src_ipmac, char *dest_ipmac, unsigned long src_ip, unsigned long dest_ip, char operation, char *iface)
{
struct ethhdr ethhdr;
struct arphdr arphdr;

char macsrc[6];
//char ipsrc[4];
char macdest[6];
//char ipdest[4];

unsigned int ipsrc;
unsigned int ipdest;
unsigned char *packet;

//long tmp;

ethhdr = new struct ethhdr;
arphdr = new struct arphdr;

ethhdr = createEthHeader(src_ipmac, dest_ipmac, ETHERTYPE_ARP);
arphdr.ar_hrd = htobe16(1);
arphdr.ar_pro = 0x0806; /*a test*/
arphdr.ar_hln = 6;
arphdr.ar_pln = 4;  /* ipv4 en dur pour le moment*/
arphdr.ar_op = htobe16(operation); /*Demande arp = 1, Reponse arp = 2*/

ipsrc = inet_addr(src_ip);
ipdest = inet_addr(dest_ip);
//memcpy(macsrc, &tmp, 6);
//memset(macdest, 0, 6);


packet = (unsigned char*)malloc(sizeof(struct ethhdr)+sizeof(struct arphdr)+20);
memcpy(packet, ethhdr, sizeof(struct ethhdr));
memcpy(packet + sizeof(struct ethhdr), &arphdr, sizeof(struct arphdr));
memcpy(packet + sizeof(struct ethhdr) + sizeof(struct arphdr), &(ethhdr.h_source), 6);
memcpy(packet + sizeof(struct ethhdr) + sizeof(struct arphdr) + 6, &ipsrc, 4);
memcpy(packet + sizeof(struct ethhdr) + sizeof(struct arphdr) + 10, &(ethhdr.h_dest), 6);
memcpy(packet + sizeof(struct ethhdr) + sizeof(struct arphdr) + 16, &ipdest, 4);

raw = createRawSocket();
bindRawSocketToInterface(iface, raw, ETH_P_ALL);


if(!sendRawPacket(raw, packet, sizeof(packet)))
  perror("Error sending packet");

free(ethhdr);
free(packet);
close (raw);

return (0);
}


int sendTCPpacket(char *device, char *src_ipmac, char *dest_ipmac, char *ipSrc, char *ipDest, int srcPort, int destPort, string dataI)
{
  int raw;
  unsigned char *data;
  unsigned char *packet;
  struct ethhdr *ethernet_header;
  struct iphdr *ip_header;
  struct tcphdr *tcp_header;
  int pkt_len;

  raw = createRawSocket();
  bindRawSocketToInterface(device, raw, ETH_P_ALL);

  ethernet_header = createEthHeader(src_ipmac, dest_ipmac, ETHERTYPE_IP);
  ip_header = createIPHeader(ipSrc, ipDest, dataI.length());
  tcp_header = createTCPHeader(srcPort, destPort);

  data = (unsigned char *)dataI.c_str();

  createPseudoHeaderAndComputeTcpChecksum(tcp_header, ip_header, data, dataI.length());

  pkt_len = sizeof(struct ethhdr) + ntohs(ip_header->tot_len);

  packet = (unsigned char *)malloc(pkt_len);

  memcpy(packet, ethernet_header, sizeof(struct ethhdr));
  memcpy((packet + sizeof(struct ethhdr)), ip_header, ip_header->ihl*4);
  memcpy((packet + sizeof(struct ethhdr) + ip_header->ihl*4),tcp_header, tcp_header->doff*4);
  memcpy((packet + sizeof(struct ethhdr) + ip_header->ihl*4 + tcp_header->doff*4), data, dataI.length());

  if(!sendRawPacket(raw, packet, pkt_len))
    perror("Error sending packet");

  free(ethernet_header);
  free(ip_header);
  free(tcp_header);
  free(data);
  free(packet);

  close(raw);

  return 0;
}
