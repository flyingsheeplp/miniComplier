/*************************************************************************
  * File Name: id.c
  * Author: Li Peng
  * Mail: flyingsheep.lp@gmail.com 
  * Created Time: 2013-11-11 16:57:31
  * Description:
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "include/inter.h"

id Id(token t,var_type p,int used){
	id i = (id)malloc(sizeof(struct _id));
	i->used = used;
	i->name = (char*)malloc((sizeof(char) * strlen(t->detail.word))+1);
	strcpy(i->name,t->detail.word);
	i->p = p;
	return i;
}
