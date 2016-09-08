#include <stdio.h>
#include <termios.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

#define UP	0xff1
#define DOWN 	0xff2
#define LEFT	0xff3
#define RIGHT	0xff4
#define NO_PRO	0xfff

int get_key( void )
{
	struct termios term, save_term;
	tcgetattr( STDIN_FILENO, &term );
	save_term = term;

	term.c_lflag &= ~ICANON;
	tcsetattr( STDIN_FILENO, TCSANOW, &term );
	
	char buf[5];

	char up[3] = { 27, 91, 65 };
	char down[3] = { 27, 91, 66 };
	char left[3] = { 27, 91, 68 };
	char right[3] = { 27, 91, 67 };
	
	int ret = read( STDIN_FILENO, buf, 3 );
	if( ret == 1 )
		return buf[0];
	else {
		if( !strncmp( up, buf, 3 ) )
			return UP;
		else if( !strncmp( down, buf, 3 ) )
			return DOWN;
		else if( !strncmp( left, buf, 3 ) )
			return LEFT;
		else if( !strncmp( right, buf, 3 ) )
			return RIGHT;		
		else
			return NO_PRO;
	}

	tcsetattr( STDIN_FILENO, TCSANOW, &save_term );
				
}

char * is_have_input( void ) 
{
	
        static char buf[1024];

        fd_set readfs;
        FD_ZERO( &readfs );
        FD_SET( 0, &readfs );
    
        struct timeval tv; 
        tv.tv_sec = 0;
        tv.tv_usec = 1;
    
        int ret = select( 1, &readfs, NULL, NULL, &tv );
        if( ret > 0 ) { 
                return buf;
        } else if( ret < 0 ) { 
                perror("select");
                return NULL;
        } else {
                return NULL;
        }
}

#include <stdio.h>
#include "data.h"
#include "link.h"
#include "stack.h"
#include "tree.h"

int insert (Trie* pt,const char* key,void* data, int datalen);
TreeNode* find(Trie* pt,const char* key);

static int num = 0;

void print(LinkNode* node)
{
    if(node != NULL )
    {
		if(num > 0 && num < 10)
		{
        	printf("[%d][%s] ",num++,((Data*)node->data)->chinese );
		}
		else if(num == 0)
		{
			printf("\r%*.*s\r",100,100," " );
        	printf("%s\n",((Data*)node->data)->chinese );
		}
		else
		{
			return ;
		}
    }
    else
    {
        printf("[NULL] " );
    }
}

int main_init(Trie* pt)
{
	char line[80]={0};
	char* data=NULL;
	char* key=NULL;

	init_trie(pt);

	FILE* fp=fopen("pinyin.txt","rb");
	while( NULL !=  fgets(line,80, fp ) )
	{
		data=strtok(line," \n");
		key=strtok(NULL," \n");
		insert (pt,key,data,strlen(data));
	}
	fclose(fp);

	return 0;
}


int main( int argc, char ** argv )
{
	struct termios term, save_term;
	tcgetattr( STDIN_FILENO, &term );
	save_term = term;
	term.c_lflag &= ~ICANON;
	tcsetattr( STDIN_FILENO, TCSANOW, &term );

	Trie trie;
	TreeNode* node=NULL;
	LinkNode* linknode=NULL;
	main_init(&trie);

	char line[80]={0};
	int linechar=0;

	while( 1 ) {
		char * flag = is_have_input();
		if( flag != NULL ) {
			int ch = get_key();
			switch(ch)
			{
				case UP :
				case DOWN :
				case LEFT :
				case RIGHT :
				case 10 :
				case ' ' :
					if(HasData(node))
					{
						num = 0 ;
						print(((Stack*)(node->data))->top);
						bzero(line,80);
						linechar=0;
						node=NULL;
					}
					continue ;
				case '' :
					if(linechar>0)
					{
						line[--linechar]='\0';
					}
					break;
				case '1' :
				case '2' :
				case '3' :
				case '4' :
				case '5' :
				case '6' :
				case '7' :
				case '8' :
				case '9' :
				case '0' :
					if(HasData(node))
					{
						linknode=seeker( ((Stack*)(node->data))->top, ch-'0' );
						num = 0 ;
						print(linknode);
						bzero(line,80);
						linechar=0;
						node=NULL;
						continue ;
					}
				default:
					if(linechar<70)
					{
						line[linechar++]=ch;
					}
			}
			/**
			if( 0 == strcmp("exit",line) )
			{
				break;
			}
			**/
			printf("\r%*.*s",100,100," " );
			printf("\rinput=[%s] ",line );
			node=find(&trie,line);
			if( HasData(node) )
			{
				num = 1 ;
				ForEachLink(((Stack*)node->data)->top,NULL,print);
			}
			fflush(NULL);
		} else {
			//printf("No input.\n" );
		}
	}	
	
	
	
	return 0;
}
