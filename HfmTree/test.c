#include <stdio.h>
#include "link.h"
#include "stack.h"

enum
{
	LEFT=0,
	RIGHT,
	ROOT,
};
struct _HfmTreeNode
{
	int weight;
	char data;
	struct _2TreeNode *parent;
	struct _2TreeNode *left;
	struct _2TreeNode *right;
};
typedef struct _HfmTreeNode TreeNode ;

struct _HfmTree
{
	TreeNode* root;
};
typedef struct _Tree HfmTree ;


void get_little2(LinkNode* head,LinkNode** little1,LinkNode** little2)
{
	TreeNode* pd1;
	TreeNode* pd2;
	LinkNode* temp;
	if(head == NULL || GetNext(head)  == NULL )
	{
		return;
	}
	else
	{
		*little1=head;
		*little2=GetNext(head);
		pd1=*((TreeNode**)((*little1)->data));
		pd2=*((TreeNode**)((*little2)->data));
		if (pd1->weight >= pd2->weight)
		{
			temp= *little1;
			*little1 = *little2;
			*little2 = temp;
			pd1=*((TreeNode**)((*little1)->data));
			pd2=*((TreeNode**)((*little2)->data));
		}
	}
	/** ldata1 始终比 ldata2 小 **/
	temp= GetNext(head);
	if (GetNext(temp) == NULL)
	{
		return ;
	}
	else
	{
		temp= GetNext(temp) ;
		TreeNode* pdata=NULL;
		while( !IsEnd(temp) )
		{
			pdata=*((TreeNode**)(temp->data));
			if (pdata-> weight <= pd1->weight )
			{
				(*little2)= (*little1);
				pd2=pd1;
				(*little1)=temp;
				pd1=pdata;
			}
			else if (pdata-> weight <= pd2->weight )
			{
				(*little2)= temp;
				pd2=pdata;
			}
			temp=temp->next;
		}
	}
	return;
}

char* get_code(TreeNode* root,int lr,char c,char*s )
{
	int prevlen=strlen(s);
	char local[80]={0};
	strcpy(local,s);
	if( lr == LEFT )
	{
		local[prevlen]='0'+0;
	}
	else if( lr == RIGHT )
	{
		local[prevlen]='0'+1;
	}
	else
	{
		/** next step **/
	}

	if(root->left == NULL && root->right == NULL )
	{
		if (((Data*)(root->data))->data == c  )
		{
			strcpy(s,local);
			return s;
		}
		else
		{
			return NULL;
		}
	}
	else
	{
		if (NULL !=get_code(root->left,LEFT,c,local))
		{
			strcpy(s,local);
			return s;
		}
		if (NULL != get_code(root->right,RIGHT,c,local) )
		{
			strcpy(s,local);
			return s;
		}
	}
	return NULL;
}

TreeNode* get_char( TreeNode* temp , char c )
{
	if (c == '0' )
	{
		return temp->left;
	}
	else
	{
		return temp->right;
	}
}

char* put_code(TreeNode* root,char* prev,int lr,FILE* fpout)
{
	int prevlen=0;
	if(prev != NULL )
	{
		prevlen=strlen(prev);
	}
	char* result=calloc(sizeof(char),prevlen+1+1);
	if(lr != ROOT && prev != NULL)
	{
		strcpy(result,prev);
	}
	if( lr == LEFT )
	{
		result[prevlen]='0'+0;
	}
	else if( lr == RIGHT )
	{
		result[prevlen]='0'+1;
	}
	else
	{
		/** next step **/
	}

	if(root == NULL )
	{
		return NULL;
	}

	if(root->left == NULL && root->right == NULL)
	{
		fprintf(fpout,"%s %c",result,((Data*)(root->data))->data);
	}
	else
	{
		put_code(root->left,result,LEFT,fpout);
		put_code(root->right,result,RIGHT,fpout);
	}
	return result;
}
/**************** tar kernel **************/
enum
{
	SOURCEFILE=0,
	CODE
};

BinaryTree* create_tree(BinaryTree* ptree,FILE* fp,const int mode)
{
	bzero(ptree,sizeof(BinaryTree ));
	Stack temphfm;
	TreeNode* pdata;
	InitStack(&temphfm );

	if (mode == SOURCEFILE )
	{
		unsigned int weight[256]={0};
		unsigned char c = 0;
		while( 1 == fread(&c ,1,1, fp )  )
		{
			++(weight[c]);
		}

		for( c=0; c<=255 ; ++c )
		{
			if(weight[c] == 0 )
			{
				continue;
			}
			pdata=calloc(sizeof(TreeNode),1);
			pdata->data=c;
			pdata->weight=weight[c];
			push(&temphfm,&pdata,sizeof(TreeNode*));
		}

	}
	else
	{
		int total = 0;
		if( 4 !=  fread(&total,sizeof(int),1, fp ) )
		{
			return NULL;
		}

		int i = 0;
		for( i=0; i < total ; ++i )
		{
			pdata=calloc(sizeof(TreeNode),1);
			if( 5 !=  fread(pdata,5,1, fp ) )
			{
				return NULL;
			}
			push(&temphfm,&pdata,sizeof(TreeNode*));
		}
	}

	LinkNode *little1;
	LinkNode *little2;
	TreeNode* pd1=NULL;
	TreeNode* pd2=NULL;
	while( !IsEnd(GetNext(GetTop(&temphfm))) )
	{
		get_little2(GetTop(&temphfm),&little1,&little2);
		pd1=*((TreeNode**)(little1->data));
		pd2=*((TreeNode**)(little2->data));
		pdata=calloc(sizeof(TreeNode),1);
		pdata->data='\0';
		pdata->weight= pd1->weight + pd2->weight;
		pdata->left= pd1;
		pdata->left->parent= pdata;
		pdata->right= pd2;
		pdata->right->parent= pdata;
		push(&temphfm,&pdata,sizeof(TreeNode*));
		DeleteNode(little1);
		DeleteNode(little2);
	}

	ptree->root=*((TreeNode**)(GetTop(&temphfm)->data));
	return ptree;
}
int untarer(FILE* fpin,FILE* fpout)
{
	BinaryTree tree;
	char c;
	char bit;
	int num = 0;
	create_tree(&tree,fpin,CODE);

	/**
	put_code(tree.root,NULL,ROOT,stdout);
	printf("\nxxxxxxxxxxxxxx\n");
	**/
	TreeNode* hfm= tree.root;
	while( 1 == fread( &c,1,1,fpin ) ) 
	{
		num = 8;
		while(num--) 
		{
			bit= '0' + ((c >> num) & (unsigned char)1);
			hfm= get_char( hfm , bit );
			if (hfm->left == NULL && hfm->right == NULL)
			{
				fputc(((Data*)(hfm->data))->data,fpout);
				hfm=tree.root;
			}
		}
	}
	return 0;
}

/** put tree in tar file head **/
int tarer(FILE* fpin,FILE* fpout)
{
	BinaryTree tree;
	create_tree(&tree,fpin,SOURCEFILE );
	put_code(tree.root,NULL,ROOT,fpout);
	fputc(0,fpout);

	char c=0;
	char byte=0;
	int total=0;
	unsigned char byte=0;
	rewind(fpin);
	while( 1 == fread(&c,1,1,fpin ) ) 
	{
		get_code(tree.root,ROOT,c,fpout);
		for(bitnum =0 ; s[bitnum] != '\0' ;bitnum ++,total++)
		{
			byte<<=1;
			if (s[bitnum] == '0' )
			{
				/** next step **/
			}
			else
			{
				byte |= (unsigned char)1;
			}
			if(total%8 == 7 )
			{
				fputc(byte,fpout);
				byte=0;
			}
		}
	}
	if( total&7 !=7 )
	{
		for(;total&7 !=7 ; total++)
		{
			byte<<=1;
		}
		fputc(byte,fpout);
	}

	return 0;
}
/****************************************/
enum
{
	NORMAL=0,
	TAR,
	EX
};
extern char *optarg;
int main(int argc,char** argv)
{
	int mode = NORMAL;
	char targetfile[80]={0};
	char sourcefile[80]={0};
	int opt = 0; 
	while( -1 != (opt=getopt(argc,argv,"hx:c:s:") ))
	{
		switch (opt)
		{
			case 's':
				strncpy(sourcefile,optarg,80);
				break;
			case 'c':
				strncpy(targetfile,optarg,80);
				mode=TAR;
				break;
			case 'x':
				strncpy(targetfile,optarg,80);
				mode=EX;
				break;
			case 'h':
			case '?':
			case ':':
				printf("Usage:%s [s sourcefile][c targetfile] [x targetfile] ...\n",
						basename(argv[0]));
				return;
		}
	}

	if (mode == NORMAL )
	{
		strncpy(sourcefile,argv[1],80);
	}
	else if(mode == TAR)
	{
		if ( 0 == strlen(sourcefile))
		{
			printf("Usage:%s [s sourcefile][c targetfile] \n",
					basename(argv[0]));
			return;
		}
	}

	if (mode == NORMAL || mode == TAR )
	{
		FILE* fpin;
		FILE* fpout;
		if( NULL == (fpin=fopen(sourcefile,"rb"))  )
		{
			return -1;
		}
		if ( mode == TAR )
		{
			if( NULL == (fpout=fopen(targetfile,"wb+"))  )
			{
				return -1;
			}
		}
		else
		{
			fpout= stdout;
		}
		tarer(fpin,fpout);
		fclose(fpin);
		fclose(fpout);
		return 0;
	}
	else
	{
		FILE* fpin;
		if( NULL == (fpin=fopen(targetfile,"rb"))  )
		{
			return -1;
		}
		untarer(fpin,stdout);
		fclose(fpin);
		return 0;
	}
}

