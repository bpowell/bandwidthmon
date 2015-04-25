#include <pcap.h>
#include <stdlib.h>
#include <netinet/ether.h>
#include <netinet/ip.h>
#include "_cgo_export.h"

void wrapper_handle_packet(unsigned char *a, struct pcap_pkthdr *h, unsigned char *d) {
    struct ip *ip_info;
    ip_info = (struct ip*)(d + sizeof(struct ether_header));
    handle_packet(a, h, ip_info);
}
