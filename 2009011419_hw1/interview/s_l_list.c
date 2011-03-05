#include "s_l_list.h"

void SLListInit(SLList *cur_list) {
	cur_list->head_->data_ = NULL;
	cur_list->head_->next_ = NULL;
}

SLList *SLListCreate() {
	/* create a new list */

	SLList *new_list = (SLList *) malloc(sizeof(SLList));
	if (new_list == NULL) {
		perror("Unable to allocate memory when creating a list!");
		return NULL;
	}

	new_list->head_ = (SLListNode *) malloc(sizeof(SLListNode));
	if (new_list->head_ == NULL) {
		perror("Unable to allocate memory when creating a node for a new list!");
		free(new_list);
		return NULL;
	}

	SLListInit(new_list);

	return new_list;
}

void SLListDestroy(SLList *to_destroy) {
	SLListNode *temp1, *temp2;
}


