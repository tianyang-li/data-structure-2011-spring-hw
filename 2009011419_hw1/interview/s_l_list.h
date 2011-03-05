/*
 * singly linked list
 */

#ifndef S_L_LIST_H
#define S_L_LIST_H

typedef void *SLListData;  /* pointer to data stored in a SLListNode */

typedef struct SLListNode {
	struct SLListNode *next_;
	SLListData data_;
} SLListNode;

typedef struct SLList {
	SLListNode *head_;
} SLList;

void SLListInit(SLList *cur_list);  /* init an existing list */

SLList *SLListCreate();  /* create a new list by allocating new memory */

void SLListDestroy(SLList *to_destroy);

#endif  /* S_L_LIST_H */

