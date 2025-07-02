#ifndef LINKEDLIST_H
#define LINKEDLIST_H 1
#include <stddef.h>

typedef struct Node {
	void* data;
	struct Node* next;
	struct Node* prev;
} Node;

typedef struct LinkedList {
	Node* head;
	Node* tail;
	size_t data_size;
	size_t size;
} LinkedList;

///////////////////////////////////////////////////////////////////
// Function					: LinkedListCreate
// Author					: MAHA
// Description				: Allocates and initialize a new list
// Date of Creation			: 22/06/2025
// Date of Modification		: 22/06/2025
///////////////////////////////////////////////////////////////////
LinkedList* LinkedListCreate(size_t data_size);

///////////////////////////////////////////////////////////////////
// Function					: LinkedListFinalize
// Author					: MAHA
// Description				: Frees a list and it's remaining nodes
// Date of Creation			: 22/06/2025
// Date of Modification		: 22/06/2025
///////////////////////////////////////////////////////////////////
int LinkedListFinalize(LinkedList* list);

///////////////////////////////////////////////////////////////////
// Function					: LinkedListPeek
// Author					: MAHA
// Description				: Returns a shallow copy of the last element inserted in the list
// Date of Creation			: 22/06/2025
// Date of Modification		: 22/06/2025
///////////////////////////////////////////////////////////////////
void* LinkedListPeek(LinkedList* list);

///////////////////////////////////////////////////////////////////
// Function					: LinkedListPeekAt
// Author					: MAHA
// Description				: Returns a shallow copy of an element in the list
// Date of Creation			: 22/06/2025
// Date of Modification		: 22/06/2025
///////////////////////////////////////////////////////////////////
void* LinkedListPeekAt(LinkedList* list, size_t idx);

///////////////////////////////////////////////////////////////////
// Function					: LinkedListPop
// Author					: MAHA
// Description				: Returns and deletes a shallow copy of the last element inserted in the list
// Date of Creation			: 22/06/2025
// Date of Modification		: 22/06/2025
///////////////////////////////////////////////////////////////////
void* LinkedListPop(LinkedList* list);

///////////////////////////////////////////////////////////////////
// Function					: LinkedListPopAt
// Author					: MAHA
// Description				: Returns and deletes a shallow copy of an element in the list
// Date of Creation			: 22/06/2025
// Date of Modification		: 22/06/2025
///////////////////////////////////////////////////////////////////
void* LinkedListPopAt(LinkedList* list, size_t idx);

///////////////////////////////////////////////////////////////////
// Function					: LinkedListPush
// Author					: MAHA
// Description				: Inserts a shallow copy of @data as the last element in the list
// Date of Creation			: 22/06/2025
// Date of Modification		: 22/06/2025
///////////////////////////////////////////////////////////////////
int LinkedListPush(LinkedList* list, const void* data);

///////////////////////////////////////////////////////////////////
// Function					: LinkedListPushAt
// Author					: MAHA
// Description				: Inserts a shallow copy of @data as the element in the @idx position in the list
// Date of Creation			: 22/06/2025
// Date of Modification		: 22/06/2025
///////////////////////////////////////////////////////////////////
int LinkedListPushAt(LinkedList* list, const void* data, size_t idx);

///////////////////////////////////////////////////////////////////
// Function					: LinkedListSize
// Author					: MAHA
// Description				: Returns the size of the list.
// Date of Creation			: 22/06/2025
// Date of Modification		: 22/06/2025
///////////////////////////////////////////////////////////////////
size_t LinkedListSize(LinkedList* list);

#endif // LINKEDLIST_H
