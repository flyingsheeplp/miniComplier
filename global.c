/*************************************************************************
  * File Name: global.c
  * Author: Li Peng
  * Mail: flyingsheep.lp@gmail.com 
  * Created Time: 2013-11-07 15:20:46
  * Description:
 ************************************************************************/

#include <stdio.h>
#include "include/token.h"
#include "include/hash.h"
#include "include/tag.h"
#include "include/global.h"

var_type TYPE_INT,TYPE_CHAR,TYPE_FLOAT;
token and,or,eq,ne,le,ge,minus,True,False,tmp;
hashtable symbol;
token If,While,Else;

void init_system(){
	symbol = init_hashtable();
	TYPE_INT = Type("int",BASIC,4);
	TYPE_CHAR = Type("char",BASIC,1);
	TYPE_FLOAT = Type("float",BASIC,8);
	and = Word("&&",AND);
	or = Word("||",OR);
	eq = Word("==",EQ);
	ne = Word("!=",NE);
	le = Word("<=",LE);
	ge = Word(">=",GE);
	If = Word("if",IF);
	While = Word("while",WHILE);
	Else = Word("else",ELSE);
	minus = Word("-",MINUS);
	True = Word("true",TRUE);
	False = Word("false",FALSE);
	tmp = Word("t",TEMP);

	put_in_hashtable(symbol,If);
	put_in_hashtable(symbol,Else);
	put_in_hashtable(symbol,While);
}

