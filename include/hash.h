/*************************************************************************
  * File Name: hash.h
  * Author: Li Peng
  * Mail: flyingsheep.lp@gmail.com 
  * Created Time: 2013-11-07 11:50:42
  * Description:
 ************************************************************************/
#include "token.h"
#ifndef _HASH_H_
#define _HASH_H_

#define HASH_SIZE 131

struct _entry{
	token t;
	struct _entry* next;
};

typedef struct _entry* entry;

typedef entry* hashtable;

hashtable init_hashtable();
token get_from_hashtable(hashtable,char*);
void put_in_hashtable(hashtable,token);
void clear_hashtable(hashtable);


#endif
