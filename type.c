/*************************************************************************
  * File Name: type.c
  * Author: Li Peng
  * Mail: flyingsheep.lp@gmail.com 
  * Created Time: 2013-11-08 16:13:38
  * Description:
 ************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "include/token.h"
#include "include/tag.h"
#include "include/global.h"

#define isequal(p1,p2) \
	((p1->tag == p2->tag) && \
	(p1->detail.type.width == p2->detail.type.width) && \
	!strcmp(p1->detail.type.name,p2->detail.type.name))


var_type Type(char* s,int t,int w){
	var_type v = (var_type)malloc(sizeof(struct _token));
	v->tag = t;
	v->detail.type.width = w;
	v->detail.type.name = (char*)malloc(strlen(s) + 1);
	strcpy(v->detail.type.name,s);
	return v;
}

/*
static int isequal(var_type p1,var_type p2){
	return (p1->tag == p2->tag) && (p1->width == p2->width) && !strcmp(p1->name,p2->name);
}
*/

static int isnumeric(var_type p){
	return isequal(p,TYPE_CHAR) || isequal(p,TYPE_INT) || isequal(p,TYPE_FLOAT);
}

var_type max(var_type p1,var_type p2){
	if(!isnumeric(p1) || !isnumeric(p2))
		return NULL;
	else if(isequal(p1,TYPE_FLOAT) || isequal(p2,TYPE_FLOAT))
		return TYPE_FLOAT;
	else if(isequal(p1,TYPE_INT) || isequal(p2,TYPE_INT))
		return TYPE_INT;
	else
		return TYPE_CHAR;
}
