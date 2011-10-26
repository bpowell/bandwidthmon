#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <pcap.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <net/if.h>
#include <sys/ioctl.h>

#include "ipinfo.h"

static void usage() __attribute__((noreturn));
char *program_name;

int main(int argc, char**argv)
{
	char *device = NULL;
	struct device_info dev_info;
	char ebuf[PCAP_ERRBUF_SIZE];

	bpf_u_int32 net, mask;
	struct in_addr address;

	int fd;
	struct ifreq ifr;

	opterr = 0;
	int c;

	program_name = argv[0];

	while((c = getopt(argc, argv, "hi:")) != -1) 
		switch(c)
		{
			case 'h':
				usage();
				break;
			case 'i':
				device = optarg;
				break;
			default:
				break;
		}

	/* Get IP address information */
	if(device==NULL)
	{
		device = pcap_lookupdev(ebuf);
		if(device==NULL)
		{
			fprintf(stderr, "Cannot find a valid device.\nError: %s\n", ebuf);
			exit(1);
		}
	}
	dev_info.dev_name = device;

	if(pcap_lookupnet(dev_info.dev_name, &net, &mask, ebuf)==-1)
	{
		fprintf(stderr, "Could not obtain network for device %s\n", dev_info.dev_name);
		exit(1);
	}
	address.s_addr = net;
	strcpy(dev_info.dev_network, inet_ntoa(address));

	fd = socket(AF_INET, SOCK_DGRAM, 0);
	if(fd<0)
	{
		fprintf(stderr, "Unable to get IP address\n");
		exit(1);
	}
	ifr.ifr_addr.sa_family = AF_INET;
	strncpy(ifr.ifr_name, dev_info.dev_name, IFNAMSIZ-1);
	ioctl(fd, SIOCGIFADDR, &ifr);
	strcpy(dev_info.dev_ip, inet_ntoa(((struct sockaddr_in *)&ifr.ifr_addr)->sin_addr));
	/* End IP */


	return 0;
}

static void usage()
{
	(void)fprintf(stderr, "Usage: %s [h]\n", program_name);
	(void)fprintf(stderr, "\t\t[ -i interface]\n");

	exit(1);
}
