#ifndef __LINK_H__
#define __LINK_H__

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
LinkNode* InsertBeforeNod(LinkNode *node,LinkNode *pins);
LinkNode* GetNext(LinkNode* this);
LinkNode * seeker (LinkNode *head, const int index);


#endif
