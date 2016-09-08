#include "link.h"

void getdata(LinkNode* source,void* data)
{
	memcpy(data,source->data,source->datalen);
	return;
}

LinkNode* CreateLinkNode(void* data,int datalen)
{
	LinkNode* pnew= calloc(sizeof(LinkNode),1);
	pnew->datalen=datalen;
	pnew->data=malloc(datalen);
	memcpy(pnew->data,data,datalen);
	return pnew;
}

int IsEnd(const LinkNode* nod)
{
	return (nod == NULL );
}
int IsBegin(const LinkNode* nod)
{
	return (nod->prev == NULL );
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

LinkNode * SearchLink (const LinkNode *head, const void* data,const int datalen)
{
	while (head != NULL)
	{
		if(0 == memcmp(head->data,data,datalen  ))
		{
			break;
		}
		else
		{
			head= GetNext(head);
		}
	}
	return (LinkNode*)head;
}

LinkNode * seeker (const LinkNode *head, const int index)
{
	LinkNode *temp= (LinkNode*)head;
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

LinkNode* DeleteNode(LinkNode * const nod)
{
	LinkNode* temp;
	if(nod == NULL)
	{
		return NULL;
	}
	if( !IsEnd(nod->next) )
	{
		nod->next->prev = nod->prev ;
	}
	else
	{
		temp=nod->prev;
	}
	if( !IsBegin(nod) )
	{
		nod->prev->next = nod->next ;
	}
	else
	{
		temp=nod->next;
	}

	free(nod->data);
	free(nod);

	return temp;
}
