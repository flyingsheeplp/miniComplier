/*************************************************************************
  * File Name: include/inter.h
  * Author: Li Peng
  * Mail: flyingsheep.lp@gmail.com 
  * Created Time: 2013-11-11 10:34:23
  * Description:
 ************************************************************************/

#ifndef _INTER_H_
#define _INTER_H_

#include "token.h"

struct _id{
	var_type p;
	int used;
	char* name;
};

typedef struct _id* id;

id Id(token t,var_type p,int used);

#endif
