#ifndef __STACK_H__
#define __STACK_H__
/*   struct(s)    */
struct _stack
{
	void* top;
};

typedef struct _stack Stack;

Stack* push (Stack* pstack , void* data, int datalen);
int pop (Stack* pstack,void* data);
int IsEmptyStack (Stack* pstack );

#endif
