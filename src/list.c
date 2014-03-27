#include <stdio.h>
#include <stdlib.h>

#include "list.h"

void append_node(struct bwmon *lnode)
{
	if(HEAD == NULL)
	{
		HEAD = lnode;
		lnode->prev = NULL;
	}
	else
	{
		TAIL->next = lnode;
		lnode->prev = TAIL;
	}

	TAIL = lnode;
	lnode->next = NULL;
}

void remove_node(struct bwmon *lnode)
{
	if(lnode->prev == NULL)
	{
		HEAD = lnode->next;
	}
	else
	{
		lnode->prev->next = lnode->next;
	}

	if(lnode->next == NULL)
	{
		TAIL = lnode->prev;
	}
	else
	{
		lnode->next->prev = lnode->prev;
	}
}

void print_nodes()
{
	struct bwmon *node;

	for(node=HEAD; node != NULL; node = node->next)
	{
		printf("%i %i/%i/%i", node->d.hour, node->d.day, node->d.month, node->d.year);
		printf("len %i type %i\n", node->p.len, node->p.type);
	}
}
