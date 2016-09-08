#include "stack.h"
#include "tree.h"
int HasData(TreeNode* n)
{
	return (n != NULL && n->data != NULL ) ;
}

void ForEachTreeNode(TreeNode* node,void (*func)(TreeNode*node))
{
	if( node == NULL )
	{
		return;
	}
	else
	{
		func(node);
		int i = 0;
		while(i< 37)
		{
			ForEachTreeNode(node->key[i++],func);
		}
	}
}

void ForEach(Trie* pt,void (*func)(TreeNode*node))
{
	ForEachTreeNode(pt->root,func);
}

TreeNode* find(Trie* pt,const char* key)
{
	TreeNode* root = pt->root;
	char tempkey='\0';
	while (root != NULL && *key != '\0' )
	{
		tempkey = *(key++);
		if( tempkey >='a' && tempkey <= 'z' )
		{
			root = root->key[(tempkey-'a')];
		}
		else if( tempkey >='A' && tempkey <= 'Z' )
		{
			root = root->key[(tempkey-'A')];
		}
		else if( tempkey >='0' && tempkey <= '9' )
		{
			root = root->key[(tempkey-'0'+27)];
		}
		else
		{
			return NULL;
		}
	}
	return root;
}

void init_trie(Trie* pt)
{
	if (pt != NULL && pt->root == NULL)
	{
		pt->root=calloc(sizeof(TreeNode),1);
	}
	return ;
}

TreeNode* insert (Trie* pt,const char* key,void* data, int datalen)
{
	if (pt == NULL || pt->root == NULL)
	{
		return NULL;
	}

	TreeNode *root= find(pt,key);
	if( root== NULL )
	{
		root = pt->root;
		TreeNode* temproot = NULL;
		char tempkey='\0';
		while (root != NULL )
		{
			temproot=root;
			tempkey = *(key++);
			if( tempkey >='a' && tempkey <= 'z' )
			{
				root = root->key[(tempkey-'a')];
			}
			else if( tempkey >='A' && tempkey <= 'Z' )
			{
				root = root->key[(tempkey-'A')];
			}
			else if( tempkey >='0' && tempkey <= '9' )
			{
				root = root->key[(tempkey-'0'+27)];
			}
			else
			{
				printf("[%s][%s]\n",key,data);
				return NULL;
			}
		}

		key--;
		root = temproot ;
		int num= 0;
		while( *key != '\0' )
		{
			tempkey = *(key++);
			if( tempkey >='a' && tempkey <= 'z' )
			{
				num = (tempkey-'a');
			}
			else if( tempkey >='A' && tempkey <= 'Z' )
			{
				num = tempkey-'A';
			}
			else if( tempkey >='0' && tempkey <= '9' )
			{
				num = tempkey-'0'+27;
			}
			else
			{
				printf("[%s][%s]\n",key,data);
				return NULL;
			}
			root->key[num]= calloc(sizeof(TreeNode),1);
			root = root->key[num];
			/**
			printf("%c[%p][%d]\n",tempkey,root,num);
			**/
		}
	}
	root->datalen=datalen;
	root->data=push(root->data,data,datalen);
	return root;
}

