#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "hashmap.h"

#define DEFAULT_ARRAY_LENGTH	(20)

static size_t hash_function(const char* key); 

int main(void)
{
	size_t i = 0; 
	hashmap_t* hashmap = NULL; 
	
	hashmap = init_hashmap_malloc(DEFAULT_ARRAY_LENGTH, hash_function);

	for (i = 0; i < 100; i++) {
		char key[100]; 
		int value = (int)i;
		int c; 
		int dummy = 512; 

		sprintf(key, "key%u", i);
		assert(add_key(hashmap, key, value) == TRUE);

		c = get_value(hashmap, key); 
		assert(c == value); 

		assert(add_key(hashmap, key, dummy) == FALSE); 
		c = get_value(hashmap, key); 
		assert(c == value);
	}

	printf("test1 complete\n");

	for (i = 0; i < 100; i++) {
		char key[100];
		int c; 
		
		sprintf(key, "key%u", i);
		assert(remove_key(hashmap, key) == TRUE); 

		c = get_value(hashmap, key); 
		assert(c == -1); 
		assert(remove_key(hashmap, key) == FALSE); 
	}

	printf("test2 complete\n");

	for (i = 0; i < DEFAULT_ARRAY_LENGTH; i++) {
		assert((hashmap->plist)[i] == NULL); 
	}

	destroy(hashmap); 

	printf("test3 complete\n");

	return 0;
}

static size_t hash_function(const char* key)
{
	size_t code = 0;
	const char* c = key; 

	while (*c != '\0') {
		code += *c++;
	}

	return code; 
}