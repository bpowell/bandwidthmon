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
