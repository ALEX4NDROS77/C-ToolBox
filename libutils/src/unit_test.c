#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <err.h>
#include <linkedlist.h>
#include <logger.h>

#define STRSS_ITERATION	15000000

// TODO: [X] Validate for null every allocation, `LinkedListCreate`
// TODO: [ ] Enhance tests

static int TestListSize(void) {
	return ERRC_OK;
}

static int TestListPopAt(void) {
	return ERRC_OK;
}

static int TestListPop(void) {
	return ERRC_OK;
}

static int TestListPeekAt(void) {
	LinkedList* list;
	int aux_int;
	unsigned long aux_long;
	char* aux_str;
	void* res_ptr;

	// int
	DefLogDebug("Beginning Peek-At Test with Int as Data Type");
	if((list = LinkedListCreate(sizeof(int))) == NULL) {
		Log(sERROR,__func__,"The list couldn't be created for the test");
		return ERRC_FATAL;
	}
	for(int idx = 0; idx < 25000; idx++) {
		aux_int = idx;
		if(LinkedListPush(list,&aux_int) != ERRC_OK) {
			Log(sERROR,__func__,"The list couldn't store the element [%d]",aux_int);
			LinkedListFinalize(list);
			return ERRC_FATAL;
		}
	}
	
	for(int idx = 0; idx < 25000; idx++) {
		if((res_ptr = LinkedListPeekAt(list,idx)) == NULL) {
			Log(sERROR,__func__,"Invalid value returned from the list");
			LinkedListFinalize(list);
			return ERRC_FATAL;
		}
		if(*(int*)res_ptr != idx) {
			Log(sERROR,__func__,"Couldn't get the value from the element at [%d]",idx);
			LinkedListFinalize(list);
			free(res_ptr);
			return ERRC_FATAL;
		}
		free(res_ptr);
	}
	LinkedListFinalize(list);

	// ulong
	DefLogDebug("Beginning Peek-At Test with Unsigned Long as Data Type");
	if((list = LinkedListCreate(sizeof(unsigned long))) == NULL) {
		Log(sERROR,__func__,"The list couldn't be created for the test");
		return ERRC_FATAL;
	}
	for(int idx = 0; idx < 25000; idx++) {
		aux_long = idx;
		if(LinkedListPush(list,&aux_long) != ERRC_OK) {
			Log(sERROR,__func__,"The list couldn't store the element [%d]",aux_long);
			LinkedListFinalize(list);
			return ERRC_FATAL;
		}
	}

	for(int idx = 0; idx < 25000; idx++) {
		if((res_ptr = LinkedListPeekAt(list,idx)) == NULL) {
			Log(sERROR,__func__,"Invalid value returned from the list");
			LinkedListFinalize(list);
			return ERRC_FATAL;
		}

		if(*(int*)res_ptr != idx) {
			Log(sERROR,__func__,"Couldn't get the value from the element at [%d]",idx);
			LinkedListFinalize(list);
			free(res_ptr);
			return ERRC_FATAL;
		}
		free(res_ptr);
	}
	LinkedListFinalize(list);

	// char
	DefLogDebug("Beginning Peek-At Test with Char as Data Type");
	if((list = LinkedListCreate(sizeof(char))) == NULL) {
		Log(sERROR,__func__,"The list couldn't be created for the test");
		LinkedListFinalize(list);
		return ERRC_FATAL;
	}
	for(int idx = 0; idx < 25000; idx++) {
		if((res_ptr = LinkedListPeekAt(list,idx)) == NULL) {
			Log(sERROR,__func__,"Invalid value returned from the list");
			LinkedListFinalize(list);
			return ERRC_FATAL;
		}
		if(*(char*)res_ptr != (char)(' '+idx%94)) {
			Log(sERROR,__func__,"Couldn't get the value from the element at [%d]",idx);
			LinkedListFinalize(list);
			free(res_ptr);
			return ERRC_FATAL;
		}
		free(res_ptr);
	}
	LinkedListFinalize(list);

	// str
	DefLogDebug("Beginning Peek-At Test with String as Data Type");
	if((list = LinkedListCreate(256)) == NULL) {
		Log(sERROR,__func__,"The list couldn't be created fot the test");
		return ERRC_FATAL;
	}
	for(int idx = 0; idx < 25000; idx++) {
		if((aux_str = malloc(256)) == NULL) {
			Log(sERROR,__func__,"Memory allocation failed for aux_str");
			LinkedListFinalize(list);
		}
        snprintf(aux_str, 256, "This is the iteration number %d", idx);
		if(LinkedListPush(list,aux_str) != ERRC_OK) {
			Log(sERROR,__func__,"The list couldn't store the element [%d]",aux_long);
			LinkedListFinalize(list);
			free(aux_str);
			return ERRC_FATAL;
		}
		free(aux_str);
	}

	for(int idx = 0; idx < 25000; idx++) {
		if((aux_str = malloc(256)) == NULL) {
			Log(sERROR,__func__,"Memory allocation failed for aux_str");
			LinkedListFinalize(list);
		}
        snprintf(aux_str, 256, "This is the iteration number %d", idx);
		if((res_ptr = LinkedListPeekAt(list,idx)) == NULL) {
			Log(sERROR,__func__,"Invalid value returned from the list");
			LinkedListFinalize(list);
			return ERRC_FATAL;
		}
		if(strcmp((char*)res_ptr,aux_str) != 0) {
			Log(sERROR,__func__,"Couldn't get the value from the element at [%d]",idx);
			LinkedListFinalize(list);
			free(res_ptr);
			free(aux_str);
			return ERRC_FATAL;
		}
		free(aux_str);
		free(res_ptr);
	}
	LinkedListFinalize(list);

	return ERRC_OK;
}

static int TestListPeek(void) {
	LinkedList* list;
	int aux_int;
	unsigned long aux_long;
	char aux_char;
	char* aux_str;
	void* res_ptr;

	// int
	DefLogDebug("Beginning Peek Test with Int as Data Type");
	if((list = LinkedListCreate(sizeof(int))) == NULL) {
		Log(sERROR,__func__,"The list couldn't be created for the test");
		return ERRC_FATAL;
	}
	aux_int = INT_MAX;
	if(LinkedListPush(list,&aux_int) != ERRC_OK) {
		Log(sERROR,__func__,"The list couldn't store the element [%d]",aux_int);
		LinkedListFinalize(list);
		return ERRC_FATAL;
	}

	if((res_ptr = LinkedListPeek(list)) == NULL || *(int*)res_ptr != aux_int) {
		Log(sERROR,__func__,"Couldn't get the value from the first element");
		LinkedListFinalize(list);
		return ERRC_FATAL;
	}
	free(res_ptr);
	LinkedListFinalize(list);

	// ulong
	DefLogDebug("Beginning Peek Test with Unsigned Long as Data Type");
	if((list = LinkedListCreate(sizeof(unsigned long))) == NULL) {
		Log(sERROR,__func__,"The list couldn't be created for the test");
		LinkedListFinalize(list);
		return ERRC_FATAL;
	}
	aux_long = ULONG_MAX;
	if(LinkedListPush(list,&aux_long) != ERRC_OK) {
		Log(sERROR,__func__,"The list couldn't store the element [%d]",aux_long);
		LinkedListFinalize(list);
		return ERRC_FATAL;
	}

	if((res_ptr = LinkedListPeek(list)) == NULL || *(unsigned long*)res_ptr != aux_long) {
		Log(sERROR,__func__,"Couldn't get the value from the first element");
		LinkedListFinalize(list);
		return ERRC_FATAL;
	}
	free(res_ptr);
	LinkedListFinalize(list);

	// char
	DefLogDebug("Beginning Peek Test with Char as Data Type");
	if((list = LinkedListCreate(sizeof(char))) == NULL) {
		Log(sERROR,__func__,"The list couldn't be created for the test");
		LinkedListFinalize(list);
		return ERRC_FATAL;
	}
	aux_char = CHAR_MAX;
	if(LinkedListPush(list,&aux_char) != ERRC_OK) {
		Log(sERROR,__func__,"The list couldn't store the element [%c]",aux_char);
		LinkedListFinalize(list);
		return ERRC_FATAL;
	}

	if((res_ptr = LinkedListPeek(list)) == NULL) {
		Log(sERROR,__func__,"Invalid value returned from the list");
		LinkedListFinalize(list);
		return ERRC_FATAL;
	}
	if(*(char*)res_ptr != aux_char) {
		Log(sERROR,__func__,"Couldn't get the value from the first element");
		return ERRC_FATAL;
	}

	if(*(char*)res_ptr != aux_char) {
		Log(sERROR,__func__,"");
		LinkedListFinalize(list);
		return ERRC_FATAL;
	}
	free(res_ptr);
	LinkedListFinalize(list);

	// str
	DefLogDebug("Beginning Peek Test with Pointer as Data Type");
	if((list = LinkedListCreate(256)) == NULL) {
		Log(sERROR,__func__,"The list couldn't be created for the test");
		return ERRC_FATAL;
	}
	if((aux_str = malloc(256)) == NULL) {
		Log(sERROR,__func__,"Memory allocation failed for aux_str");
		LinkedListFinalize(list);
	}
	strcpy(aux_str,"Hello World");
	if(LinkedListPush(list,aux_str) != ERRC_OK) {
		Log(sERROR,__func__,"The list couldn't store the element [%s]",aux_str);
		LinkedListFinalize(list);
		free(aux_str);
		return ERRC_FATAL;
	}

	if((res_ptr = LinkedListPeek(list)) == NULL || strcmp(res_ptr,aux_str)) {
		Log(sERROR,__func__,"Couldn't get the value of the first element");
		LinkedListFinalize(list);
		return ERRC_FATAL;
	}
	free(aux_str);
	free(res_ptr);
	LinkedListFinalize(list);

	DefLogDebug("Beginning Peek Test with Invalid Data");
	if((list = LinkedListCreate(sizeof(void*))) == NULL) {
		Log(sERROR,__func__,"The list couldn't be created for the test");
		return ERRC_FATAL;
	}

	if(LinkedListPush(list,NULL) == ERRC_OK) {
		Log(sERROR,__func__,"The list stored a null element");
		LinkedListFinalize(list);
		return ERRC_FATAL;
	}
	if((res_ptr = LinkedListPeek(list)) != NULL) {
		Log(sERROR,__func__,"Invalid value returned from the list: %p",res_ptr);
		LinkedListFinalize(list);
		return ERRC_FATAL;
	}
	LinkedListFinalize(list);

	return ERRC_OK;
}

static int TestListPushAt(void) {
	LinkedList* list;
	int aux_int;
	unsigned long aux_long;
	char aux_char;
	char* aux_str;

	// int
	DefLogDebug("Beginning Push-At Test with Int as Data Type");
	if((list = LinkedListCreate(sizeof(int))) == NULL) {
		Log(sERROR,__func__,"The list couldn't be created for the test");
		return ERRC_FATAL;
	}

	aux_int = INT_MAX;
	if(LinkedListPushAt(list,&aux_int,0) != ERRC_OK) {
		Log(sERROR,__func__,"The list couldn't store the element [%d]",aux_int);
		LinkedListFinalize(list);
		return ERRC_FATAL;
	}

	for(int idx = 0; idx < STRSS_ITERATION/10; idx++) {
		aux_int = idx%2 == 0? INT_MAX : INT_MIN;
		if(LinkedListPushAt(list,&aux_int,idx%(STRSS_ITERATION/10)) != ERRC_OK) {
			Log(sERROR,__func__,"The list couldn't store the element [%d]",aux_int);
			LinkedListFinalize(list);
			return ERRC_FATAL;
		}
	}
	LinkedListFinalize(list);

	// ulong
	DefLogDebug("Beginning Push-At Test with Unsigned Long as Data Type");
	if((list = LinkedListCreate(sizeof(unsigned long))) == NULL) {
		Log(sERROR,__func__,"The list couldn't be created for the test");
		LinkedListFinalize(list);
		return ERRC_FATAL;
	}

	aux_long = ULONG_MAX;
	if(LinkedListPushAt(list,&aux_long,0) != ERRC_OK) {
		Log(sERROR,__func__,"The list couldn't store the element [%d]",aux_long);
		return ERRC_FATAL;
	}
	for(int idx = 0; idx < STRSS_ITERATION/10; idx++) {
		aux_long = idx%2 == 0? ULONG_MAX : 0;
		if(LinkedListPushAt(list,&aux_long,idx%(STRSS_ITERATION/10)) != ERRC_OK) {
			Log(sERROR,__func__,"The list couldn't store the element [%d]",aux_int);
			LinkedListFinalize(list);
			return ERRC_FATAL;
		}
	}
	LinkedListFinalize(list);

	// char
	DefLogDebug("Beginning Push Test with Char as Data Type");
	if((list = LinkedListCreate(sizeof(char))) == NULL) {
		Log(sERROR,__func__,"The list couldn't be created for the test");
		LinkedListFinalize(list);
		return ERRC_FATAL;
	}

	aux_char = CHAR_MAX;
	if(LinkedListPushAt(list,&aux_char,0) != ERRC_OK) {
		Log(sERROR,__func__,"The list couldn't store the element [%d]",aux_int);
		LinkedListFinalize(list);
		return ERRC_FATAL;
	}


	for(int idx = 0; idx < STRSS_ITERATION/10; idx++) {
		aux_char = idx%2 == 0? CHAR_MAX : CHAR_MIN;
		if(LinkedListPushAt(list,&aux_char,idx%(STRSS_ITERATION/10)) != ERRC_OK) {
			Log(sERROR,__func__,"The list couldn't store the element [%d]",aux_char);
			LinkedListFinalize(list);
			return ERRC_FATAL;
		}
	}
	LinkedListFinalize(list);

	// str
	DefLogDebug("Beginning Push Test with Pointer as Data Type");
	if((list = LinkedListCreate(256)) == NULL) {
		Log(sERROR,__func__,"The list couldn't be created for the test");
		return ERRC_FATAL;
	}
	if((aux_str = malloc(256)) == NULL) {
		Log(sERROR,__func__,"Memory allocation failed for aux_str");
		LinkedListFinalize(list);
	}
	strcpy(aux_str,"Hello World");

	if(LinkedListPushAt(list,aux_str,0) != ERRC_OK) {
		Log(sERROR,__func__,"The list coulnd't store the element [%s]",aux_str);
		LinkedListFinalize(list);
		free(aux_str);
		return ERRC_FATAL;
	}

	for(int idx = 0; idx < STRSS_ITERATION/10; idx++) {
		if(LinkedListPushAt(list,aux_str,idx%(STRSS_ITERATION/10)) != ERRC_OK) {
			Log(sERROR,__func__,"The list coulnd't store the element [%s]",aux_str);
			LinkedListFinalize(list);
			free(aux_str);
			return ERRC_FATAL;
		}
	}
	free(aux_str);
	LinkedListFinalize(list);

	// null
	DefLogDebug("Beginning Push Test with Invalid Data");
	if((list = LinkedListCreate(sizeof(void*))) == NULL) {
		Log(sERROR,__func__,"The list couldn't be created for the test");
		return ERRC_FATAL;
	}

#ifndef WARNING
	for(int idx = 0; idx < STRSS_ITERATION/10; idx++) {
		if(LinkedListPushAt(list,NULL,idx%(STRSS_ITERATION/10)) == ERRC_OK) {
			Log(sERROR,__func__,"The list stored a null element");
			LinkedListFinalize(list);
			return ERRC_FATAL;
		}
	}
#endif
	LinkedListFinalize(list);

	return ERRC_OK;
}

static int TestListPush(void) {
	LinkedList* list;
	int aux_int;
	unsigned long aux_long;
	char aux_char;
	char* aux_str;

	// int
	DefLogDebug("Beginning Push Test with Int as Data Type");
	if((list = LinkedListCreate(sizeof(int))) == NULL) {
		Log(sERROR,__func__,"The list couldn't be created for the test");
		return ERRC_FATAL;
	}
	aux_int = INT_MAX;
	if(LinkedListPush(list,&aux_int) != ERRC_OK) {
		Log(sERROR,__func__,"The list couln't store the element [%d]",aux_int);
		LinkedListFinalize(list);
		return ERRC_FATAL;
	}
	aux_int = INT_MIN;
	if(LinkedListPush(list,&aux_int) != ERRC_OK) {
		Log(sERROR,__func__,"The list couln't store the element [%d]",aux_int);
		LinkedListFinalize(list);
		return ERRC_FATAL;
	}
	for(int idx = 0; idx < STRSS_ITERATION/5; idx++) {
		aux_int = idx%2 == 0? INT_MAX : INT_MIN;
		if(LinkedListPush(list,&aux_int) != ERRC_OK) {
			Log(sERROR,__func__,"The list couln't store the element [%d]",aux_int);
			LinkedListFinalize(list);
			return ERRC_FATAL;
		}
	}
	LinkedListFinalize(list);

	// ulong
	DefLogDebug("Beginning Push Test with Unsigned Long as Data Type");
	if((list = LinkedListCreate(sizeof(unsigned long))) == NULL) {
		Log(sERROR,__func__,"The list couldn't be created for the test");
		LinkedListFinalize(list);
		return ERRC_FATAL;
	}
	aux_long = ULONG_MAX;
	if(LinkedListPush(list,&aux_long) != ERRC_OK) {
		Log(sERROR,__func__,"The list couldn't store the element [%d]",aux_int);
		LinkedListFinalize(list);
		return ERRC_FATAL;
	}
	aux_long = 0;
	if(LinkedListPush(list,&aux_long) != ERRC_OK) {
		Log(sERROR,__func__,"The list couldn't store the element [%d]",aux_int);
		LinkedListFinalize(list);
		return ERRC_FATAL;
	}
	for(int idx = 0; idx < STRSS_ITERATION/5; idx++) {
		aux_long = idx%2 == 0? ULONG_MAX : 0;
		if(LinkedListPush(list,&aux_long) != ERRC_OK) {
			Log(sERROR,__func__,"The list couldn't store the element [%d]",aux_long);
			LinkedListFinalize(list);
			return ERRC_FATAL;
		}
	}
	LinkedListFinalize(list);

	// char
	DefLogDebug("Beginning Push Test with Char as Data Type");
	if((list = LinkedListCreate(sizeof(char))) == NULL) {
		Log(sERROR,__func__,"The list couldn't be created for the test");
		LinkedListFinalize(list);
		return ERRC_FATAL;
	}
	aux_char = CHAR_MAX;
	if(LinkedListPush(list,&aux_char) != ERRC_OK) {
		Log(sERROR,__func__,"The list couldn't store the element [%d]",aux_char);
		LinkedListFinalize(list);
		return ERRC_FATAL;
	}
	aux_char = CHAR_MIN;
	if(LinkedListPush(list,&aux_char) != ERRC_OK) {
		Log(sERROR,__func__,"The list couldn't store the element [%d]",aux_char);
		LinkedListFinalize(list);
		return ERRC_FATAL;
	}
	for(int idx = 0; idx < STRSS_ITERATION/5; idx++) {
		aux_char = idx%2 == 0? CHAR_MAX : CHAR_MIN;
		if(LinkedListPush(list,&aux_char) != ERRC_OK) {
			Log(sERROR,__func__,"The list couldn't store the element [%d]",aux_char);
			LinkedListFinalize(list);
			return ERRC_FATAL;
		}
	}
	LinkedListFinalize(list);

	// str
	DefLogDebug("Beginning Push Test with Pointer as Data Type");
	if((list = LinkedListCreate(256)) == NULL) {
		Log(sERROR,__func__,"The list couldn't be created for the test");
		return ERRC_FATAL;
	}
	if((aux_str = malloc(256)) == NULL) {
		Log(sERROR,__func__,"Memory allocation failed for aux_str");
		LinkedListFinalize(list);
	}

	strcpy(aux_str,"Hello World");
	if(LinkedListPush(list,aux_str) != ERRC_OK) {
		Log(sERROR,__func__,"The list couldn't store the element [%s]",aux_str);
		LinkedListFinalize(list);
		free(aux_str);
		return ERRC_FATAL;
	}
	for(int idx = 0; idx < STRSS_ITERATION/5; idx++) {
		if(LinkedListPush(list,aux_str) != ERRC_OK) {
			Log(sERROR,__func__,"The list couldn't store the element [%s]",aux_str);
			LinkedListFinalize(list);
			free(aux_str);
			return ERRC_FATAL;
		}
	}
	free(aux_str);
	LinkedListFinalize(list);

	// null
	DefLogDebug("Beginning Push Test with Invalid Data");
	if((list = LinkedListCreate(sizeof(void*))) == NULL) {
		Log(sERROR,__func__,"The list couldn't be created for the test");
		return ERRC_FATAL;
	}
	if(LinkedListPush(list,NULL) == ERRC_OK) {
		Log(sERROR,__func__,"The list stored a null element");
		LinkedListFinalize(list);
		return ERRC_FATAL;
	}
	LinkedListFinalize(list);

	return ERRC_OK;
}

static int TestListCreate(void) {
	LinkedList* list;

	DefLogDebug("Beginning Create Test with Int as Data Type");
	list = LinkedListCreate(sizeof(int));
	if(list == NULL) {
		Log(sERROR,__func__,"The list couldn't be created with data_size of [%ld]",sizeof(int));
		return ERRC_FATAL;
	}
	LinkedListFinalize(list);

	DefLogDebug("Beginning Create Test with Char as Data Type");
	list = LinkedListCreate(sizeof(char));
	if(list == NULL) {
		Log(sERROR,__func__,"The list couldn't be created with data_size of [%ld]",sizeof(char));
		return ERRC_FATAL;
	}
	LinkedListFinalize(list);

	DefLogDebug("Beginning Create Test with String as Data Type");
	list = LinkedListCreate(sizeof(char*));
	if(list == NULL) {
		Log(sERROR,__func__,"The list couldn't be created with data_size of [%ld]",sizeof(char*));
		return ERRC_FATAL;
	}
	LinkedListFinalize(list);

	DefLogDebug("Beginning Create Test with Pointer as Data Type");
	list = LinkedListCreate(sizeof(void*));
	if(list == NULL) {
		Log(sERROR,__func__,"The list couldn't be created with data_size of [%ld]",sizeof(int*));
		return ERRC_FATAL;
	}
	LinkedListFinalize(list);

	DefLogDebug("Beginning Create Test with 1 as Data Type");
	list = LinkedListCreate(1);
	if(list == NULL) {
		Log(sERROR,__func__,"The list couldn't be created with data_size of [%ld]",1);
		return ERRC_FATAL;
	}
	LinkedListFinalize(list);

	DefLogDebug("Beginning Create Test with Edge Cases");
	list = LinkedListCreate(0);
	if(list != NULL) {
		Log(sERROR,__func__,"The list couldn't be created with data_size of [%ld]",0);
		return ERRC_FATAL;
	}
	LinkedListFinalize(list);

	list = LinkedListCreate(-1);
	if(list == NULL) {
		Log(sERROR,__func__,"The list couldn't be created with data_size of [%ld]",-1);
		return ERRC_FATAL;
	}
	LinkedListFinalize(list);

	list = LinkedListCreate(INT_MAX);
	if(list == NULL) {
		Log(sERROR,__func__,"The list couldn't be created with data_size of [%ld]",INT_MAX);
		return ERRC_FATAL;
	}
	LinkedListFinalize(list);

	list = LinkedListCreate(LONG_MAX);
	if(list == NULL) {
		Log(sERROR,__func__,"The list couldn't be created with data_size of [%ld]",LONG_MAX);
		return ERRC_FATAL;
	}
	LinkedListFinalize(list);

	list = LinkedListCreate(ULONG_MAX);
	if(list == NULL) {
		Log(sERROR,__func__,"The list couldn't be created with data_size of [%ld]",ULONG_MAX);
		return ERRC_FATAL;
	}
	LinkedListFinalize(list);

	list = LinkedListCreate(ULLONG_MAX);
	if(list == NULL) {
		Log(sERROR,__func__,"The list couldn't be created with data_size of [%ld]",ULONG_MAX);
		return ERRC_FATAL;
	}
	LinkedListFinalize(list);

	return ERRC_OK;
}

int main(void) {
	int result;

	printf("\n\n");
	printf("************ Initializing LinkedList Test... ************\n");
	printf("      ******** LinkedList Creation Test... ********\n");

	if((result = TestListCreate()) != ERRC_OK) {
		printf("[\033[32mFAILED\033[37m]  |  LinkedList creation test failed with error code: %d",result);
	} else {
		printf("[\033[32m  OK  \033[37m]  |  LinkedList creation test passed successfully.\n");
	}

	if((result = TestListPush()) != ERRC_OK) {
		printf("[\033[32mFAILED\033[37m]  |  LinkedList push test failed with error code: %d\n",result);
	} else {
		printf("[\033[32m  OK  \033[37m]  |  LinkedList push test passed successfully.\n");
	}

	if((result = TestListPushAt()) != ERRC_OK) {
		printf("[\033[32mFAILED\033[37m]   |  LinkedList push-at test failed with error code: %d\n",result);
	} else {
		printf("[\033[32m  OK  \033[37m]   |  LinkedList push-at test passed successfully.\n");
	}

	if((result = TestListPeek()) != ERRC_OK) {
		printf("[\033[32mFAILED\033[37m]   |  LinkedList peek test failed with error code: %d\n",result);
	} else {
		printf("[\033[32m  OK  \033[37m]   |  LinkedList peek test passed successfully.\n");
	}

	if((result = TestListPeekAt()) != ERRC_OK) {
		printf("[\033[32mFAILED\033[37m]   |  LinkedList peek test failed with error code: %d\n",result);
	} else {
		printf("[\033[32m  OK  \033[37m]   |  LinkedList peek test passed successfully.\n");
	}

	if((result = TestListPop()) != ERRC_OK) {
		printf("[\033[32mFAILED\033[37m]   |  LinkedList pop test failed with error code: %d\n",result);
	} else {
		printf("[\033[32m  OK  \033[37m]   |  LinkedList pop test passed successfully.\n");
	}

	if((result = TestListPopAt()) != ERRC_OK) {
		printf("[\033[32mFAILED\033[37m]   |  LinkedList pop-at test failed with error code: %d\n",result);
	} else {
		printf("[\033[32m  OK  \033[37m]   |  LinkedList pop-at test passed successfully.\n");
	}

	if((result = TestListSize()) != ERRC_OK) {
		printf("[\033[32mFAILED\033[37m]   |  LinkedList size test failed with error code: %d\n",result);
	} else {
		printf("[\033[32m  OK  \033[37m]   |  LinkedList size test passed successfully.\n");
	}

	printf("************  Finalizing LinkedList Test...  ************\n");
	printf("\n\n");
	return result;
}
