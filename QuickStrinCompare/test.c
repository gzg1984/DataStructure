#include <stdio.h>
#include <string.h>

char* sstrstr(const char* dst,const char* src);
char* qstrstr(const char* dst,const char* src,int* fail);
void mkfail(const char* src,int * fail);

int main(int argc,char** argv)
{
	int i = 0;
	char*c =NULL;
	char a[]="asdfasdfasdfasdfasldfkjasl;kdjsnkvioeharkneknvoaivdfnsjkgnsdkofjnvgdsiofjbndsofbnsdbgfksnbgfkopsnbl;nhcvbkxcbvklnxcvkl;bnxcl;vkbxl;vkbnxcl;vkbxcl;vkbjxcl;vkbjxc";
	char b[]="fjnvgdsiofjbndsofbnsdbgfksnbgfkopsnbl";
	const int length=strlen(b);
	int fail[length];
	mkfail(b,fail);
	while((i++)< 1000000)
	{
		c =  strstr(a,b);
		//c =  sstrstr(a,b);
		//c =  qstrstr(a,b,fail);
	}
	printf("%s\n",c);
	return 0;
}

