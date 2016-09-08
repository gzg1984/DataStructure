#include <stdio.h>
#include <string.h>

char* sstrstr(const char* dst,const char* src)
{
	const char* tempdst=NULL;
	const char* tempsrc=NULL;

	while(1)
	{
		tempdst=dst++;
		tempsrc=src;
		if(*tempdst == '\0' )
		{
			return NULL;
		}
		while(*tempdst!='\0'&& *tempsrc != '\0')
		{
			if( *tempdst != *tempsrc )
			{
				break;
			}
			tempdst++;
			tempsrc++;
		}
		if( *tempsrc == '\0')
		{
			break;
		}
	}

	return (char* )(dst-1);
}

void mkfail(const char* src,int * fail)
{
	const int length=strlen(src);
	int j = 0,k=-1;
	fail[0]=-1;
	while( j < length) 
	{
		if( k == -1 || src[j]== src[k] )
		{
			j++; k++;
			if(src[j]==src[k] ) fail[j]=fail[k];
			else fail[j]=k;
		}
		else
		{
			k=fail[k];
		}
	}
}

char* qstrstr(const char* dst,const char* src,int* fail)
{
	int j=0,i=0,n=strlen(dst),m=strlen(src);
	while(i<n && j < m )
	{
		if(j== -1 || dst[i]==src[j])
		{
			i++;j++;
		}
		else
		{
			j=fail[j];
		}
	}

	if ( j == m )
	{
		return (char* )&dst[i-m];
	}
	else
	{
		return NULL;
	}
}
