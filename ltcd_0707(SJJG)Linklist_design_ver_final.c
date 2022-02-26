#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
// 如果一直addtail，那就会每次都遍历一遍，addtail n次就会花 n(n+1)/2 的时间
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
    L->count = -1;              // count 初始要为负一，因为第一个节点的index是零，这样才能对应
    L->head = NULL;             //创建一个头部，其中有两个指针，一个用于指向第一个节点，一个用于指向最后一个
    L->tail = NULL;
    return L;
}
void addWhileEmpty(MyLinkedList* obj, int val) {
    MyNode* newnode = (MyNode*)malloc(sizeof(MyNode));
    newnode->num = val;                //向空链表里加元素，无论是addHead还是addTail，空的时候都一样。
    newnode->next = NULL;
    obj->head = newnode;
    obj->tail = newnode;           //head tail一样
}
void myLinkedListAddAtHead(MyLinkedList* obj, int val) {
    if (obj->head == NULL) {
        addWhileEmpty(obj, val);        //向空链加，
    }
    else {
        MyNode* newnode = (MyNode*)malloc(sizeof(MyNode));
        newnode->num = val;
        newnode->next = obj->head;
        obj->head = newnode;            //从头加不需要调整tail指针。
    }
    obj->count++;
}
void myLinkedListAddAtTail(MyLinkedList* obj, int val) {  
    if (obj->head == NULL) {
        addWhileEmpty(obj, val);        //向空链加，
    }
    else {
        MyNode* newnode = (MyNode*)malloc(sizeof(MyNode));
        newnode->num = val;
        newnode->next = NULL;
        MyNode* tmp = obj->tail;        //这时候把tail指向的最后一个节点的位置拿出来，
        tmp->next = newnode;            //它的next指向新节点，就不用遍历了。
        obj->tail = newnode;            //让tail指向新的尾节点。
    }obj->count++;
}
MyNode* goToIndex(MyLinkedList* obj, int index) {
    MyNode* pos = obj->head;            //无论是get，delete add_at 都需要跳到中间的某个节点。
    int i = 0;                          // 这些重复的部分就用个函数解决。
    while (i < index) {
        pos = pos->next;
        i++;
    }
    return pos;
}
int myLinkedListGet(MyLinkedList* obj, int index) {
    if (index > obj->count || index < 0)        //index要取在linklist的长度范围内
        return -1;
    MyNode* tmp = goToIndex(obj, index);        //get谁就去谁的位置。
    return tmp->num;
}
void myLinkedListAddAtIndex(MyLinkedList* obj, int index, int val) {
    if (index > obj->count + 1)                    //题目中是在 --第index个-- 节点《之前》加节点，所以右边界是count+1  
        return;                                                 
    else if (index <= 0)                        //题目规定index非正，就加头部
        myLinkedListAddAtHead(obj, val);
    else if (index == obj->count + 1)           //在count+1个之前加，就等于在末尾加。
        myLinkedListAddAtTail(obj, val);
    else {
        MyNode* newnode = (MyNode*)malloc(sizeof(MyNode));//否则就在中间加咯
        newnode->num = val;
        newnode->next = NULL;
        MyNode* tmp = goToIndex(obj, index - 1);        //去 index之前的那个节点才能插入
        newnode->next = tmp->next;
        tmp->next = newnode;
        obj->count++;
    }
}
void myLinkedListDeleteAtIndex(MyLinkedList* obj, int index) {
    if (index > obj->count || index < 0)        //边界情况。
        return;
    MyNode* tmp = NULL;                     //只有删尾，会改变tail节点的位置。
    MyNode* p = NULL;
    if (index == 0) {                           //删头，需要改head指向的节点。
        tmp = obj->head;                        //当链表就一个节点的时候，头就是尾。
        obj->head = tmp->next;                  //删了后，tail节点需要改成NULL，但这个放在最后改
    }
    else {                                      //不在头部，时，去第index个节点之前的节点。
        p = goToIndex(obj, index - 1);          
        tmp = p->next;
        p->next = tmp->next;                    //
    }
    free(tmp);                                  //删了后要free掉malloc的空间
    obj->count--;
    if (index == (obj->count) + 1) {            // 判断删的地方是否在尾部。因为这时候count减一了，所以加回去一下
        obj->tail = p;                      //把尾节点改成, 新的，最后一个节点，也就是index-1的那个节点。这个我们已求过了
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