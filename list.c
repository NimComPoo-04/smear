#include <stdio.h>
#include <stdlib.h>

#include "list.h"

list_t *list_create(void *data)
{
	list_t *l = malloc(sizeof(list_t)) ;
	l->data = data ;
	l->next = NULL ;
	return l ;
}

void list_delete(list_t *l, void(*d)(void *))
{
	if(l == NULL)
		return ;
	if(d != NULL)
		d(l->data) ;

	list_t *n = l->next ;
	free(l) ;

	list_delete(n, d) ;
}

void list_insert(list_t *l, void *d, int i)
{
	if(i < 1) return ;
	if(i == 1)
	{
		list_t *x = list_create(d) ;
		x->next = l->next ;
		l->next = x ;
	}
	else
		list_insert(l->next, d, i-1) ;
}

void *list_remove(list_t *l, int i)
{
	if(i < 1) return NULL ;
	if(i == 1)
	{
		list_t *x = l->next ;
		void *d = x->data ;
		l->next = l->next->next ;
		free(x) ;
		return d ;
	}
	else
		return list_remove(l->next, i-1) ;
}

void *list_get(list_t *l, int i)
{
	if(i == 0)
	{
		return l->data ;
	}
	else
		return list_get(l->next, i-1) ;
}

void *list_set(list_t *l, void *d, int i)
{
	if(i == 0)
	{
		void *x = l->data ;
		l->data = d ;
		return x ;
	}
	else
		return list_set(l->next, d, i-1) ;
}

void list_push_back(list_t *l, void *d)
{
	if(l->next == NULL)
	{
		list_t *x = list_create(d) ;
		x->next = l->next ;
		l->next = x ;
	}
	list_push_back(l->next, d) ;
}

int __list_len(list_t *l, int i)
{
	if(l == NULL) return i ;
	return __list_len(l->next, i+1) ;
}
