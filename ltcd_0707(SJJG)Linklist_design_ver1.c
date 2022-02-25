#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
typedef struct MyLinkedList {
    int val;
    struct MyLinkedList* next;
} MyLinkedList;
MyLinkedList* myLinkedListCreate() {
    MyLinkedList* L = (MyLinkedList*)malloc(sizeof(MyLinkedList));
    L->val = 0;
    L->next = NULL;
    return L;
}
int myLinkedListGet(MyLinkedList* obj, int index) {
    if (index < 0 || obj->next == NULL) {
        return -1;
    }
    MyLinkedList* tmp = obj->next;
    for (int i = 0; (i < index) && (tmp); i++) {
        tmp = tmp->next;
    }
    if (tmp)
        return tmp->val;
    return -1;

}
void myLinkedListAddAtHead(MyLinkedList* obj, int val) {
    MyLinkedList* tmp = (MyLinkedList*)malloc(sizeof(MyLinkedList));
    tmp->val = val;
    tmp->next = NULL;
    obj->next;
    if ((obj->next) == NULL) {
        obj->next = tmp;
    }
    else {
        tmp->next = obj->next;
        obj->next = tmp;
    }
}

void myLinkedListAddAtTail(MyLinkedList* obj, int val) {
    MyLinkedList* p = (MyLinkedList*)malloc(sizeof(MyLinkedList));
    p->val = val;
    p->next = NULL;
    MyLinkedList* tmp = obj;
    while (tmp->next) {
        tmp = tmp->next;
    }
    tmp->next = p;
}

void myLinkedListAddAtIndex(MyLinkedList* obj, int index, int val) {
    if (index <= 0)
        myLinkedListAddAtHead(obj, val);
    else {
        MyLinkedList* tmp = obj->next;
        MyLinkedList* p = (MyLinkedList*)malloc(sizeof(MyLinkedList));
        int i = 0;
        if (index > 0 && tmp == NULL)
            return;
        while (tmp->next) {
            if (i == (index - 1)) {
                break;
            }
            else
                tmp = tmp->next;
            i++;
        }
        if (i == (index - 1)) {
            p->val = val;
            p->next = tmp->next;
            tmp->next = p;
        }
    }
}
void myLinkedListDeleteAtIndex(MyLinkedList* obj, int index) {
    MyLinkedList* p = obj->next;
    int i = 0;
    if (index < 0 || obj->next == NULL) {
        return;
    }
    if (index == 0) {
        obj->next = p->next;
        free(p);
        return;
    }
    while (p->next) {
        if (i == index - 1) {
            break;
        }
        i++;
        p = p->next;
    }
    if (i == index - 1 && p->next) {
        MyLinkedList* tmp = p->next;
        p->next = tmp->next;
        free(tmp);
    }
}

void myLinkedListFree(MyLinkedList* obj) {
    while (obj->next) {
        MyLinkedList* tmp = obj->next;
        obj->next = tmp->next;
        free(tmp);
    }
    free(obj);
}
void outlist(MyLinkedList* obj) {
    MyLinkedList* tmp = obj->next;
    while (tmp) {
        printf("[%d|-]->", tmp->val);
        tmp = tmp->next;
    }
    printf("\n");
}
void test1() {
    MyLinkedList* list = myLinkedListCreate();
    myLinkedListAddAtHead(list, 7);
    myLinkedListAddAtHead(list, 2);
    myLinkedListAddAtHead(list, 1);      
    outlist(list);

    myLinkedListAddAtIndex(list, 3, 0);      outlist(list);

    myLinkedListDeleteAtIndex(list, 2);      outlist(list);
    myLinkedListAddAtHead(list, 6);
    myLinkedListAddAtTail(list, 4);      outlist(list);
    printf("\n%d",myLinkedListGet(list, 4));
    myLinkedListAddAtHead(list, 4);
    myLinkedListAddAtIndex(list, 5, 0);      outlist(list);
    myLinkedListAddAtHead(list, 6);      outlist(list);
    
}
void test2() {

    MyLinkedList* list = myLinkedListCreate();
    myLinkedListAddAtIndex(list, 1, 0);
    printf("\n%d", myLinkedListGet(list, 0));
}
void test3() {

    MyLinkedList* list = myLinkedListCreate();
    myLinkedListAddAtHead(list,1);
    myLinkedListAddAtTail(list, 3);  outlist(list);
    myLinkedListAddAtIndex(list, 1, 2);  outlist(list);
    printf("%d\n", myLinkedListGet(list, 1));
    myLinkedListDeleteAtIndex(list, 1);  outlist(list);
    printf("%d\n", myLinkedListGet(list, 1));
}
int main() {
  test1();
    test3();
    return 0;
}

/**
 * Your MyLinkedList struct will be instantiated and called as such:
 * MyLinkedList* obj = myLinkedListCreate();
 * int param_1 = myLinkedListGet(obj, index);

 * myLinkedListAddAtHead(obj, val);

 * myLinkedListAddAtTail(obj, val);

 * myLinkedListAddAtIndex(obj, index, val);

 * myLinkedListDeleteAtIndex(obj, index);

 * myLinkedListFree(obj);
*/