/*************************************************************************
  * File Name: token.h
  * Author: Li Peng
  * Mail: flyingsheep.lp@gmail.com 
  * Created Time: 2013-11-06 16:29:46
  * Description:
 ************************************************************************/

#ifndef _TOKEN_H_
#define _TOKEN_H_

struct _token{
	int tag;
	union{
		int num;
		float real;
		char* word;
		char dummy;
		struct {char* name;int width;} type;
	}detail;
};

typedef struct _token* token;
typedef struct _token* var_type;

token Token(char c);
token Num(int v);
token Real(float x);
token Word(char* lexme,int tag);
var_type Type(char* lexme,int tag,int w);
var_type max(var_type p1,var_type p2);
int token_equal(token t1,token t2);
void print_token(token t);
token scan();


#endif
