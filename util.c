#include <pcap.h>
#include <stdlib.h>
#include "_cgo_export.h"

void wrapper_handle_packet(unsigned char *a, struct pcap_pkthdr *h, unsigned char *d) {
    handle_packet(a, h, d);
}
