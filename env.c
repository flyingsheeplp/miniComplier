/*************************************************************************
  * File Name: env.c
  * Author: Li Peng
  * Mail: flyingsheep.lp@gmail.com 
  * Created Time: 2013-11-08 17:01:27
  * Description:
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "include/env.h"
#include "include/inter.h"
#include "include/token.h"

static int env_loc(char* s){
	int h = 0;
	while(*s++)
		h = h * 31 + *s;
	return h % ENV_SIZE;
}

static env_entry Env_entry(token t,id i){
	env_entry entry = (env_entry)malloc(sizeof(struct _env_entry));
	entry->t = t;
	entry->i = i;
	entry->next = NULL;
	return entry;
}

enviroment Enviroment(enviroment e){
	int i;
	envtable tab = (envtable)malloc(ENV_SIZE * sizeof(env_entry));
	for(i=0;i<ENV_SIZE;i++)
		tab[i] = NULL;
	enviroment newenv = (enviroment)malloc(sizeof(struct _enviroment));
	newenv->tab = tab;
	newenv->next = e;
	return newenv;
}

void put_in_env(enviroment e,token t,id i){
	int h = env_loc(t->detail.word);
	env_entry new_entry = Env_entry(t,i);
	env_entry head = e->tab[h];
	new_entry->next = head;
	e->tab[h] = new_entry;
}

id get_from_env(enviroment e,token t){
	if(e == NULL)
		return NULL;
	int h = env_loc(t->detail.word);
	env_entry head ;
	for(head = e->tab[h];head != NULL;head=head->next){
		if(token_equal(t,head->t)){
			return head->i;
		}
	}
	return get_from_env(e->next,t);
}
