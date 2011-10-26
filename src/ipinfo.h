#ifndef _IP_INOF_H_
#define _IP_INFO_H_

#include <netinet/ip.h>

struct device_info {
	char *dev_name;
	char dev_ip[sizeof(".xxx.xxx.xxx.xxx")];
	char dev_network[sizeof(".xxx.xxx.xxx.xxx")];
};

struct pkt_info {
	char src_ip[sizeof(".xxx.xxx.xxx.xxx")];
	char dst_ip[sizeof(".xxx.xxx.xxx.xxx")];
	int length;
};


#endif
