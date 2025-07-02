#include <stdlib.h>
#include <string.h>
#include <logger.h>
#include <err.h>
#include <linkedlist.h>

// TODO: Check alloc validations
// TODO: Change logs to debug logs
// TODO: Check size modifying


///////////////////////////////////////////////////////////////////
// Function					: NodeGetAt
// Author					: MAHA
// Description				: Auxiliar function to get a particular idx in list
// Date of Creation			: 22/06/2025
// Date of Modification		: 22/06/2025
///////////////////////////////////////////////////////////////////
static Node* NodeGetAt(LinkedList* list, size_t idx) {
	Node* current;
	size_t dist_from_tail = list->size-1-idx;

	if(dist_from_tail >= idx) {
		current = list->head;
		for(size_t count = 0; count < idx; count++)
			current = current->next;
	} else {
		current = list->tail;
		for(size_t count = 0; count < list->size-idx-1; count++)
			current = current->prev;
	}

	return current;
}

///////////////////////////////////////////////////////////////////
// Function					: NodeCreate
// Author					: MAHA
// Description				: Auxiliar function to allocate and initialize a new node
// Date of Creation			: 22/06/2025
// Date of Modification		: 22/06/2025
///////////////////////////////////////////////////////////////////
static Node* NodeCreate(const void* data, size_t data_size) {
	Node* new_node;

	if((new_node = malloc(sizeof(Node))) == NULL) {
		Log(sERROR,__func__,"[ERRC_NOMEM]: The process ran out of memory");
		return NULL;
	}
	if((new_node->data = malloc(data_size)) == NULL) {
		Log(sERROR,__func__,"[ERRC_NOMEM]: The process ran out of memory");
		free(new_node);
		return NULL;
	}

	memcpy(new_node->data,data,data_size);
	new_node->next = NULL;
	new_node->prev = NULL;
	return new_node;
}

///////////////////////////////////////////////////////////////////
// Function					: NodeFinalize
// Author					: MAHA
// Description				: Auxiliar function to free a Node
// Date of Creation			: 22/06/2025
// Date of Modification		: 22/06/2025
///////////////////////////////////////////////////////////////////
static void NodeFinalize(Node* current) {
	if(current == NULL) return;
	current->next = NULL;
	current->prev = NULL;
	if(current->data != NULL) {
		free(current->data);
	}
	free(current);
}

///////////////////////////////////////////////////////////////////
// Function					: LinkedListCreate
// Author					: MAHA
// Description				: Allocates and initialize a new list
// Date of Creation			: 22/06/2025
// Date of Modification		: 22/06/2025
///////////////////////////////////////////////////////////////////
LinkedList* LinkedListCreate(size_t data_size) {
	if(data_size == 0) {
		Log(sWARNING,__func__,"data_size is invalid");
		return NULL;
	}

	LinkedList* list;

	if((list = malloc(sizeof(LinkedList))) == NULL) {
		Log(sERROR,__func__,"[ERRC_NOMEM]: The process ran out of memory\n");
		return NULL;
	}

	list->data_size = data_size;
	list->head = NULL;
	list->tail = NULL;
	list->size = 0;
	return list;
}

///////////////////////////////////////////////////////////////////
// Function					: LinkedListFinalize
// Author					: MAHA
// Description				: Frees a list and it's remaining nodes
// Date of Creation			: 22/06/2025
// Date of Modification		: 22/06/2025
///////////////////////////////////////////////////////////////////
int LinkedListFinalize(LinkedList* list) {
	if(list == NULL) {
		Log(sWARNING,__func__,"list is NULL");
		return ERRC_NULPTR;
	}
	if(list->size == 0) {
		free(list);
		return ERRC_OK;
	}

	Node* current = list->head;
	Node* next;

	while(current != NULL) {
		next = current->next;
		NodeFinalize(current);
		current = next;
	}

	list->head = NULL;
	list->tail = NULL;
	list->size = 0;
	free(list);

	return ERRC_OK;
}

///////////////////////////////////////////////////////////////////
// Function					: LinkedListPeek
// Author					: MAHA
// Description				: Returns a shallow copy of the last element inserted in the list
// Date of Creation			: 22/06/2025
// Date of Modification		: 22/06/2025
///////////////////////////////////////////////////////////////////
void* LinkedListPeek(LinkedList* list) {
	if(list == NULL) {
		Log(sWARNING,__func__,"list is NULL");
		return NULL;
	}
	if(list->size == 0) {
		return NULL;
	}

	void* data_res = malloc(list->data_size);
	if(data_res == NULL) {
		Log(sERROR,__func__,"[ERRC_NOMEM]: The process ran out of memory");
		return NULL;
	}

	memcpy(data_res,list->tail->data,list->data_size);
	return data_res;
}

///////////////////////////////////////////////////////////////////
// Function					: LinkedListPeekAt
// Author					: MAHA
// Description				: Returns a shallow copy of an element in the list
// Date of Creation			: 22/06/2025
// Date of Modification		: 22/06/2025
///////////////////////////////////////////////////////////////////
void* LinkedListPeekAt(LinkedList* list, size_t idx) {
	if(list == NULL) {
		Log(sWARNING,__func__,"list is NULL");
		return NULL;
	}
	if(idx >= list->size) {
		Log(sWARNING,__func__,"idx is invalid");
		return NULL;
	}
	if(idx == list->size-1)
		return LinkedListPeek(list);

	Node* current = NodeGetAt(list,idx);
	void* data_res = malloc(list->data_size);
	if(data_res == NULL) {
		Log(sERROR,__func__,"[ERRC_NOMEM]: The process ran out of memory");
		return NULL;
	}

	memcpy(data_res,current->data,list->data_size);
	return data_res;
}

///////////////////////////////////////////////////////////////////
// Function					: LinkedListPop
// Author					: MAHA
// Description				: Returns and deletes a shallow copy of the last element inserted in the list
// Date of Creation			: 22/06/2025
// Date of Modification		: 22/06/2025
///////////////////////////////////////////////////////////////////
void* LinkedListPop(LinkedList* list) {
	if(list == NULL) {
		Log(sWARNING,__func__,"list is NULL");
		return NULL;
	}
	if(list->size == 0) {
		return NULL;
	}

	Node* new_tail = list->tail->prev;
	void* data_res = malloc(list->data_size);
	if(data_res == NULL) {
		Log(sERROR,__func__,"[ERRC_NOMEM]: The process ran out of memory");
		return NULL;
	}

	memcpy(data_res,list->tail->data,list->data_size);
	NodeFinalize(list->tail);
	list->tail = new_tail;
	if(new_tail != NULL)
		new_tail->next = NULL;
	list->size--;

	return data_res;
}

///////////////////////////////////////////////////////////////////
// Function					: LinkedListPopAt
// Author					: MAHA
// Description				: Returns and deletes a shallow copy of an element in the list
// Date of Creation			: 22/06/2025
// Date of Modification		: 22/06/2025
///////////////////////////////////////////////////////////////////
void* LinkedListPopAt(LinkedList* list, size_t idx) {
	if(list == NULL) {
		Log(sWARNING,__func__,"list is NULL");
		return NULL;
	}
	if(idx >= list->size) {
		Log(sWARNING,__func__,"idx is invalid");
		return NULL;
	}
	if(idx == list->size-1)
		return LinkedListPop(list);

	Node* current = NodeGetAt(list,idx);
	void* data_res = malloc(list->data_size);
	if(data_res == NULL) {
		Log(sERROR,__func__,"[ERRC_NOMEM]: The process ran out of memory");
		return NULL;
	}

	memcpy(data_res,current->data,list->data_size);
	current->next->prev = current->prev;
	if(current->prev != NULL)
		current->prev->next = current->next;
	NodeFinalize(current);
	list->size--;

	return data_res;
}

///////////////////////////////////////////////////////////////////
// Function					: LinkedListPush
// Author					: MAHA
// Description				: Inserts a shallow copy of @data as the last element in the list
// Date of Creation			: 22/06/2025
// Date of Modification		: 22/06/2025
///////////////////////////////////////////////////////////////////
int LinkedListPush(LinkedList* list, const void* data) {
	if(list == NULL) {
		Log(sWARNING,__func__,"list is NULL");
		return ERRC_NULPTR;
	}
	if(data == NULL) {
		Log(sWARNING,__func__,"data is NULL");
		return ERRC_NULPTR;
	}

	Node* new_node = NodeCreate(data,list->data_size);
	if(new_node == NULL) {
		Log(sERROR,__func__,"[ERRC_NOMEM]: The process ran out of memory");
		return ERRC_NOMEM;
	}

	list->size++;

	if(list->head == NULL && list->tail == NULL) {
		list->head = new_node;
		list->tail = new_node;
		return ERRC_OK;
	}

	list->tail->next = new_node;
	new_node->prev = list->tail;
	list->tail = new_node;

	return ERRC_OK;
}

///////////////////////////////////////////////////////////////////
// Function					: LinkedListPushAt
// Author					: MAHA
// Description				: Inserts a shallow copy of @data as the element in the @idx position in the list
// Date of Creation			: 22/06/2025
// Date of Modification		: 22/06/2025
///////////////////////////////////////////////////////////////////
int LinkedListPushAt(LinkedList* list, const void* data, size_t idx) {
	if(list == NULL) {
		Log(sWARNING,__func__,"list is NULL");
		return ERRC_NULPTR;
	}
	if(data == NULL) {
		Log(sWARNING,__func__,"data is NULL");
		return ERRC_NULPTR;
	}
	if(idx != 0 && idx >= list->size) {
		Log(sWARNING,__func__,"idx is invalid");
		return ERRC_BADARG;
	}
	if(list->size == 0 || idx == list->size-1)
		return LinkedListPush(list,data);

	Node* current;
	size_t dist_from_tail = list->size-1-idx;
	Node* new_node = NodeCreate(data,list->data_size);
	if(new_node == NULL) {
		Log(sERROR,__func__,"[ERRC_NOMEM]: The process ran out of memory");
		return ERRC_NOMEM;
	}

	if(dist_from_tail >= idx) { // It's faster to start from the head
		current = list->head;

		for(size_t count = 0; count < idx; count++)
			current = current->next;
	}
	if(dist_from_tail < idx) { // It's faster to start from the tail
		current = list->tail;

		for(size_t count = 0; count < dist_from_tail; count++)
			current = current->prev;
	}

	new_node->next = current;
	new_node->prev = current->prev;
	if(current->prev != NULL)
		current->prev->next = new_node;
	current->prev = new_node;
	list->size++;

	return ERRC_OK;
}

///////////////////////////////////////////////////////////////////
// Function					: LinkedListSize
// Author					: MAHA
// Description				: Returns the size of the list.
// Date of Creation			: 22/06/2025
// Date of Modification		: 22/06/2025
///////////////////////////////////////////////////////////////////
size_t LinkedListSize(LinkedList* list) {
	if(list == NULL) {
		Log(sWARNING,__func__,"list is NULL");
		return 0;
	}
	return list->size;
}
