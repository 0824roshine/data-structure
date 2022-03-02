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
        tp->val = i < n / 2 ? i : n - 1;
        tp->next = NULL;
        p->next = tp;
        p = p->next;
    }
    p = head1->next;
    free(head1);
    return p;
}
struct ListNode* reverse(struct ListNode* head) {
    struct ListNode* proceed = head;
    struct ListNode* p = head;
    while (proceed->next) {
        struct ListNode* newhead = proceed->next;
        proceed->next = newhead->next;
        newhead->next = p;
        p = newhead;
    }
    return p;
}
int isPalindrome(struct ListNode* head) {
    int count = 0;
    struct ListNode* tmp = head;
    if (head->next == NULL)
        return 1;
    while (tmp) {
        count++;
        tmp = tmp->next;
    }
    int half = count % 2 ? count / 2 : count / 2 - 1;
    for (count = 0, tmp = head; count < half; count++) {
        tmp = tmp->next;
    }
    struct ListNode* mid = reverse(tmp->next);
    tmp = head;
    while (mid) {
        if (mid->val != tmp->val)
            return 0;
        else {
            mid = mid->next;
            tmp = tmp->next;
        }
    }
    return 1;
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
    struct ListNode* p1 = crt(7);
    outlist(p1);
    if (isPalindrome(p1));
        printf("yes\n");
    else
        printf("no\n");
    myLinkedListFree(p1);
}
int main() {
    test1();
    return 0;
}