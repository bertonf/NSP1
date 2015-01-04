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

 public:
  ReadPcap();
  void run(string fileName);

 signals:
  void AddPacketFromFileToList(MyPacket*);
}
