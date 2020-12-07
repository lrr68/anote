/* HEADERS */
#include <stdlib.h>

#include "list.h"

/* FUNCTION DEFINITIONS */
int
d_list_length(struct d_list *list)
{
	int l;
	struct d_list *i;
	for (i=list; i->next; i = i->next)
		++l;
	return l;
}

struct d_list *
new_list_node(void)
{
	struct d_list *list = (struct d_list *) malloc(sizeof(struct d_list));
	list->obj = NULL;
	list->next = NULL;
}

void
d_list_add(void *obj, struct d_list **list, size_t obj_size)
{
	struct d_list *i;
	for (i=*list; i->obj; i = i->next);

	i->next = new_list_node();
	i->obj = malloc(obj_size);

	memcpy(i->obj, obj, obj_size);
}

void /* adds obj before ref, if ref not found, adds to end of the list*/
d_list_add_before(void *obj, struct d_list *ref, struct d_list **list, size_t obj_size)
{
	struct d_list *i;
	struct d_list *aux;


	/* has to add new head */
	if (ref == *list) {

		(*list) = new_list_node();
		(*list)->next = ref;
		(*list)->obj = malloc(obj_size);
		memcpy((*list)->obj, obj, obj_size);

	} else {

		/* finds the reference */
		i = *list;
		while (i->next && i->next != ref)
			i = i->next;

		aux = i->next;
		i->next = new_list_node();
		i->next->next = aux;
		i->next->obj = malloc(obj_size);
		memcpy(i->next->obj, obj, obj_size);
	}
}

void /* adds last object and points it to the head to make a circular list */
d_list_add_circular(void *obj, struct d_list **list, size_t obj_size)
{
	struct d_list *i;
	struct d_list *head;
	struct d_list *aux;

	i = *list;
	head = i;
	for (; i->next != head; i = i->next);

	i->next = new_list_node();
	i->obj = malloc(obj_size);
	i->next->next = head;

	memcpy(i->obj, obj, obj_size);
}

void
d_list_del_pos(int pos, struct d_list *list)
{
	int i;
	struct d_list *j;
	struct d_list *aux;

	/* never delete the head */
	if (list != NULL && list->next != NULL && pos > 0) {

		/* finds the position */
		for (i=0, j=list; i<pos-1 && j->next->next != NULL; ++i, j=j->next);

		aux = j->next;
		j->next = aux->next;
		free(aux);
	}
}

void
d_list_del_obj(void *obj, struct d_list *list)
{
	struct d_list *i;
	struct d_list *aux;

	/* never delete the head */
	if (list != NULL && list->next != NULL && obj != list->obj) {

		/* finds the position */
		for (i=list; i->next != NULL && i->next != obj; i=i->next);

		if (i->next == obj) {
			aux = i->next;
			i->next = aux->next;
			free(aux);
		}
	}
}

void
delete_list(struct d_list *list)
{
	/* delete all objects */
	while (list->next != NULL)
		d_list_del_obj(list->next,list);

	free(list->next);
	free(list);
}
