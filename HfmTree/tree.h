#ifndef __2TREE_H__
#define __2TREE_H__

#include<stdio.h>
#include<malloc.h>
#include<string.h>

/*   struct(s)    */
struct _2TreeNode
{
	void* data;
	int datalen;
	struct _2TreeNode *parent;
	struct _2TreeNode *left;
	struct _2TreeNode *right;
};
typedef struct _2TreeNode TreeNode ;

struct _2Tree
{
	TreeNode* root;
};
typedef struct _2Tree BinaryTree ;
/*    structs.h over   */

/** function.c **/


#endif
