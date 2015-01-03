#include "readPcap.h"

ReadPcap::ReadPcap()
{
  pkt_counter=0; 
  byte_counter=0; 
  cur_counter=0; 
  max_volume=0;
  current_ts=0;
}

void ReadPcap::run(string fileName)
{
//-------- Begin Main Packet Processing Loop -------------------  

    //open the pcap file 
    pcap_t *handle; 
    char errbuf[PCAP_ERRBUF_SIZE]; //not sure what to do with this, oh well 
    handle = pcap_open_offline(fileName, errbuf);   //call pcap library function 
 
    if (handle == NULL)
      { 
	fprintf(stderr,"Couldn't open pcap file %s: %s\n", /*file name*/, errbuf); 
	return(2); 
      }
 
    //----------------- 
    //begin processing the packets in this particular file, one at a time 
 
    while (packet = pcap_next(handle,&header))
      { 
      // header contains information about the packet (e.g. timestamp) 
	u_char *pkt_ptr = (u_char *)packet; //cast a pointer to the packet data 
	pkt = new MyPacket(pkt_ptr);
	emit AddPacketFromFileToList(pkt);







      //parse the first (ethernet) header, grabbing the type field 
      /*int ether_type = ((int)(pkt_ptr[12]) << 8) | (int)pkt_ptr[13]; 
      int ether_offset = 0; 
 
      if (ether_type == ETHER_TYPE_IP) //most common 
        ether_offset = 14; 
      else if (ether_type == ETHER_TYPE_8021Q) //my traces have this 
         ether_offset = 18; 
      else 
         fprintf(stderr, "Unknown ethernet type, %04X, skipping...\n", ether_type); 
 
      //parse the IP header 
      pkt_ptr += ether_offset;  //skip past the Ethernet II header 
      struct ip *ip_hdr = (struct ip *)pkt_ptr; //point to an IP header structure 
 
      int packet_length = ntohs(ip_hdr->ip_len); 
 
      //check to see if the next second has started, for statistics purposes 
      if (current_ts == 0) {  //this takes care of the very first packet seen 
         current_ts = header.ts.tv_sec; 
      } else if (header.ts.tv_sec > current_ts) { 
         printf("%d KBps\n", cur_counter/1000); //print 
         cur_counter = 0; //reset counters 
         current_ts = header.ts.tv_sec; //update time interval 
      } 
    //lets start with the ether header... 
    eptr = (struct ether_header *) packet;

    // Do a couple of checks to see what packet type we have..
    if (ntohs (eptr->ether_type) == ETHERTYPE_IP)
    {
        printf("Ethernet type hex:%x dec:%d is an IP packet\n",
                ntohs(eptr->ether_type),
                ntohs(eptr->ether_type));
    }else  if (ntohs (eptr->ether_type) == ETHERTYPE_ARP)
    {
        printf("Ethernet type hex:%x dec:%d is an ARP packet\n",
                ntohs(eptr->ether_type),
                ntohs(eptr->ether_type));
    }else {
        printf("Ethernet type %x not IP\n", ntohs(eptr->ether_type));
    }
    ptr = eptr->ether_dhost;
    i = ETHER_ADDR_LEN;
    printf(" Destination Address:  ");
    do{
        printf("%s%x",(i == ETHER_ADDR_LEN) ? " " : ":",*ptr++);
    }while(--i>0);
    printf("\n");

    ptr = eptr->ether_shost;
    i = ETHER_ADDR_LEN;
    printf(" Source Address:  ");
    do{
        printf("%s%x",(i == ETHER_ADDR_LEN) ? " " : ":",*ptr++);
    }while(--i>0);
    printf("\n");
      */





      cur_counter += packet_length; 
      byte_counter += packet_length; //byte counter update 
      pkt_counter++; //increment number of packets seen 
 
    } //end internal loop for reading packets (all in one file) 
 
    pcap_close(handle);  //close the pcap file 
 
  } //end for loop through each command line argument 
  //---------- Done with Main Packet Processing Loop --------------  
 
  //output some statistics about the whole trace 
  byte_counter /= 1e6;  //convert to MB to make easier to read 
 
  printf("Processed %d packets and %u MBytes, in %d files\n", pkt_counter, byte_counter, argc-1);
  return 0; //done
}
