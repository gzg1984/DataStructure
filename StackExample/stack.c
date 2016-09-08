#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "link.h"
#include "stack.h"
int IsEmptyStack (Stack* pstack )
{
	return IsEnd(pstack->top);
}

Stack* push (Stack* pstack , void* data, int datalen)
{
	if(pstack == NULL )
	{
		pstack=calloc(sizeof(Stack),1);
	}
	LinkNode* pins = (LinkNode *) malloc (sizeof(LinkNode));
	pins->data = malloc (datalen);
	pins->datalen = datalen;
	memcpy(pins->data,data,datalen);
	pstack->top =  InsertBeforeNod(pstack->top ,pins);
	return pstack;
}
int pop (Stack* pstack,void*data)
{
	if(pstack==NULL || pstack->top == NULL)
	{
		return 0;
	}
	LinkNode* temp= pstack->top;
	if( data != NULL )
	{
		memcpy(data,temp->data,temp->datalen);
	}
	pstack->top = GetNext(pstack->top) ;
	return DeleteNod(temp);
}
