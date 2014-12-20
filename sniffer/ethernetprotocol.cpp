#include "ethernetprotocol.h"

EthernetProtocol::EthernetProtocol()
{
    InitEtherProt();
 // super com de la mort
}

Void EthernetProtocol::InitEtherProt()
{
    _protocolEther[0x0800] = "Internet Protocol version 4 (IPv4)";
    _protocolEther[0x0806] = "Address Resolution Protocol (ARP)";
    _protocolEther[0x0842] = "Wake-on-LAN[3]";
    _protocolEther[0x22F0] = "Audio Video Transport Protocol as defined in IEEE Std 1722-2011";
    _protocolEther[0x22F3] = "IETF TRILL Protocol";
    _protocolEther[0x6003] = "DECnet Phase IV";
    _protocolEther[0x8035] = "Reverse Address Resolution Protocol";
    _protocolEther[0x809B] = "AppleTalk (Ethertalk)";
    _protocolEther[0x80F3] = "AppleTalk Address Resolution Protocol (AARP)";
    _protocolEther[0x8100] = "VLAN-tagged frame (IEEE 802.1Q) & Shortest Path Bridging IEEE 802.1aq[4]";
    _protocolEther[0x8137] = "IPX";
    _protocolEther[0x8138] = "IPX";
    _protocolEther[0x8204] = "QNX Qnet";
    _protocolEther[0x86DD] = "Internet Protocol Version 6 (IPv6)";
    _protocolEther[0x8808] = "Ethernet flow control";
    _protocolEther[0x8809] = "Slow Protocols (IEEE 802.3)";
    _protocolEther[0x8819] = "CobraNet";
    _protocolEther[0x8847] = "MPLS unicast";
    _protocolEther[0x8848] = "MPLS multicast";
    _protocolEther[0x8863] = "PPPoE Discovery Stage";
    _protocolEther[0x8864] = "PPPoE Session Stage";
    _protocolEther[0x8870] = "Jumbo Frames[2]";
    _protocolEther[0x887B] = "HomePlug 1.0 MME";
    _protocolEther[0x888E] = "EAP over LAN (IEEE 802.1X)";
    _protocolEther[0x8892] = "PROFINET Protocol";
    _protocolEther[0x889A] = "HyperSCSI (SCSI over Ethernet)";
    _protocolEther[0x88A2] = "ATA over Ethernet";
    _protocolEther[0x88A4] = "EtherCAT Protocol";
    _protocolEther[0x88A8] = "Provider Bridging (IEEE 802.1ad) & Shortest Path Bridging IEEE 802.1aq[5]";
    _protocolEther[0x88AB] = "Ethernet Powerlink[citation needed]";
    _protocolEther[0x88CC] = "Link Layer Discovery Protocol (LLDP)";
    _protocolEther[0x88CD] = "SERCOS III";
    _protocolEther[0x88E1] = "HomePlug AV MME[citation needed]";
    _protocolEther[0x88E3] = "Media Redundancy Protocol (IEC62439-2)";
    _protocolEther[0x88E5] = "MAC security (IEEE 802.1AE)";
    _protocolEther[0x88F7] = "Precision Time Protocol (PTP) over Ethernet (IEEE 1588)";
    _protocolEther[0x8902] = "IEEE 802.1ag Connectivity Fault Management (CFM) Protocol / ITU-T Recommendation Y.1731 (OAM)";
    _protocolEther[0x8906] = "Fibre Channel over Ethernet (FCoE)";
    _protocolEther[0x8914] = "FCoE Initialization Protocol";
    _protocolEther[0x8915] = "RDMA over Converged Ethernet (RoCE)";
    _protocolEther[0x892F] = "High-availability Seamless Redundancy (HSR)";
    _protocolEther[0x9000] = "Ethernet Configuration Testing Protocol[6]";
    _protocolEther[0xCAFE] = "Veritas Low Latency Transport (LLT)[7] for Veritas Cluster Server";
}

std::string EthernetProtocol::getProtocolName(unsigned int protocolNumber)
{
    if (_protocolEther.find(protocolNumber) == _protocolEther.end())
        return ("");
    return (_protocolEther[protocolNumber]);
}
