#include <assert.h>
#include <string.h>
#include "hashmap.h"

hashmap_t* init_hashmap_malloc(size_t length, size_t(*p_hash_func)(const char* key))
{
	int i = 0;
	hashmap_t* hashmap = malloc(sizeof(hashmap_t));

	hashmap->hash_func = p_hash_func;
	hashmap->plist = malloc(sizeof(node_t) * length);
	hashmap->length = length;

	for (i = 0; i < length; i++) {
		hashmap->plist[i] = NULL;
	}

	return hashmap;
}
int add_key(hashmap_t* hashmap, const char* key, const int value)
{
	assert(hashmap != NULL); 

	node_t* temp_node;
	size_t hash_key;
	hash_key = hashmap->hash_func(key) % hashmap->length;

	temp_node = hashmap->plist[hash_key];
	while (temp_node != NULL) {
		if (strcmp(temp_node->key, key) == 0) {
			return FALSE;
		}

		temp_node = temp_node->next;
	}

	temp_node = malloc(sizeof(node_t));
	strcpy(temp_node->key, key);
	temp_node->value = value;

	return TRUE;
}

int get_value(const hashmap_t* hashmap, const char* key)
{
	assert(hashmap != NULL);

	node_t* temp_node; 
	size_t hash_key; 
	hash_key = hashmap->hash_func(key) % hashmap->length;

	temp_node = hashmap->plist[hash_key];
	while (temp_node != NULL) {
		if (strcmp(temp_node->key, key) == 0) {
			return temp_node->value;
		}

		temp_node = temp_node->next;
	}

	return -1;
}

int update_value(hashmap_t* hashmap, const char* key, int value)
{
	assert(hashmap != NULL);

	size_t hash_key;
	hash_key = hashmap->hash_func(key);

	if (hashmap->plist[hash_key] != NULL) {
		hashmap->plist[hash_key]->value = value;
	}

	return FALSE;
}

int remove_key(hashmap_t* hashmap, const char* key)
{
	assert(hashmap != NULL); 

	size_t hash_key; 
	hash_key = hashmap->hash_func(key); 

	if (hashmap->plist[hash_key] != NULL) {
		free(hashmap->plist[hash_key]);

		hashmap->plist[hash_key]->key = NULL;
		hashmap->plist[hash_key]->value = 0;

		return TRUE;
	}

	return FALSE;
}

void destroy(hashmap_t* hashmap)
{
	int i = 0;
	for (i = 0; i < (hashmap->length); i++) {
		free(hashmap->plist[i]);
	}

	free(hashmap->plist);
}