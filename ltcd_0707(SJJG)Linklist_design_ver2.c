#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
typedef struct MyLinkedList {
    int val;
    struct MyLinkedList* next;
} MyLinkedList;
MyLinkedList* myLinkedListCreate() {
    MyLinkedList* L = (MyLinkedList*)malloc(sizeof(MyLinkedList));
    L->val = -1;
    L->next = NULL;
    return L;
}
void myLinkedListAddAtHead(MyLinkedList* obj, int num) {
    MyLinkedList* newl = (MyLinkedList*)malloc(sizeof(MyLinkedList));
    newl->val = num;
    newl->next = obj->next;
    obj->next = newl;
    obj->val++;
}
void myLinkedListAddAtTail(MyLinkedList* obj, int num) {
    if (obj->val == -1) {
        myLinkedListAddAtHead(obj, num);
    }
    else {
        MyLinkedList* tmp = obj->next;
        MyLinkedList* newl = (MyLinkedList*)malloc(sizeof(MyLinkedList));
        newl->val = num;
        newl->next = NULL;
        while (tmp->next) {
            tmp = tmp->next;
        }
        tmp->next = newl;
        obj->val++;
    }
}
int myLinkedListGet(MyLinkedList* obj, int index) {
    if (index < 0 || obj->val < 0 || obj->val < index) {
        return -1;
    }
    MyLinkedList* tmp = obj->next;
    int i = 0;
    while (index != i) {
        tmp = tmp->next;
        i++;
    }
    return tmp->val;
}
void myLinkedListAddAtIndex(MyLinkedList* obj, int index, int num) {
    if (index == (obj->val + 1)) {
        myLinkedListAddAtTail(obj, num);
    }
    else if (index > (obj->val + 1))
        return;
    else {
        MyLinkedList* p = obj;
        int i = 0;
        while (i < index) {
            p = p->next;
            i++;
        }
        myLinkedListAddAtHead(p, num);
        p->val--;
        obj->val++;
    }
}
void myLinkedListDeleteAtIndex(MyLinkedList* obj, int index) {
    if ((index > obj->val) || index < 0)
        return;
    else {
        MyLinkedList* tmp = obj;
        int i = 0;
        while (i < index) {
            tmp = tmp->next;
            i++;
        }
        MyLinkedList* pos = tmp->next;
        tmp->next = pos->next;
        free(pos);
        obj->val--;
    }
}
void myLinkedListFree(MyLinkedList* obj) {
    while (obj) {
        MyLinkedList* tmp = obj;
        obj = obj->next;
        free(tmp);
    }
}
void outlist(MyLinkedList* obj) {
    MyLinkedList* tmp = obj->next;
    while (tmp) {
        printf("[%d|-]->", tmp->val);
        tmp = tmp->next;
    }
    printf("\n");
}
void test0() {
    MyLinkedList* list = myLinkedListCreate();
    myLinkedListAddAtHead(list, 7);
    myLinkedListAddAtHead(list, 2);
    myLinkedListAddAtHead(list, 1);
    outlist(list);

    myLinkedListAddAtIndex(list, 3, 0);      outlist(list);

    myLinkedListDeleteAtIndex(list, 2);      outlist(list);
    myLinkedListAddAtHead(list, 6);
    myLinkedListAddAtTail(list, 4);      outlist(list);
    printf("\n%d", myLinkedListGet(list, 4));
    myLinkedListAddAtHead(list, 4);
    myLinkedListAddAtIndex(list, 5, 0);      outlist(list);
    myLinkedListAddAtHead(list, 6);      outlist(list);

}
void test1() {
    MyLinkedList* list = myLinkedListCreate();
    myLinkedListAddAtHead(list, 1);
    myLinkedListAddAtTail(list, 3);
    myLinkedListAddAtIndex(list, 1, 2);
    outlist(list);
    printf("%d\n", myLinkedListGet(list, 1));
    myLinkedListDeleteAtIndex(list, 1);
    outlist(list);
    printf("%d\n", myLinkedListGet(list, 1));
}
int main() {
    test1();
    return 0;
}
