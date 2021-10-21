#ifndef _LIST_H_
#define _LIST_H_

typedef struct list_t
{
	void *data ;
	struct list_t *next ;
} list_t ;

list_t *list_create(void *data) ;

// the function pointer is used to destroy the data 
void list_delete(list_t *l, void(*d)(void *)) ;

void list_insert(list_t *l, void *d, int i) ;
void *list_remove(list_t *l, int i) ;

void *list_get(list_t *l, int i) ;
void *list_set(list_t *l, void *d, int i) ;

void list_push_back(list_t *l, void *d) ;
int __list_len(list_t *l, int i) ;

#define list_len(l) __list_len(l, 0)

#endif
