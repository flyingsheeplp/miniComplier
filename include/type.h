/*************************************************************************
  * File Name: type.h
  * Author: Li Peng
  * Mail: flyingsheep.lp@gmail.com 
  * Created Time: 2013-11-08 16:02:03
  * Description:
 ************************************************************************/

#ifndef _TYPE_H_
#define _TYPE_H_

struct _type{
	int tag;
	int width;
	char* name;
};

typedef struct _type* var_type;

var_type Type(char* n,int tag,int w);
var_type max(var_type p1,var_type p2);

#endif
