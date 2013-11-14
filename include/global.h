/*************************************************************************
  * File Name: include/global.h
  * Author: Li Peng
  * Mail: flyingsheep.lp@gmail.com 
  * Created Time: 2013-11-07 15:10:28
  * Description:
 ************************************************************************/

#include "hash.h"
#include "token.h"

#ifndef _GLOBAL_H_
#define _GLOBAL_H_

extern var_type TYPE_INT;
extern var_type TYPE_CHAR;
extern var_type TYPE_FLOAT;

extern token and;
extern token or;
extern token eq;
extern token ne;
extern token le;
extern token ge;
extern token minus;
extern token True;
extern token False;
extern token tmp;
extern token If;
extern token While;

extern hashtable symbol;


void init_system();
#endif
