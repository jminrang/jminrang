#ifndef	__LIST_H__
#define	__LIST_H__

#include "types.h"

//
//	simple double linked list implementation by linux/include/linux/list.h
//	for other data structure
//

struct	list_head	{
	struct list_head *next, *prev;
};

#define	LIST_HEAD_INIT(name)	{ &(name), &(name) }

#define	LIST_HEAD(name)			\
	struct list_head name = LIST_HEAD_INIT(name)

//	initialize list 
//	now 1 entry
static inline void	INIT_LIST_HEAD	(struct list_head *list)	{
	list->next	= list;
	list->prev	= list;
}

//	add list between two entry (prev, next)
//	prev <-> new <-> next
static inline void	__list_add		(struct list_head *new,
									 struct list_head *prev,
									 struct list_head *next)	{
	next->prev	= new;
	new->next	= next;
	new->prev	= prev;
	prev->next	= new;
}

//	add list 
//	prev <-> new
static inline void	list_add		(struct list_head *new,
									 struct list_head *head)	{
	__list_add(new, head, head->next);
}

//	add list
//	new <-> prev
static inline void	list_add_tail	(struct list_head *new,
									 struct list_head *head)	{
	__list_add(new, head->prev, head);
}

static inline void	__list_del		(struct list_head * prev, 
									 struct list_head * next)	{
	next->prev	= prev;
	prev->next	= next;
}

static inline void	__list_del_entry(struct list_head *entry)	{
	__list_del(entry->prev, entry->next);
	entry->next	= NULL;	// page fualt (LIST_POISON)
	entry->prev	= NULL;	// page fault (LIST_POISON)
}

//	change old and new
static inline void	list_replace	(struct list_head *old,
									 struct list_head *new)	{
	new->next	= old->next;
	new->next->prev	= new;
	new->prev	= old->prev;
	new->prev->next	= new;
}

static inline void	list_replace_init	(struct list_head *old,
										 struct list_head *new)	{
	list_replace(old, new);
	INIT_LIST_HEAD(old);
}

static inline void	list_del_init	(struct list_head *entry)	{
	__list_del_entry(entry);
	INIT_LIST_HEAD(entry);
}

static inline void	list_move		(struct list_head *list,
									 struct list_head *head)	{
	__list_del_entry(list);
	list_add(list, head);	
}

static inline void	list_move_tail	(struct list_head *list,
									 struct list_head *head)	{
	__list_del_entry(list);
	list_add_tail(list, head);
}

static inline int32_t	list_is_last	(struct list_head *list,
										 const struct list_head *head)	{
	return list->next == head;
}

static inline int32_t	list_enpty	(struct list_head *head)	{
	return head->next == head;
}


#endif
