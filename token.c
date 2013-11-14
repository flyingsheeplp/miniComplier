/*************************************************************************
  * File Name: token.c
  * Author: Li Peng
  * Mail: flyingsheep.lp@gmail.com 
  * Created Time: 2013-11-06 17:08:20
  * Description:
 ************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "include/token.h"
#include "include/tag.h"

token Token(char c){
	token t = (token)malloc(sizeof(struct _token));
	t->tag = c;
	t->detail.dummy = c;
	return t;
}

token Num(int v){
	token t = (token)malloc(sizeof(struct _token));
	t->tag = NUM;
	t->detail.num = v;
	return t;
}

token Real(float x){
	token t = (token)malloc(sizeof(struct _token));
	t->tag = REAL;
	t->detail.real = x;
	return t;
}

token Word(char* lexme,int tag){
	token t = (token)malloc(sizeof(struct _token));
	t->tag = tag;
	t->detail.word = (char*)malloc(sizeof(char) * strlen(lexme) + 1);
	strcpy(t->detail.word,lexme);
	return t;
}

void print_token(token t){
	printf("TAG:%d\n",t->tag);
	if(t->tag == ID){
		printf("lexme:%s\n",t->detail.word);
	}
}


int token_equal(token t1,token t2){
	if(t1->tag != t2->tag)
		return 0;
	if(t1->tag == NUM)
		return t1->detail.num == t2->detail.num;
	if(t1->tag == REAL)
		return t1->detail.real == t2->detail.real;
	if(t1->tag == ID)
		return !strcmp(t1->detail.word,t2->detail.word);
	return t1->detail.dummy == t2->detail.dummy;
}
