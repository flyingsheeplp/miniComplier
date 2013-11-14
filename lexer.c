/*************************************************************************
  * File Name: token_parser.c
  * Author: Li Peng
  * Mail: flyingsheep.lp@gmail.com 
  * Created Time: 2013-11-06 14:33:02
  * Description:
 ************************************************************************/

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "include/tag.h"
#include "include/lex.h"
#include "include/token.h"
#include "include/hash.h"
#include "include/global.h"

#define MAX_LEN 50

extern token and,or,eq,ne,le,ge,minus,True,False,temp;


char peek = ' ';
int line = 1;
static char lexme[MAX_LEN] = {0};

void next_char(){
	peek = fgetc(stdin);
	if(peek == EOF)
		exit(2);
}

int next_c(char c){
	next_char();
	if(peek != c)
		return 0;
	return 1;
}

token get_token(){
	int index = 0;
	for(;;next_char()){
		if(peek == ' ' || peek == '\t')
			continue;
		else if(peek == '\n')
			line = line + 1;
		else break;
	}
	switch(peek){
		case '&':
			if(next_c('&')) return and; else return Token('&');
		case '|':
			if(next_c('|')) return or; else return Token('|');
		case '=':
			if(next_c('=')) return eq; else return Token('=');
		case '!':
			if(next_c('=')) return ne; else return Token('!');
		case '<':
			if(next_c('=')) return le; else return Token('<');
		case '>':
			if(next_c('=')) return ge; else return Token('>');
	}
	if(isdigit(peek)){
		int v = 0;
		do{
			v = v*10 + (peek-'0');
			next_char();
		}while(isdigit(peek));
		if(peek != '.') return Num(v);
		float x = v; float d = 10;
		for(;;){
			next_char();
			if(!isdigit(peek)) break;
			x = x + (peek-'0')/d;
			d = d * 10;
		}
		return Real(x);
	}
	if(isalpha(peek)){
		index = 0;
		memset(lexme,0,MAX_LEN);
		do{
			lexme[index++] = peek;
			next_char();
		}while(isalpha(peek) || isdigit(peek));
		token t = get_from_hashtable(symbol,lexme);
		if(t != NULL)
			return t;
		if(!strcmp(lexme,"int")){
			return TYPE_INT;
		}
		if(!strcmp(lexme,"float")) 
			return TYPE_FLOAT;
		if(!strcmp(lexme,"char")) 
			return TYPE_CHAR;
		t = Word(lexme,ID);
		put_in_hashtable(symbol,t);
		return t;
	}
	token tok = Token(peek);
	peek = ' ' ;
	return tok;
}
