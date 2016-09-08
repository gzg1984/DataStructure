#include <stdio.h>
#include "link.h"

int IsEnd(const LinkNode* nod)
{
	return (nod == NULL );
}
int IsBegin(const LinkNode* nod)
{
	return (nod->prev == NULL );
}

LinkNode* GetNext(LinkNode* this)
{
	return this->next;
}

LinkNode* GetPrev(LinkNode* this)
{
	return this->prev;
}
int ForEachLink (LinkNode *begin,LinkNode* end,void (*func)( LinkNode* ) )
{
	int i = 0;
	while ( begin != end  )
	{
		func(begin);
		begin=GetNext(begin);
		++i ;
	}
	return i;
}

LinkNode * seeker (LinkNode *head, const int index)
{
	LinkNode *temp= head;
	int i = 1;
	for (i = 1; i < index ; i++)
	{
		if( temp == NULL )
		{
		    break;
		}
		temp=temp->next;
	}

	if( temp == NULL || i != index )
	{
		return NULL;
	}
	else
	{
		return temp;
	}
}

LinkNode* InsertBeforeNod(LinkNode *nod,LinkNode *pins)
{
	if( pins == NULL )
	{
		return NULL;
	}
	if( nod == NULL )
	{
		pins->next=NULL;
		pins->prev=NULL;
	}
	else
	{
		pins->next=nod;
		pins->prev=nod->prev;
		pins->next->prev=pins;
		if( ! IsBegin(pins) )
		{
			pins->prev->next=pins;
		}
	}
	return pins;
}

int DeleteNod(LinkNode * const nod)
{
	if(nod == NULL)
	{
		return -1;
	}
	if( !IsEnd(nod->next) )
	{
		nod->next->prev = nod->prev ;
	}
	if( !IsBegin(nod) )
	{
		nod->prev->next = nod->next ;
	}

	free(nod->data);
	free(nod);

	return 0;
}
