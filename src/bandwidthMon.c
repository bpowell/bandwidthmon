#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

static void usage() __attribute__((noreturn));
char *program_name;

int main(int argc, char**argv)
{
	char *device;

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


	return 0;
}

static void usage()
{
	(void)fprintf(stderr, "Usage: %s [h]\n", program_name);
	(void)fprintf(stderr, "\t\t[ -i interface]\n");

	exit(1);
}
