#ifndef __NODE_H__
#define __NODE_H__
struct _element
{
	char chinese[5];
};

typedef struct _element Data;

#ifndef IsEmpty
#define IsEmpty(_DATA,_TYPE) IsEmpty##_TYPE(_DATA)
#endif

#endif
