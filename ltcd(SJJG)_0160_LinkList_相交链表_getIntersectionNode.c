#include<malloc.h>
struct ListNode {
    int val;
    struct ListNode* next;
};
int* numcount(struct ListNode* headA, struct ListNode* headB) {
    int count = 0;
    struct ListNode* pa = headA; struct ListNode* pb = headB;
    int* ret = (int*)malloc(3 * sizeof(int));
    while (pa != NULL && pb != NULL) {
        count++;
        pa = pa->next;
        pb = pb->next;
    }
    ret[0] = count;
    count = 0;
    if (pa != NULL) {
        ret[2] = 1;
        while (pa) {
            pa = pa->next;
            count++;
        }
    }
    else {
        ret[2] = 0;
        while (pb) {
            pb = pb->next;
            count++;
        }
    }
    ret[1] = count;
    return ret;
}
struct ListNode* getIntersectionNode(struct ListNode* headA, struct ListNode* headB) {
    int* data = numcount(headA, headB);
    struct ListNode* Atmp = data[2] ? headA : headB;
    struct ListNode* Btmp = data[2] ? headB : headA;
    for (int i = 0; i < data[1]; i++) {
        Atmp = Atmp->next;
    }
    for (int i = 0; i < data[0]; i++) {
        if (Atmp != Btmp) {
            Atmp = Atmp->next;
            Btmp = Btmp->next;
        }
    }
    free(data);
    return Atmp;
}
//________________________________
int numcount(struct ListNode* head) {
    int count = 0;
    struct ListNode* p = head;
    while (p) {
        count++;
        p = p->next;
    }
    return count;
}
void swap(int* x, int* y) {
    int tmp = 0;
    tmp = *y;
    *y = *x;
    *x = tmp;
}
struct ListNode* getIntersectionNode(struct ListNode* headA, struct ListNode* headB) {
    int LA = numcount(headA);
    int LB = numcount(headB);
    struct ListNode* Atmp = LA > LB ? headA : headB;
    struct ListNode* Btmp = (Atmp == headA) ? headB : headA;
    if (LA < LB)
        swap(&LA, &LB);
    for (int i = 0; i < (LA - LB); i++) {
        Atmp = Atmp->next;
    }
    for (int i = 0; i < LB; i++) {
        if (Atmp != Btmp) {
            Atmp = Atmp->next;
            Btmp = Btmp->next;
        }
    }
    return Atmp;
}