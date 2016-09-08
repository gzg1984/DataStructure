#ifndef __CHAINBOX_H__
#define __CHAINBOX_H__

#include<stdio.h>
#include<malloc.h>
#include<string.h>

/*   struct(s)    */
struct _TrieTreeNode
{
	struct _TrieTreeNode * key[37];
	void* data;
	int datalen;
};
typedef struct _TrieTreeNode TreeNode ;

struct _TrieTree
{
	TreeNode* root;
};
typedef struct _TrieTree Trie ;
/*    structs.h over   */

/** function.c **/


#endif
