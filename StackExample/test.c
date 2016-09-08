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

int main(int argc,char** argv)
{
	if( argc > 3 || argc < 2 )
	{
		return 0;
	}
	char line[80]={0};
	char* data=NULL;
	char* key=NULL;

	Trie pt;
	init_trie(&pt);

	FILE* fp=fopen("pinyin.txt","rb");
	while( NULL != fgets(line,80, fp ) )
	{
		data=strtok(line," \n");
		key=strtok(NULL," \n");
		insert (&pt,key,data,strlen(data));
	}

	TreeNode* node=find(&pt,argv[1]);
	if( HasData(node) )
	{
		ForEachLink(((Stack*)node->data)->top,NULL,print);
	}
	return 0;
}

