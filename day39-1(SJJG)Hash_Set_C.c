#define _SYSTEM_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<assert.h>
#define base 769
struct List
{
	int value;
	struct List* next;
};
typedef struct
{
	struct List* data;
}MyHashSet;
int hash(int key)
{
	return key % base;
}
int listContain(struct List* head, int p)
{
	struct List* pos = head;
	while (pos->next)
	{
		if (pos->next->value==p)
			return 1;
		pos = pos->next;
	}
	return 0;
}
void listPush(struct List* head, int p)
{
	struct List* tmp = (struct List*)malloc(sizeof(struct List));
		tmp->value = p;
		tmp->next = head->next;
		head->next = tmp;
}
void listDelete(struct List* head, int p)
{
	for (struct List* pos = head; pos->next; pos = pos->next)
	{
		if (pos->next->value == p)
		{
			struct List* tmp = pos->next;
			pos->next = tmp->next;
			free(tmp);
			break;
		}
	}
}
void listFree(struct List* head)
{
	while (head->next)
	{
		struct List* tmp =head->next;
		head->next = tmp->next;
		free(tmp);
	}
}
MyHashSet* myHashSetCreate()
{
	MyHashSet* ret = malloc(sizeof(MyHashSet));
	ret->data = malloc(sizeof(struct List) * base);
	for (int i = 0; i < base; i++)
	{
		ret->data[i].value = 0;
		ret->data[i].next = NULL;
	}
	return ret;
}
void myHashSetAdd(MyHashSet* obj, int key)
{
	int h = hash(key);
	if (!(listContain(&(obj->data[h]), key)))
		listPush(&(obj->data[h]), key);
}
void myHashSetRemove(MyHashSet* obj, int key) 
{
	int h = hash(key);
	listDelete(&(obj->data[h]), key);
}
int myHashSetContains(MyHashSet* obj, int key)
{
	int h = hash(key);
	return listContain(&(obj->data[h]), key);
}
void myHashSetFree(MyHashSet* obj)
{
	for (int i = 0; i < base; i++)
		listFree(&(obj->data[i]));
	free(obj->data);
}

