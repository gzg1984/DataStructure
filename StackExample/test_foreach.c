#include <stdio.h>
#include "data.h"
#include "link.h"
#include "stack.h"
#include "tree.h"

int insert (Trie* pt,const char* key,void* data, int datalen);
TreeNode* find(Trie* pt,const char* key);

void print(LinkNode* node)
{
	if(node != NULL )
	{
		printf("data=[%s]\n",((Data*)node->data)->chinese );
	}
	else
	{
		printf("LinkNode=[NULL]\n" );
	}
}
void print_node(TreeNode* node)
{
	printf("node=[%p]\n",node );
	if(node != NULL )
	{
		if(node->data != NULL)
		{
			ForEachLink(((Stack*)node->data)->top,NULL,print);
		}
		else
		{
			printf("data=[NULL]\n" );
		}
	}
	else
	{
		printf("TreeNode=[NULL]\n" );
	}
	return;
}

int main(int argc,char** argv)
{
	char line[80]={0};
	char* data=NULL;
	char* key=NULL;
	int datalen=0;
	Trie pt;
	init_trie(&pt);

	FILE* fp=fopen("pinyin.txt","rb");
	while( 0 < fgets(line,80, fp ) )
	{
		data=strtok(line," \n");
		datalen=strlen(data);
		key=strtok(NULL," \n");
		insert (&pt,key,data,datalen);
	}

	ForEach(&pt,print_node );
	return 0;
}

