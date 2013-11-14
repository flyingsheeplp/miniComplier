/*************************************************************************
  * File Name: parser.c
  * Author: Li Peng
  * Mail: flyingsheep.lp@gmail.com 
  * Created Time: 2013-11-07 16:12:31
  * Description: recursive descent parser 
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "include/env.h"
#include "include/token.h"
#include "include/lex.h"
#include "include/tag.h"
#include "include/global.h"

static token look;
static enviroment top = NULL;
static int used = 0;
static int label = 0;
static int temp = 0;
extern int line;
void mylog(char*);
static inline void move()
{
	look = get_token();
}

static inline void error(char* s){
	printf("near line %d : %s\n",line,s);
	exit(1);
}

static inline void match(int t){
	if(look->tag == t)
		move();
	else 
		error("syntax error");
}

static inline void gencode(char* code){
	printf("%s",code);
}

#define gen printf

void program();
void block();
void decls();
var_type type();
void dims();
void stmts();
void stmt();
void assign();
int boolean();
int join();
int equality();
int rel();
int _expr();
int term();
int unary();
int factor();
int offset(id a);
void init();

void mylog(char* s){
	printf("%s\n",s);

}
//program -> block
void program(){
	move();
	block();
}

//block -> {decls statements}
void block(){
	match('{');
	enviroment saved_env = top;
	top = Enviroment(top);
	decls();
	stmts();
	match('}');
	top = saved_env;
}

//decls -> var_type ID
void decls(){
	while(look->tag == BASIC){
		var_type p = type();
		token tok = look;
		match(ID);
		match(';');
		gen(" %s\n",tok->detail.word);
		id var_id = Id(tok,p,used);
		put_in_env(top,tok,var_id);
		used = used + p->detail.type.width;
	}
}

var_type type(){
	var_type p = look;
	match(BASIC);
	gen("%s",p->detail.type.name);
	if(look->tag == '[')
		dims();
	return p;
}

void dims(){
	match('[');
	token tok = look;
	match(NUM);
	gen("[%d]",tok->detail.num);
	match(']');
	if(look->tag == '[')
		dims();
}

void stmts(){
	while(look->tag != '}'){
		stmt();
	}
}

void stmt(){
	int l = label;
	int t;
	int br;
	switch(look->tag){
		case ';':
			move();
			break;
		case IF:     // if(x) s1  or  if(x) s1 else s2
			match(IF);
			match('(');
			t = boolean();
			match(')');
			gen("if false t%d goto L%d\n",t,l);
			stmt();
			gen("L%d:\n",label++);
			if(look->tag != ELSE)
				break;
			match(ELSE);
			stmt();
			break;
		case WHILE:
			match(WHILE);
			match('(');
			t = boolean();
			match(')');
			gen("L%d:\n",label++);
			stmt();
			gen("if true t%d goto L%d\n",t,l);
			gen("L%d:\n",label++);
			br = label;
			break;
		case DO:
			match(DO);
			gen("L%d:\n",label++);
			stmt();
			match(WHILE);
			match('(');
			t = boolean();
			match(')');
			match(';');
			gen("if true t%d goto L%d\n",t,l);
			break;
		case BREAK:
			match(BREAK);
			gen("goto L%d\n",br);
			match(';');
		case '{':
			block();
		default:
			assign();
	}
}

void assign(){
	int tmp,off;
	token t = look;
	match(ID);
	id i = get_from_env(top,t);
	if(i == NULL)
		error("undeclared variable in assign");
	if(look->tag == '='){
		move();
		tmp = boolean();
		gen("%s = t%d\n",t->detail.word,tmp);
	}else{
		off = offset(i);
		match('=');
		tmp = boolean();
		gen("t%d = t%d\n",off,tmp);
	}
	match(';');
}

int boolean(){
	int t,t1,t2;
	t1 = join();
	t = t1;
	while(look->tag == OR){
		t = temp++;
		move();
		t2 = join();
		gen("t%d = t%d || t%d\n",t,t1,t2);
		t1 = t;
	}
	return t;
}

int join(){
	int t,t1,t2;
	t1 = equality();
	t = t1;
	while(look->tag == AND){
		t = temp++;
		move();
		t2 = equality();
		gen("t%d = t%d && t%d\n",t,t1,t2);
		t1 = t;
	}
	return t;
}

int equality(){
	int t,t1,t2;
	token tok;
	t1 = rel();
	t = t1;
	while(look->tag == EQ || look->tag == NE){
		tok = look;
		t = temp++;
		move();
		t2 = rel();
		if(tok->tag == EQ)
			gen("t%d = t%d == t%d\n",t,t1,t2);
		if(tok->tag == NE)
			gen("t%d = t%d != t%d\n",t,t1,t2);
		t1 = t;
	}
	return t;
}

int rel(){
	int t,t1,t2;	
	t1 = _expr();
	switch(look->tag){
		case '<':
			t = temp++;
			move();
			t2 = _expr();
			gen("t%d = t%d < t%d\n",t,t1,t2);
			return t;
		case LE:
			t = temp++;
			move();
			t2 = _expr();
			gen("t%d = t%d <= t%d\n",t,t1,t2);
			return t;
		case GE:
			t = temp++;
			move();
			t2 = _expr();
			gen("t%d = t%d >= t%d\n",t,t1,t2);
			return t;
		case '>':
			t = temp++;
			move();
			t2 = _expr();
			gen("t%d = t%d > t%d\n",t,t1,t2);
			return t;
		default:
			return t1;
	}
}

int _expr(){
	int t,t1,t2;
	token tok;
	t1 = term();
	t = t1;
	while(look->tag == '+' || look->tag == '-'){
		token tok = look;
		t = temp++;
		move();
		t2 = term();
		if(tok->tag == '+')
			gen("t%d = t%d + t%d\n",t,t1,t2);
		if(tok->tag == '-')
			gen("t%d = t%d - t%d\n",t,t1,t2);
		t1 = t;
	}
	return t;
}

int term(){
	int t,t1,t2;
	token tok;
	t1 = unary();
	t = t1;
	while(look->tag == '*' || look->tag == '/'){
		tok = look;
		t = temp++;
		move();
		t2 = unary();
		if(tok->tag == '*')
			gen("t%d = t%d * t%d\n",t,t1,t2);
		if(tok->tag == '/')
			gen("t%d = t%d / t%d\n",t,t1,t2);
		t1 = t;
	}
	return t;
}

int unary(){
	int t,t1;
	if(look->tag == '-'){
		move();
		t = temp++;
		t1 = unary();
		gen("t%d = -t%d\n",t,t1);
		return t;
	}else if(look->tag == '!'){
		move();
		t = temp++;
		t1 = unary();
		gen("t%d = !t%d\n",t,t1);
		return t;
	}
	else return factor();
}

int factor(){
	int t,t1,off;
	float r;
	id var;
	t = temp++;
	switch(look->tag){
		case '(':
			move();
			t1 = boolean();
			match(')');
			gen("t%d = t%d\n",t,t1);
			return t;
		case NUM:
			t1 = look->detail.num;
			gen("t%d = %d\n",t,t1);
			move();
			return t;
		case REAL:
			r = look->detail.real;
			gen("t%d = %f\n",t,r);
			move();
			return t; 
		case TRUE:
			gen("t%d = true\n",t);
			move();
			return t;
		case FALSE:
			gen("t%d = false\n",t);
			move();
			return t;
		case ID:
			var = get_from_env(top,look);
			if(var == NULL)
				error("undeclared var in factor");
			move();
			if(look->tag != '['){
				gen("t%d = %s\n",t,var->name);
			}
			else{
				off = offset(var);
				gen("t%d = %s",off,var->name);
			}
			return t;
		default:
			error("syntax error");
	}
}

int offset(id a){
	int t,b,w,loc,t1;
	var_type type = a->p;
	match('[');
	b = boolean();
	match(']');
	w = type->detail.type.width;
	t = temp++;
	gen("t%d = |%s + t%d * %d|\n",t,a->name,b,w);
	loc = t;
	while(look->tag == '['){
		t = temp++;
		match('[');
		b = boolean();
		match(']');
		w = type->detail.type.width;
		gen("t%d = t%d * %d\n",t,b,w);
		t1 = t;
		t = temp++;
		gen("t%d = t%d + t%d\n",t,loc,t1);
		loc = t;
	}
	return t;
}
