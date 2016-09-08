#ifndef __LINK_H__
#define __LINK_H__
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define GetNext(_this) ((_this)->next )

struct _chain
{
	struct _chain* prev;
	void* data;
	int datalen;
	struct _chain* next;
};

typedef struct _chain LinkNode;
/*    structs.h over   */

/** function.c **/
void getdata(LinkNode *node,void *data);
LinkNode* InsertBeforeNod(LinkNode *node,LinkNode *pins);
LinkNode * seeker (const LinkNode *head, const int index);
LinkNode* CreateLinkNode(void* data,int datalen);
LinkNode * SearchLink (const LinkNode *head, 
						const void* data,
						const int datalen);
LinkNode* DeleteNode(LinkNode * const nod);


#endif
