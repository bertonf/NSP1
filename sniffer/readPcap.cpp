#include "readPcap.h"

ReadPcap::ReadPcap()
{
}

void ReadPcap::run(string fileName)
{
  unsigned int pkt_counter = 0;   // packet counter 
  unsigned long byte_counter = 0; //total bytes seen in entire trace 
  unsigned long cur_counter = 0; //counter for current 1-second interval 
  unsigned long max_volume = 0;  //max value of bytes in one-second interval 
  unsigned long current_ts = 0; //current timestamp 
  struct ether_header *eptr;
 
  //temporary packet buffers 
  struct pcap_pkthdr header; // The header that pcap gives us 
  const u_char *packet; // The actual packet 
  u_char *ptr; // printing out hardware header info
  MyPacket *pkt;
   
  //open the pcap file 
  pcap_t *handle; 
  char errbuf[PCAP_ERRBUF_SIZE];
  handle = pcap_open_offline(fileName, errbuf);   //call pcap library function 
  
  if (handle == NULL)
    { 
      fprintf(stderr,"Couldn't open pcap file %s: %s\n", /*file name*/, errbuf); 
      return(2); 
    }
  
  while (packet = pcap_next(handle,&header))
    { 
      // header contains information about the packet
      u_char *pkt_ptr = (u_char *)packet; //cast a pointer to the packet data 
      pkt = new MyPacket(pkt_ptr);
      
      emit AddPacketFromFileToList(pkt);
      
      cur_counter += packet_length; 
      byte_counter += packet_length; //byte counter update 
      pkt_counter++; //increment number of packets seen 
    }
  
  pcap_close(handle);  //close the pcap file 

  byte_counter /= 1e6;  //convert to MB to make easier to read 

  printf("Processed %d packets and %u MBytes, in %d files\n", pkt_counter, byte_counter, argc-1);
  return 0; //done
}
