#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef int NodData;

struct nod
{
	NodData data;
	struct nod* pnext;
};

typedef struct nod Nod;
typedef Nod* PNod;
typedef const Nod* CPNod;

int IsEnd(const CPNod p)
{
	return (p->pnext == NULL );
}

NodData GetData(const CPNod p)
{
	return (p->data );
}
char* GetDataFmt()
{
	static char* s="%d";
	return s;
}

PNod GetNext(const CPNod p)
{
	return (p->pnext );
}

NodData PutData(const PNod p,NodData data)
{
	return (p->data=data );
}

PNod PutNext(const PNod p,PNod next)
{
	return (p->pnext=next );
}
PNod MakeNod()
{
	return calloc(1,sizeof(Nod));
}

int main(int argc,char** argv)
{
    char line[1024]={0};
    char prs[1024]={0};
	PNod head = NULL;
	PNod current = NULL;
	PNod pn = NULL;

	while( 0 < fgets(line,1024,stdin) )
	{
	    pn=MakeNod();
		PutData(pn,strlen(line)) ;
		PutNext(pn, NULL ) ;

		if(head == NULL)
		{
		    head = pn ;
			continue;
		}
		else
		{
		    current = head ;
		    while( ! IsEnd( current ) )
			{
				current=GetNext(current);
			}
		    PutNext(current , pn ) ;
		}
		
	}

	printf("\n=========================\n");

	current = head ;
	while( current != NULL )
	{
	    sprintf(prs,"%s\n",GetDataFmt() );
	    printf( prs ,GetData(current));
		current=GetNext(current);
	}
	printf("\n=========================\n");
}
