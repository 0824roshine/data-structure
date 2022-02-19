#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#define base 769
struct List
{
	int value;
	int key;
	struct List* next;
};
typedef struct {
	struct List* data;
} MyHashMap;
int hash(int key) {
	return key % base;
}
struct List* listContain(struct List* head, int key) {
	for (struct List* pos = head; pos->next; pos = pos->next) {
		if (pos->next->key == key)
			return pos->next;
	}
	return NULL;
}
void listPush(struct List* head, int key, int value)  //
{
	struct List* tmp = malloc(sizeof(struct List));  //push时要malloc
	tmp->key = key;
	tmp->value = value;
	tmp->next = head->next;  //这里插入可能是从中间插入，而不一定是末尾
	head->next = tmp;
}
void listDelete(struct List* head, int pKey)
{
	for (struct List* pos = head; pos->next; pos = pos->next) {
		if (pos->next->key == pKey) {
			struct List* tmp = pos->next;  //这里用for？
			pos->next = tmp->next;
			free(tmp);
			break;
		}
	}
}
void listFree(struct List* head)  // 这里是释放，所以可以用while
{
	while (head->next) {
		struct List* tmp = head->next;
		head->next = tmp->next;
		free(tmp);
	}
}
MyHashMap* myHashMapCreate() {		// 为什么没有强制类型转化，为什么要定义成自定义类型呢？
	MyHashMap* ret = malloc(sizeof(MyHashMap));
	ret->data = malloc(sizeof(struct List) * base); //总共要malloc base+1次
	for (int i = 0; i < base; i++) {    //这里一定要从头开始引用结构
		ret->data[i].value = 0;
		ret->data[i].key = 0;
		ret->data[i].next = NULL;
	}
	return ret;
}
void myHashMapPut(MyHashMap* obj, int key, int Value) {
	int h = hash(key);
	struct List* tmp = listContain(&(obj->data[h]), key);
	if (tmp == NULL) {
		listPush(&(obj->data[h]), key, Value);
	}
	else {
		tmp->value = Value;
	}
}
int myHashMapGet(MyHashMap* obj, int key) {
	int h = hash(key);
	struct List* tmp = listContain(&(obj->data[h]), key);
	if (tmp == NULL) {
		return -1;
	}
	else {
		return tmp->value;
	}
}
void myHashMapRemove(MyHashMap* obj, int key) {
	int h = hash(key);
	listDelete(&(obj->data[h]), key);
}
void myHashMapFree(MyHashMap* obj) {
	for (int i = 0; i < base; i++) {
		listFree(&(obj->data[i]));
	}
	free(obj->data);
}

/**
 * Your MyHashMap struct will be instantiated and called as such:
 * MyHashMap* obj = myHashMapCreate();
 * myHashMapPut(obj, key, value);

 * int param_2 = myHashMapGet(obj, key);

 * myHashMapRemove(obj, key);

 * myHashMapFree(obj);
*/