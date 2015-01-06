#include <iostream>
#include "readPcap.h"

ReadPcap::ReadPcap()
{
}

void ReadPcap::run(std::string fileName)
{
  struct pcap_pkthdr header;
  const u_char *packet;
  MyPacket *pkt;
  pcap_t *handle; 
  char errbuf[PCAP_ERRBUF_SIZE];

  handle = pcap_open_offline(fileName.c_str(), errbuf);
  
  if (handle == NULL)
    { 
      std::cerr << "Couldn't open pcap file " << fileName << ", " << errbuf << std::endl;
      return;
    }
  
  while (NULL != (packet = pcap_next(handle,&header)))
    { 
      u_char *pkt_ptr = (u_char *)packet;
      pkt = new MyPacket(pkt_ptr, header.caplen);
      
      emit AddPacketFromFileToList(pkt);
    }
  
    pcap_close(handle);
    return;
}
