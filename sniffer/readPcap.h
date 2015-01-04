#include <stdio.h>
#include <pcap.h>
#include <stdlib.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/if_ether.h>
#include "mypacket.h"

//defines for the packet type code in an ETHERNET header
#define ETHER_TYPE_IP (0x0800)
#define ETHER_TYPE_8021Q (0x8100)

class ReadPcap
{
 private:
  int i;
  unsigned int pkt_counter;   // packet counter 
  unsigned long byte_counter; //total bytes seen in entire trace 
  unsigned long cur_counter; //counter for current 1-second interval 
  unsigned long max_volume;  //max value of bytes in one-second interval 
  unsigned long current_ts; //current timestamp 
  struct ether_header *eptr;
 
  //temporary packet buffers 
  struct pcap_pkthdr header; // The header that pcap gives us 
  const u_char *packet; // The actual packet 
  u_char *ptr; // printing out hardware header info
  MyPacket *pkt;

 public:
  ReadPcap();
  void run(string fileName);

 signals:
  void AddPacketFromFileToList(MyPacket*);
}
