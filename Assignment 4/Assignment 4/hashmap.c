#define _CRT_SECURE_NO_WARNINGS

#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "hashmap.h"

hashmap_t* init_hashmap_malloc(size_t length, size_t(*p_hash_func)(const char* key))
{
	int i = 0;
	hashmap_t* hashmap = malloc(sizeof(hashmap_t));
	memset(hashmap, 0, sizeof(hashmap_t));

	hashmap->hash_func = p_hash_func;
	hashmap->length = length;
	
	hashmap->plist = malloc(sizeof(node_t) * length);
	memset(hashmap->plist, 0, sizeof(node_t) * length);

	return hashmap;
}

int add_key(hashmap_t* hashmap, const char* key, const int value)
{
	node_t** cur_node;
	size_t hash_key;

	assert(hashmap != NULL);

	hash_key = hashmap->hash_func(key) % hashmap->length;

	cur_node = &hashmap->plist[hash_key];
	while (*cur_node != NULL) {
		if (strcmp((*cur_node)->key, key) == 0) {
			return FALSE;
		}

		cur_node = &(*cur_node)->next;
	}

	*cur_node = malloc(sizeof(node_t));
	(*cur_node)->key = key;
	(*cur_node)->value = value;
	(*cur_node)->next = NULL;

	return TRUE;
}

int get_value(const hashmap_t* hashmap, const char* key)
{
	node_t** cur_node; 
	size_t hash_key; 

	assert(hashmap != NULL);
	
	hash_key = hashmap->hash_func(key) % hashmap->length;

	cur_node = &(hashmap->plist[hash_key]);
	while (*cur_node != NULL) {
		if (strcmp((*cur_node)->key, key) == 0) {
			return (*cur_node)->value;
		}

		cur_node = &(*cur_node)->next;
	}

	return -1;
}

int update_value(hashmap_t* hashmap, const char* key, int value)
{
	node_t** cur_node; 
	size_t hash_key;

	assert(hashmap != NULL);

	hash_key = hashmap->hash_func(key) % hashmap->length;

	cur_node = &(hashmap->plist[hash_key]);
	while (*cur_node != NULL) {
		if (strcmp((*cur_node)->key, key) == 0) {
			(*cur_node)->value = value;
			return TRUE;
		}

		cur_node = &(*cur_node)->next;
	}

	return FALSE;
}

int remove_key(hashmap_t* hashmap, const char* key)
{
	node_t** cur_node;
	size_t hash_key; 

	assert(hashmap != NULL);

	hash_key = hashmap->hash_func(key) % hashmap->length; 

	cur_node = &(hashmap->plist[hash_key]); 
	while (*cur_node != NULL) {
		if (strcmp((*cur_node)->key, key) == 0) {
			node_t* tmp_node = *cur_node;
			cur_node = (*cur_node)->next;
			free(tmp_node); 
			
			return TRUE;
		}

		cur_node = &(*cur_node)->next;
	}

	return FALSE;
}

void destroy(hashmap_t* hashmap)
{
	int i = 0;
	for (i = 0; i < (hashmap->length); i++) {
		if (hashmap->plist[i] != NULL) {
			free(hashmap->plist[i]);
		}
	}

	free(hashmap->plist);
}