#include "stack.h"

int IsEmptyStack (Stack* pstack )
{
	return IsEnd(pstack->top);
}

void InitStack (Stack* const pstack )
{
	pstack->top = NULL;
	return;
}

Stack* push (Stack* pstack , void* data, int datalen)
{
	if(pstack == NULL )
	{
		pstack=calloc(sizeof(Stack),1);
	}
	LinkNode* pins = CreateLinkNode(data,datalen);
	pstack->top =  InsertBeforeNod(pstack->top ,pins);
	return pstack;
}
int pop (Stack* pstack,void*data)
{
	if(pstack==NULL || pstack->top == NULL)
	{
		return 0;
	}
	LinkNode * temp= pstack->top;
	if( data != NULL )
	{
		getdata(temp,data);
	}
	pstack->top = GetNext(pstack->top) ;
	DeleteNode(temp);
	return 0;
}
