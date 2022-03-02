#define _CRT_SECURE_NO_WARNINGS
#include<malloc.h>
#include<stdio.h>
struct ListNode {
    int val;
    struct ListNode* next;
};
struct ListNode* crt1(int n) {
    struct ListNode* head1 = malloc(sizeof(struct ListNode));
    struct ListNode* p = head1;
    for (int i = 0; i < n; i++) {
        struct ListNode* tp = malloc(sizeof(struct ListNode));
        tp->val = ((i - 2) * (i - 4)+6)%10;
        tp->next = NULL;
        p->next = tp;
        p = p->next;
    }
    p = head1->next;
    free(head1);
    return p;
}
struct ListNode* crt2(int n) {
    struct ListNode* head1 = malloc(sizeof(struct ListNode));
    struct ListNode* p = head1;
    for (int i = 0; i < n; i++) {
        struct ListNode* tp = malloc(sizeof(struct ListNode));
        tp->val = n;
        tp->next = NULL;
        p->next = tp;
        p = p->next;
    }
    p = head1->next;
    free(head1);
    return p;
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
struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2) {
    struct ListNode* add1 = l1;
    struct ListNode* add2 = l2;
    int promote = 0;
    int sum = 0;
    while (add1 && add2) {
        sum = add1->val + add2->val + promote;
        if (sum > 9) {
            promote = 1;
            add1->val = sum % 10;
        }
        else {
            promote = 0;
            add1->val = sum;
        }
        if (add1->next && add2->next) {
            add1 = add1->next;
            add2 = add2->next;
        }
        else
            break;
    }
    if (add1->next == NULL) {
        add1->next = add2->next;
        add2->next = NULL;
    }
    while (add1->next) {
        add1 = add1->next;
        sum = add1->val + promote;
        if (sum > 9) {
            promote = 1;
            add1->val = sum % 10;
        }
        else {
            promote = 0;
            add1->val = sum;
        }
    }
    if (promote==1 && add1->next == NULL) {
        struct ListNode* new = malloc(sizeof(struct ListNode));
        new->val = promote;
        new->next = NULL;
        add1->next = new;
    }
    return l1;
}

void test1() {
    struct ListNode* p1 = crt1(8);
    outlist(p1);
    struct ListNode* p2 = crt2(9);
    outlist(p2);
    outlist(addTwoNumbers(p1, p2));
    myLinkedListFree(p1);
    myLinkedListFree(p2);
}
int main() {
    test1();
    return 0;
}