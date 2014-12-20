#include "ethernetprotocol.h"

EthernetProtocol::EthernetProtocol()
{
    InitEtherProt();
 // super com de la mort
}

void EthernetProtocol::InitEtherProt()
{
    _protocolEther[0x0800] = "IPv4";
    _protocolEther[0x0806] = "ARP";
    _protocolEther[0x0842] = "WakeonLAN[3]";
    _protocolEther[0x22F0] = "AVTProtocol";
    _protocolEther[0x22F3] = "IETF TRILL P";
    _protocolEther[0x6003] = "DECnet P-IV";
    _protocolEther[0x8035] = "Reverse ARP";
    _protocolEther[0x809B] = "AppleTalk(ET)";
    _protocolEther[0x80F3] = "AppleTalk(AARP)";
    _protocolEther[0x8100] = "VLAN-tagged-frame";
    _protocolEther[0x8137] = "IPX";
    _protocolEther[0x8138] = "IPX";
    _protocolEther[0x8204] = "QNX Qnet";
    _protocolEther[0x86DD] = "(IPv6)";
    _protocolEther[0x8808] = "EthernetFlowControl";
    _protocolEther[0x8809] = "Slow Protocols";
    _protocolEther[0x8819] = "CobraNet";
    _protocolEther[0x8847] = "MPLS unicast";
    _protocolEther[0x8848] = "MPLS multicast";
    _protocolEther[0x8863] = "PPPoE DiscoStage";
    _protocolEther[0x8864] = "PPPoE SessStage";
    _protocolEther[0x8870] = "Jumbo";
    _protocolEther[0x887B] = "HomePlug";
    _protocolEther[0x888E] = "EAP over LAN";
    _protocolEther[0x8892] = "PROFINET Prot";
    _protocolEther[0x889A] = "HyperSCSI";
    _protocolEther[0x88A2] = "ATA";
    _protocolEther[0x88A4] = "EtherCAT Prot";
    _protocolEther[0x88A8] = "Provider Bridging";
    _protocolEther[0x88AB] = "Ethernet Powerlink";
    _protocolEther[0x88CC] = "LLDP";
    _protocolEther[0x88CD] = "SERCOS III";
    _protocolEther[0x88E1] = "HomePlug AV MME";
    _protocolEther[0x88E3] = "MediaRedundancyProt";
    _protocolEther[0x88E5] = "MACsecurity";
    _protocolEther[0x88F7] = "PTP";
    _protocolEther[0x8902] = "CFM Prot";
    _protocolEther[0x8906] = "FCoE";
    _protocolEther[0x8914] = "FCoE InitProt";
    _protocolEther[0x8915] = "RDMA(RoCE)";
    _protocolEther[0x892F] = "HSR";
    _protocolEther[0x9000] = "EthernetConfTestProt";
    _protocolEther[0xCAFE] = "Veritas LLT";
}

std::string EthernetProtocol::getProtocolName(unsigned int protocolNumber)
{
    if (_protocolEther.find(protocolNumber) == _protocolEther.end())
    {
        std::cout<<"num ethernet protocol inconnu " << protocolNumber << std::endl;
        return ("Unknown : " + protocolNumber);
    }
    return (_protocolEther[protocolNumber]);
}
