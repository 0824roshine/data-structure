#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<malloc.h>
#include<errno.h>
typedef struct Node
{
	int data;
	struct Node* next;
}Node,*LinkedList;
LinkedList listinit() {     //   初始化
	Node* L;
	L = (Node*)malloc(sizeof(Node));    
	if (L == NULL) {                    
		printf("%s\n",strerror(errno));
		//exit(0);           
	}
	L->next = NULL;   
	return L;
}
LinkedList LinkedListCrt_From_tail(Node* L)
{
	for (int i = 0; i < 10; i++)
	{
		Node* p = (Node*)malloc(sizeof(Node));
		p->data = i * i;
		p->next = L->next;
		L->next = p;
	}
	return L;
}
LinkedList LinkedListCrt_From_head(Node* L)
{
	Node* tmp = L;
	for (int i = 0; i < 10; i++)
	{
		Node* p = (Node*)malloc(sizeof(Node));
		p->data = i * 2;
		tmp->next = p;
		tmp = p;
	}
	tmp->next = NULL;
	return L;
}
void Print_List(LinkedList L)
{
	Node* p = L->next;
	int i = 0;
	while (p)
	{
		i++;
		printf("第%d个元素为%d\n",i, p->data);
		p = p->next;
	}
}
int main()
{
	{
		Node* Linklist1 = listinit();
		LinkedListCrt_From_tail(Linklist1);
		Print_List(Linklist1);
		free(Linklist1);
		Linklist1 = NULL;
	}
	{
		Node* Linklist2 = listinit();
		LinkedListCrt_From_head(Linklist2);
		Print_List(Linklist2);
		free(Linklist2);
		Linklist2 = NULL;
	}
	return 0;
}