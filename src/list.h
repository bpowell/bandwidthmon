#ifndef _MY_DLL_H_
#define _MY_DLL_H_

struct date
{
	int hour, day, month, year;
};

/* TYPE: type of packet
 * 1. local up
 * 2. local down
 * 3. external up
 * 4. external down
 */
struct pkt
{
	int len;
	int type;
};

struct bwmon
{
	struct date d;
	struct pkt p;
	struct bwmon *next;
	struct bwmon *prev;
};

struct bwmon *HEAD, *TAIL;

void append_node(struct bwmon *lnode);
void remove_node(struct bwmon *lnode);
void print_nodes();

#endif
