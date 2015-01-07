#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<features.h>
#include<linux/if_packet.h>
#include<linux/if_ether.h>
#include<errno.h>
#include<sys/ioctl.h>
#include<net/if.h>
#include<net/ethernet.h>
#include<netinet/ether.h>
#include<linux/ip.h>
#include<linux/tcp.h>
#include<arpa/inet.h>
#include<string.h>
#include<sys/time.h>
#include<iostream>

using namespace std;

typedef struct PseudoHeader
{
  unsigned long int source_ip;
  unsigned long int dest_ip;
  unsigned char reserved;
  unsigned char protocol;
  unsigned short int tcp_length;
}PseudoHeader;

int createRawSocket(int protocol_to_sniff)
{
  int rawsock;
  
  if((rawsock = socket(PF_PACKET, SOCK_RAW, htons(protocol_to_sniff)))== -1)
    {
      perror("Error creating raw socket: ");
      exit(-1);
    }
  
  return rawsock;
}

int bindRawSocketToInterface(char *device, int rawsock, int protocol)
{
  struct sockaddr_ll sll;
  struct ifreq ifr;
  
  bzero(&sll, sizeof(sll));
  bzero(&ifr, sizeof(ifr));
  
  strncpy((char *)ifr.ifr_name, device, IFNAMSIZ);
  if((ioctl(rawsock, SIOCGIFINDEX, &ifr)) == -1)
    {
      printf("Error getting Interface index !\n");
      exit(-1);
    }
  
  sll.sll_family = AF_PACKET;
  sll.sll_ifindex = ifr.ifr_ifindex;
  sll.sll_protocol = htons(protocol);  
  
  if((bind(rawsock, (struct sockaddr *)&sll, sizeof(sll)))== -1)
    {
      perror("Error binding raw socket to interface\n");
      exit(-1);
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

struct ethhdr* createEthHeader(char *src_mac, char *dst_mac, int protocol)
{
  struct ethhdr *ethernet_header;
  
  ethernet_header = (struct ethhdr *)malloc(sizeof(struct ethhdr));
  
  memcpy(ethernet_header->h_source, (void *)ether_aton(src_mac), 6);
  memcpy(ethernet_header->h_dest, (void *)ether_aton(dst_mac), 6);
  
  ethernet_header->h_proto = htons(protocol);
  
  return (ethernet_header);
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

unsigned char *createData(int len)
{
  unsigned char *data = (unsigned char *)malloc(len);  
  struct timeval tv;
  struct timezone tz;
  int counter = len;	
  
  gettimeofday(&tv, &tz);
  
  srand(tv.tv_sec);
  
  for(counter = 0; counter < len; counter++)
    data[counter] = 255.0 *rand()/(RAND_MAX +1.0);
  
  return data;
}


int sendTCPpacket(char *device, char *ipSrc, char *ipDest, int srcPort, int destPort, string dataI)
{
  int raw;
  unsigned char *data;
  unsigned char *packet;
  struct ethhdr *ethernet_header;
  struct iphdr *ip_header;
  struct tcphdr *tcp_header;
  int pkt_len;
  
  raw = createRawSocket(ETH_P_ALL);
  bindRawSocketToInterface(device, raw, ETH_P_ALL);
  
  ethernet_header = createEthHeader("aa:aa:aa:aa:aa:aa", "bb:bb:bb:bb:bb:bb", ETHERTYPE_IP);
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
  else
    printf("Packet sent successfully\n");
  
  free(ethernet_header);
  free(ip_header);
  free(tcp_header);
  free(data);
  free(packet);
  
  close(raw);
  
  return 0;
}
