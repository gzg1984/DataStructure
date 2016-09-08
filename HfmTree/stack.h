#ifndef __STACK_H__
#define __STACK_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "link.h"

/** 栈必然由链表构成，但栈不应该关心链表的节点属性**/
/** 栈的各项操作应该可以用链表向上提供的函数完成，而不必了解链表的实现细节**/
/** 链表的实现细节，例如单链表或者双链表或者链表节点的附加数据，对于栈而言应该是透明的 **/
/** 链表的各项操作函数，对于栈的实现而言，应该是可见的，可随意使用的，是其继承的数据结构的一部分 **/
/** 但栈始终是构建在链表之上的，所以其应该可以使用节点的类型名称 **/


/*   struct(s)    */
struct _stack
{
	LinkNode* top;
};

typedef struct _stack Stack;
#define  GetTop(_this) ((_this)->top)

void InitStack (Stack* const pstack );
Stack* push (Stack* pstack , void* data, int datalen);
int pop (Stack* pstack,void* data);
int IsEmptyStack (Stack* pstack );

#endif
