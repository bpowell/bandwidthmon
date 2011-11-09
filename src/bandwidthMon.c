#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

#include <pcap.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <net/if.h>
#include <sys/ioctl.h>
#include <netinet/ether.h>

#include <sqlite3.h>

#include "ipinfo.h"
#include "utils.h"
#include "sql.h"

static void usage() __attribute__((noreturn));
char *program_name;

static struct bandwidth_info bw_info;
static struct device_info dev_info;

/* Number of seconds to flush out SQL and PCAP Loop (in ms) */
int pcap_flush_out = 1000;
int sql_flush_out = 2000; 
static time_t oldtime;

sqlite3 *db;

void print_pkt_info(const struct pkt_info *p)
{
	fprintf(stdout, "Source IP %s\tDest IP %s\tLength %i\n",
		p->src_ip, 
		p->dst_ip,
		p->length);

	
	fprintf(stdout, "EU: %i\tED: %i\tIU: %i\tID: %i\n",
		bw_info.external_up,
		bw_info.external_down,
		bw_info.local_up,
		bw_info.local_down);
	fflush(stdout);

	return;
}

void handle_packets(unsigned char *args, const struct pcap_pkthdr *pkthdr, const unsigned char *packet)
{
	struct pkt_info pktinfo;
	struct ip *ip_info;

	unsigned int off;

	ip_info = (struct ip*)(packet + sizeof(struct ether_header));
	off = ntohs(ip_info->ip_off);

	if((off & 0x1fff)==0)
	{
		strncpy(pktinfo.src_ip, inet_ntoa(ip_info->ip_src), sizeof(pktinfo.src_ip));
		strncpy(pktinfo.dst_ip, inet_ntoa(ip_info->ip_dst), sizeof(pktinfo.dst_ip));
		pktinfo.length = pkthdr->len;

		/* Outgoing Traffic */
		if(strcmp(pktinfo.src_ip, dev_info.dev_ip)==0)
		{
			/* Local Outgoing Traffic */
			if(strncmp(pktinfo.dst_ip, dev_info.dev_network, 6)==0)
			{
				bw_info.local_up += pktinfo.length;
			}
			/* External Outgoing Traffic */
			else
			{
				bw_info.external_up += pktinfo.length;
			}
		}
		/* Incoming Traffic */
		else
		{
			/* Local Incoming Traffic */
			if(strncmp(pktinfo.src_ip, dev_info.dev_network, 6)==0)
			{
				bw_info.local_down += pktinfo.length;
			}
			/* External Incoming Traffic */
			else
			{
				bw_info.external_down += pktinfo.length;
			}
		}

		//print_pkt_info(&pktinfo);
	}

	/* Flush out bw_info to sql database */
	time_t newtime;
	time(&newtime);
	if( ((int)newtime - (int)oldtime) >= (sql_flush_out/1000) ){
		update_database(bw_info);
		time(&oldtime);
	}
}

int main(int argc, char**argv)
{
	char *device = NULL;
	char ebuf[PCAP_ERRBUF_SIZE];
	pcap_t* descr;

	bpf_u_int32 net, mask;
	struct in_addr address;

	int fd;
	struct ifreq ifr;


	opterr = 0;
	int c;

	time(&oldtime);

	bw_info.local_up = 0;
	bw_info.local_down = 0;
	bw_info.external_up = 0;
	bw_info.external_down = 0;

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

	/* SQL Setup */
	db_filename = "test_db.db";
	create_database();

	/* Get IP address information */
	if(device==NULL)
	{
		device = pcap_lookupdev(ebuf);
		if(device==NULL)
		{
			error("Cannot find a valid device.\nError: %s\n", ebuf);
		}
	}
	dev_info.dev_name = device;

	if(pcap_lookupnet(dev_info.dev_name, &net, &mask, ebuf)==-1)
	{
		error("Could not obtain network for device %s\n", dev_info.dev_name);
	}
	address.s_addr = net;
	strcpy(dev_info.dev_network, inet_ntoa(address));

	fd = socket(AF_INET, SOCK_DGRAM, 0);
	if(fd<0)
	{
		error("Unable to get IP address\n");
	}
	ifr.ifr_addr.sa_family = AF_INET;
	strncpy(ifr.ifr_name, dev_info.dev_name, IFNAMSIZ-1);
	ioctl(fd, SIOCGIFADDR, &ifr);
	strcpy(dev_info.dev_ip, inet_ntoa(((struct sockaddr_in *)&ifr.ifr_addr)->sin_addr));
	/* End IP */

	/* Open device for reading */
	descr = pcap_open_live(dev_info.dev_name, BUFSIZ, 0, 1000, ebuf);
	if(descr == NULL)
	{
		error("pcap_open_live(): %s\n", ebuf);
	}

	/* Loop that shit */
	pcap_loop(descr, -1, handle_packets, NULL);


	return 0;
}

static void usage()
{
	(void)fprintf(stderr, "Usage: %s [h]\n", program_name);
	(void)fprintf(stderr, "\t\t[ -i interface]\n");

	exit(1);
}
