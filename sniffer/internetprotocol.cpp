#include "internetprotocol.h"

InternetProtocol::InternetProtocol()
{
    initProtoIPV4();
    initProtoIPV6();
}

void InternetProtocol::initProtoIPV4()
{
    _protocolNumbersv4[0] = "HOPOPT";
    _protocolNumbersv4[1] = "ICMP";
    _protocolNumbersv4[2] = "IGMP";
    _protocolNumbersv4[3] = "GGP";
    _protocolNumbersv4[4] = "IPv4";
    _protocolNumbersv4[5] = "ST";
    _protocolNumbersv4[6] = "TCP";
    _protocolNumbersv4[7] = "CBT";
    _protocolNumbersv4[8] = "EGP";
    _protocolNumbersv4[9] = "IGP";
    _protocolNumbersv4[10] = "BBN-RCC-MON";
    _protocolNumbersv4[11] = "NVP-II";
    _protocolNumbersv4[12] = "PUP";
    _protocolNumbersv4[13] = "ARGUS";
    _protocolNumbersv4[14] = "EMCON";
    _protocolNumbersv4[15] = "XNET";
    _protocolNumbersv4[16] = "CHAOS";
    _protocolNumbersv4[17] = "UDP";
    _protocolNumbersv4[18] = "MUX";
    _protocolNumbersv4[19] = "DCN-MEAS";
    _protocolNumbersv4[20] = "HMP";
    _protocolNumbersv4[21] = "PRM";
    _protocolNumbersv4[22] = "XNS-IDP";
    _protocolNumbersv4[23] = "TRUNK-1";
    _protocolNumbersv4[24] = "TRUNK-2";
    _protocolNumbersv4[25] = "LEAF-1";
    _protocolNumbersv4[26] = "LEAF-2";
    _protocolNumbersv4[27] = "RDP";
    _protocolNumbersv4[28] = "IRTP";
    _protocolNumbersv4[29] = "ISO-TP4";
    _protocolNumbersv4[30] = "NETBLT";
    _protocolNumbersv4[31] = "MFE-NSP";
    _protocolNumbersv4[32] = "MERIT-INP";
    _protocolNumbersv4[33] = "DCCP";
    _protocolNumbersv4[34] = "3PC";
    _protocolNumbersv4[35] = "IDPR";
    _protocolNumbersv4[36] = "XTP";
    _protocolNumbersv4[37] = "DDP";
    _protocolNumbersv4[38] = "IDPR-CMTP";
    _protocolNumbersv4[39] = "TP++";
    _protocolNumbersv4[40] = "IL";
    _protocolNumbersv4[41] = "IPv6";
    _protocolNumbersv4[42] = "SDRP";
    _protocolNumbersv4[43] = "IPv6-Route";
    _protocolNumbersv4[44] = "IPv6-Frag";
    _protocolNumbersv4[45] = "IDRP";
    _protocolNumbersv4[46] = "RSVP";
    _protocolNumbersv4[47] = "GRE";
    _protocolNumbersv4[48] = "DSR";
    _protocolNumbersv4[49] = "BNA";
    _protocolNumbersv4[50] = "ESP";
    _protocolNumbersv4[51] = "AH";
    _protocolNumbersv4[52] = "I-NLSP";
    _protocolNumbersv4[53] = "SWIPE";
    _protocolNumbersv4[54] = "NARP";
    _protocolNumbersv4[55] = "MOBILE";
    _protocolNumbersv4[56] = "TLSP";
    _protocolNumbersv4[57] = "SKIP";
    _protocolNumbersv4[58] = "IPv6-ICMP";
    _protocolNumbersv4[59] = "IPv6-NoNxt";
    _protocolNumbersv4[60] = "IPv6-Opts";
    _protocolNumbersv4[61] = "";
    _protocolNumbersv4[62] = "CFTP";
    _protocolNumbersv4[63] = "";
    _protocolNumbersv4[64] = "SAT-EXPAK";
    _protocolNumbersv4[65] = "KRYPTOLAN";
    _protocolNumbersv4[66] = "RVD";
    _protocolNumbersv4[67] = "IPPC";
    _protocolNumbersv4[68] = "";
    _protocolNumbersv4[69] = "SAT-MON";
    _protocolNumbersv4[70] = "VISA";
    _protocolNumbersv4[71] = "IPCV";
    _protocolNumbersv4[72] = "CPNX";
    _protocolNumbersv4[73] = "CPHB";
    _protocolNumbersv4[74] = "WSN";
    _protocolNumbersv4[75] = "PVP";
    _protocolNumbersv4[76] = "BR-SAT-MON";
    _protocolNumbersv4[77] = "SUN-ND";
    _protocolNumbersv4[78] = "WB-MON";
    _protocolNumbersv4[79] = "WB-EXPAK";
    _protocolNumbersv4[80] = "ISO-IP";
    _protocolNumbersv4[81] = "VMTP";
    _protocolNumbersv4[82] = "SECURE-VMTP";
    _protocolNumbersv4[83] = "VINES";
    _protocolNumbersv4[84] = "TTP";
    _protocolNumbersv4[84] = "IPTM";
    _protocolNumbersv4[85] = "NSFNET-IGP";
    _protocolNumbersv4[86] = "DGP";
    _protocolNumbersv4[87] = "TCF";
    _protocolNumbersv4[88] = "EIGRP";
    _protocolNumbersv4[89] = "OSPFIGP";
    _protocolNumbersv4[90] = "Sprite-RPC";
    _protocolNumbersv4[91] = "LARP";
    _protocolNumbersv4[92] = "MTP";
    _protocolNumbersv4[93] = "AX.25";
    _protocolNumbersv4[94] = "IPIP";
    _protocolNumbersv4[95] = "MICP";
    _protocolNumbersv4[96] = "SCC-SP";
    _protocolNumbersv4[97] = "ETHERIP";
    _protocolNumbersv4[98] = "ENCAP";
    _protocolNumbersv4[99] = "";
    _protocolNumbersv4[100] = "GMTP";
    _protocolNumbersv4[101] = "IFMP";
    _protocolNumbersv4[102] = "PNNI";
    _protocolNumbersv4[103] = "PIM";
    _protocolNumbersv4[104] = "ARIS";
    _protocolNumbersv4[105] = "SCPS";
    _protocolNumbersv4[106] = "QNX";
    _protocolNumbersv4[107] = "A/N";
    _protocolNumbersv4[108] = "IPComp";
    _protocolNumbersv4[109] = "SNP";
    _protocolNumbersv4[110] = "Compaq-Peer";
    _protocolNumbersv4[111] = "IPX-in-IP";
    _protocolNumbersv4[112] = "VRRP";
    _protocolNumbersv4[113] = "PGM";
    _protocolNumbersv4[114] = "";
    _protocolNumbersv4[115] = "L2TP";
    _protocolNumbersv4[116] = "DDX";
    _protocolNumbersv4[117] = "IATP";
    _protocolNumbersv4[118] = "STP";
    _protocolNumbersv4[119] = "SRP";
    _protocolNumbersv4[120] = "UTI";
    _protocolNumbersv4[121] = "SMP";
    _protocolNumbersv4[122] = "SM";
    _protocolNumbersv4[123] = "PTP";
    _protocolNumbersv4[124] = "ISIS over IPv4";
    _protocolNumbersv4[125] = "FIRE";
    _protocolNumbersv4[126] = "CRTP";
    _protocolNumbersv4[127] = "CRUDP";
    _protocolNumbersv4[128] = "SSCOPMCE";
    _protocolNumbersv4[129] = "IPLT";
    _protocolNumbersv4[130] = "SPS";
    _protocolNumbersv4[131] = "PIPE";
    _protocolNumbersv4[132] = "SCTP";
    _protocolNumbersv4[133] = "FC";
    _protocolNumbersv4[134] = "RSVP-E2E-IGNORE";
    _protocolNumbersv4[135] = "Mobility Header";
    _protocolNumbersv4[136] = "UDPLite";
    _protocolNumbersv4[137] = "MPLS-in-IP";
    _protocolNumbersv4[138] = "manet";
    _protocolNumbersv4[139] = "HIP";
    _protocolNumbersv4[140] = "Shim6";
    _protocolNumbersv4[141] = "WESP";
    _protocolNumbersv4[142] = "ROHC";
}

void InternetProtocol::initProtoIPV6()
{

}

std::string InternetProtocol::getProtocolName(unsigned char protocolNumber)
{
    if (protocolNumber <= 142)
        return (_protocolNumbersv4[protocolNumber]);
    return ("");
}
