#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
// ���һֱaddtail���Ǿͻ�ÿ�ζ�����һ�飬addtail n�ξͻỨ n(n+1)/2 ��ʱ��
typedef struct MyNode {
    int num;
    struct MyNode* next;
}MyNode;
typedef struct MyList {
    int count;
    struct MyNode* head;
    struct MyNode* tail;
}MyLinkedList;
MyLinkedList* myLinkedListCreate() {
    MyLinkedList* L = (MyLinkedList*)malloc(sizeof(MyLinkedList));
    L->count = -1;              // count ��ʼҪΪ��һ����Ϊ��һ���ڵ��index���㣬�������ܶ�Ӧ
    L->head = NULL;             //����һ��ͷ��������������ָ�룬һ������ָ���һ���ڵ㣬һ������ָ�����һ��
    L->tail = NULL;
    return L;
}
void addWhileEmpty(MyLinkedList* obj, int val) {
    MyNode* newnode = (MyNode*)malloc(sizeof(MyNode));
    newnode->num = val;                //����������Ԫ�أ�������addHead����addTail���յ�ʱ��һ����
    newnode->next = NULL;
    obj->head = newnode;
    obj->tail = newnode;           //head tailһ��
}
void myLinkedListAddAtHead(MyLinkedList* obj, int val) {
    if (obj->head == NULL) {
        addWhileEmpty(obj, val);        //������ӣ�
    }
    else {
        MyNode* newnode = (MyNode*)malloc(sizeof(MyNode));
        newnode->num = val;
        newnode->next = obj->head;
        obj->head = newnode;            //��ͷ�Ӳ���Ҫ����tailָ�롣
    }
    obj->count++;
}
void myLinkedListAddAtTail(MyLinkedList* obj, int val) {  
    if (obj->head == NULL) {
        addWhileEmpty(obj, val);        //������ӣ�
    }
    else {
        MyNode* newnode = (MyNode*)malloc(sizeof(MyNode));
        newnode->num = val;
        newnode->next = NULL;
        MyNode* tmp = obj->tail;        //��ʱ���tailָ������һ���ڵ��λ���ó�����
        tmp->next = newnode;            //����nextָ���½ڵ㣬�Ͳ��ñ����ˡ�
        obj->tail = newnode;            //��tailָ���µ�β�ڵ㡣
    }obj->count++;
}
MyNode* goToIndex(MyLinkedList* obj, int index) {
    MyNode* pos = obj->head;            //������get��delete add_at ����Ҫ�����м��ĳ���ڵ㡣
    int i = 0;                          // ��Щ�ظ��Ĳ��־��ø����������
    while (i < index) {
        pos = pos->next;
        i++;
    }
    return pos;
}
int myLinkedListGet(MyLinkedList* obj, int index) {
    if (index > obj->count || index < 0)        //indexҪȡ��linklist�ĳ��ȷ�Χ��
        return -1;
    MyNode* tmp = goToIndex(obj, index);        //get˭��ȥ˭��λ�á�
    return tmp->num;
}
void myLinkedListAddAtIndex(MyLinkedList* obj, int index, int val) {
    if (index > obj->count + 1)                    //��Ŀ������ --��index��-- �ڵ㡶֮ǰ���ӽڵ㣬�����ұ߽���count+1  
        return;                                                 
    else if (index <= 0)                        //��Ŀ�涨index�������ͼ�ͷ��
        myLinkedListAddAtHead(obj, val);
    else if (index == obj->count + 1)           //��count+1��֮ǰ�ӣ��͵�����ĩβ�ӡ�
        myLinkedListAddAtTail(obj, val);
    else {
        MyNode* newnode = (MyNode*)malloc(sizeof(MyNode));//��������м�ӿ�
        newnode->num = val;
        newnode->next = NULL;
        MyNode* tmp = goToIndex(obj, index - 1);        //ȥ index֮ǰ���Ǹ��ڵ���ܲ���
        newnode->next = tmp->next;
        tmp->next = newnode;
        obj->count++;
    }
}
void myLinkedListDeleteAtIndex(MyLinkedList* obj, int index) {
    if (index > obj->count || index < 0)        //�߽������
        return;
    MyNode* tmp = NULL;                     //ֻ��ɾβ����ı�tail�ڵ��λ�á�
    MyNode* p = NULL;
    if (index == 0) {                           //ɾͷ����Ҫ��headָ��Ľڵ㡣
        tmp = obj->head;                        //�������һ���ڵ��ʱ��ͷ����β��
        obj->head = tmp->next;                  //ɾ�˺�tail�ڵ���Ҫ�ĳ�NULL���������������
    }
    else {                                      //����ͷ����ʱ��ȥ��index���ڵ�֮ǰ�Ľڵ㡣
        p = goToIndex(obj, index - 1);          
        tmp = p->next;
        p->next = tmp->next;                    //
    }
    free(tmp);                                  //ɾ�˺�Ҫfree��malloc�Ŀռ�
    obj->count--;
    if (index == (obj->count) + 1) {            // �ж�ɾ�ĵط��Ƿ���β������Ϊ��ʱ��count��һ�ˣ����Լӻ�ȥһ��
        obj->tail = p;                      //��β�ڵ�ĳ�, �µģ����һ���ڵ㣬Ҳ����index-1���Ǹ��ڵ㡣��������������
    }
}
void myLinkedListFree(MyLinkedList* obj) {      //free
    MyNode* tmp = obj->head;
    while (tmp) {
        MyNode* p = tmp;
        tmp = p->next;
        free(p);
    }
    free(obj);
}
void outlist(MyLinkedList* obj) {
    MyNode* tmp = obj->head;
    while (tmp) {
        printf("[%d|-]->", tmp->num);
        tmp = tmp->next;
    }
    printf("\n");
}
void test1() {
    MyLinkedList* list = myLinkedListCreate();
    myLinkedListAddAtHead(list, 1);
    myLinkedListAddAtHead(list, 3);
    myLinkedListAddAtIndex(list, 1, 2);
    outlist(list);
    printf("%d\n", myLinkedListGet(list, 1));
    myLinkedListDeleteAtIndex(list, 1);
    outlist(list);
    printf("%d\n", myLinkedListGet(list, 1));
}
void test2() {
    MyLinkedList* list = myLinkedListCreate();
    myLinkedListAddAtHead(list, 1);
    myLinkedListDeleteAtIndex(list, 0);
}
void test3() {
    MyLinkedList* list = myLinkedListCreate();
    myLinkedListAddAtHead(list, 7); outlist(list);
    myLinkedListAddAtTail(list, 7); outlist(list);
    myLinkedListAddAtHead(list, 9); outlist(list);
    myLinkedListAddAtTail(list, 8);  outlist(list);
    myLinkedListAddAtHead(list, 6);  outlist(list);
    myLinkedListAddAtHead(list, 0); outlist(list);
    printf("%d\n", myLinkedListGet(list, 5));
    myLinkedListAddAtHead(list, 0); outlist(list);
    printf("%d\n", myLinkedListGet(list, 2));
    printf("%d\n", myLinkedListGet(list, 5));
    myLinkedListAddAtTail(list, 4); outlist(list);
}
int main() {
    test3();
    return 0;
}