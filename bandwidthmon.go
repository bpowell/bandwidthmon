package main

/*
#cgo LDFLAGS: -lpcap
#include <pcap.h>
#include <stdlib.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
void wrapper_handle_packet(unsigned char *a, struct pcap_pkthdr *h, unsigned char *d);
typedef void (*voidFunc) ();
*/
import "C"

import (
	"errors"
	"fmt"
	"net"
	"os"
)

//export handle_packet
func handle_packet(args *C.uchar, header *C.struct_pcap_pkthdr, data *C.struct_ip) {
	src_ip := C.GoString(C.inet_ntoa(data.ip_src))
	dst_ip := C.GoString(C.inet_ntoa(data.ip_dst))
	length := int(header.len)

	fmt.Println(src_ip, " ", dst_ip, " ", length)
}

func getIP() (string, error) {
	ifaces, err := net.Interfaces()
	if err != nil {
		return "", err
	}
	for _, iface := range ifaces {
		if iface.Flags&net.FlagUp == 0 {
			continue
		}
		if iface.Flags&net.FlagLoopback != 0 {
			continue
		}
		addrs, err := iface.Addrs()
		if err != nil {
			return "", err
		}
		for _, addr := range addrs {
			var ip net.IP
			switch v := addr.(type) {
			case *net.IPNet:
				ip = v.IP
			case *net.IPAddr:
				ip = v.IP
			}
			if ip == nil || ip.IsLoopback() {
				continue
			}
			ip = ip.To4()
			if ip == nil {
				continue
			}
			return ip.String(), nil
		}
	}
	return "", errors.New("are you connected to the network?")
}

func main() {
	ip, _ := getIP()
	fmt.Println(ip)

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
