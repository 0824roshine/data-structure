#define _CRT_SECURE_NO_WARNINGS
#include<malloc.h>
#include<stdio.h>
struct ListNode {
    int val;
    struct ListNode* next;
}; 
struct ListNode* crt(int n) {
    struct ListNode* head1 = malloc(sizeof(struct ListNode));
    struct ListNode* p = head1;
    for (int i = 0; i < n; i++) {
        struct ListNode* tp = malloc(sizeof(struct ListNode));
        tp->val = (i-2)* (i-4);
        tp->next = NULL;
        p->next = tp;
        p = p->next;
    }
    p = head1->next;
    free(head1);
    return p;
}
struct ListNode* removeElements(struct ListNode* head, int val) {
    struct ListNode* fakehead = malloc(sizeof(struct ListNode));
    fakehead->val = 514;
    fakehead->next = head;
    struct ListNode* tmp = fakehead;
    while (tmp->next) {
        if (tmp->next->val == val) {
            struct ListNode* p = tmp->next;
            tmp->next = p->next;
            free(p);
            continue;
        }
        tmp = tmp->next;
    }
    tmp = fakehead->next;
    free(fakehead);
    return tmp;
}
void outlist(struct ListNode* obj) {
    struct ListNode* tmp = obj;
    while (tmp) {
        printf("[%d|-]->", tmp->val);
        tmp = tmp->next;
    }
    printf("\n");
}
void myLinkedListFree(struct ListNode* obj) {      //free
    struct ListNode* p = obj;
    while (p) {
        struct ListNode* tmp = p;
        p = tmp->next;
        free(tmp);
    }
}
void test1() {
    struct ListNode* p1 = crt(5);
    outlist(p1); 
    struct ListNode* pf = removeElements(p1, 0);
    outlist(pf);
    myLinkedListFree(pf);
}
int main() {
    test1();
    return 0;
}