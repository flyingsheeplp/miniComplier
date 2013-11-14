/*************************************************************************
  * File Name: include/env.h
  * Author: Li Peng
  * Mail: flyingsheep.lp@gmail.com 
  * Created Time: 2013-11-08 16:41:31
  * Description:
 ************************************************************************/

#include "token.h"
#include "inter.h"

#ifndef _ENV_H_
#define _ENV_H_

#define ENV_SIZE 131

struct _env_entry{
	token t;
	id i;
	struct _env_entry* next;
};

typedef struct _env_entry* env_entry;
typedef env_entry* envtable;

struct _enviroment{
	envtable tab;
	struct _enviroment* next;
};

typedef struct _enviroment* enviroment;

enviroment Enviroment(enviroment e);
id get_from_env(enviroment e,token t);
void put_in_env(enviroment e,token t,id i);



#endif
