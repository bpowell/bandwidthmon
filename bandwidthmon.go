package main

/*
#cgo LDFLAGS: -lpcap
#include <pcap.h>
#include <stdlib.h>
void wrapper_handle_packet(unsigned char *a, struct pcap_pkthdr *h, unsigned char *d);
typedef void (*voidFunc) ();
*/
import "C"

import (
	"fmt"
	"os"
)

//export handle_packet
func handle_packet(args *C.uchar, header *C.struct_pcap_pkthdr, data *C.uchar) {
	fmt.Println("here")
}

func main() {
	ebuf := (*C.char)(C.calloc(256, 1))
	device := C.pcap_lookupdev(ebuf)
	if C.GoString(ebuf) != "" {
		fmt.Println("Error opening device: ", C.GoString(ebuf))
		os.Exit(1)
	}

	live := C.pcap_open_live(device, C.int(1024), 0, 1000, ebuf)
	if live == nil {
		fmt.Println("Error opening device: ", C.GoString(ebuf))
		os.Exit(1)
	}

	callback := C.voidFunc(C.wrapper_handle_packet)
	C.pcap_loop(live, -1, callback, nil)
}
