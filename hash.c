/*************************************************************************
  * File Name: hash.c
  * Author: Li Peng
  * Mail: flyingsheep.lp@gmail.com 
  * Created Time: 2013-11-07 11:26:50
  * Description:
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "include/hash.h"
#include "include/token.h"
#include "include/tag.h"

static int get_hashcode(char* str){
	int h = 0;
	while(*str){
		h = h * 31 + *str;
		str++;
	}
	return h%HASH_SIZE;
}

hashtable init_hashtable(){
	int i;
	hashtable ht = (hashtable)malloc(sizeof(entry) * HASH_SIZE);
	for(i=0;i<HASH_SIZE;i++)
		ht[i] = NULL;
	return ht;
}

token get_from_hashtable(hashtable ht,char* str){
	int h = get_hashcode(str);
	entry e = ht[h];
	while(e){
		if(!strcmp(e->t->detail.word,str))
			return e->t;
		e = e->next;
	}
	return NULL;
}

void put_in_hashtable(hashtable ht,token t){
	int h = get_hashcode(t->detail.word);
	entry e = ht[h];
	entry pe = (entry)malloc(sizeof(struct _entry));
	pe->t = t;
	pe->next = NULL;
	entry old = ht[h];
	ht[h] = pe;
	pe->next = old;
}

static void release(entry e){
	assert(e!=NULL);
	free(e->t->detail.word);
	free(e->t);
	free(e);
}

void clear_hashtable(hashtable ht){
	int i,count = 0;
	for(i=0;i<HASH_SIZE;i++){
		if(ht[i]){
			entry e = ht[i];
			while(e){
				entry te = e;
				e = e->next;
				release(te);
				count++;
			}
		}
	}
	free(ht);
	count++;
	printf("%d items released.\n",count);
}

/*
int main(){
	hashtable symbol;
	symbol = init_hashtable(&symbol);
	token t1 = Word("if",ID);
	token t2 = Word("while",ID);
	put_in_hashtable(symbol,t1);
	put_in_hashtable(symbol,t2);
	token temp = get_from_hashtable(symbol,"if");
	print_token(temp);
	temp = get_from_hashtable(symbol,"while");
	print_token(temp);
	clear_hashtable(symbol);
	return 0;
}
*/
