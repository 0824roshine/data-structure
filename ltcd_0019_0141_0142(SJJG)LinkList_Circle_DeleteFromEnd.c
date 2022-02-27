#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
typedef struct MyLinkedList {
    int val;
    struct MyLinkedList* next;
}ListNode;
//环形链表0141
int hasCycle( ListNode* head) {
    if (head == NULL || head->next == NULL || head->next->next == NULL)
        return 0;
    else {
        ListNode* fast = head;
        ListNode* slow = head;
        while (fast != NULL && fast->next != NULL) {
            fast = fast->next->next;
            slow = slow->next;
            if (fast == NULL || fast->next == NULL || fast->next->next == NULL)
                break;
            if (fast->val == slow->val)
                return 1;
        }
        return 0;
    }
}
int hasCycle1( ListNode* head) {
    if (head == NULL || head->next == NULL) {
        return 0;
    }
    ListNode* slow = head;
    ListNode* fast = head->next;
    while (slow != fast) {
        if (fast == NULL || fast->next == NULL) {
            return 0;
        }
        slow = slow->next;
        fast = fast->next->next;
    }
    return 1;
}
//环形链表 二 0142
ListNode* detectCycle1(ListNode* head) {
    if (head == NULL || head->next == NULL || head->next->next == NULL)
        return NULL;
    else {
        ListNode* fast = head;
        ListNode* slow = head;
        while (fast != NULL && fast->next != NULL) {
            fast = fast->next->next;
            slow = slow->next;
            if (fast == NULL || fast->next == NULL || fast->next->next == NULL)
                break;
            if (fast == slow){
                ListNode* tmp = head;
                while (tmp != slow) {
                    slow = slow->next;
                    tmp = tmp->next;
                }
                return tmp;
            }
        }
        return NULL;
    }
}
ListNode* detectCycle2(ListNode* head) {
    if (head == NULL || head->next == NULL) {
        return NULL;
    }
    ListNode* slow = head;
    ListNode* fast = head;
    do {
        if (fast == NULL || fast->next == NULL) {
            return NULL;
        }
        slow = slow->next;
        fast = fast->next->next;
    } while (slow != fast);
    ListNode* tmp = head;
    while (tmp != slow) {
        slow = slow->next;
        tmp = tmp->next;
    }
    return tmp;
}
//0019 删除倒数第k个元素
ListNode* gotofromend(ListNode* head, int k) {
    ListNode* tmp = head;
    for (int i = 0; i < k; i++) {
        tmp = tmp->next;
    }
    return tmp;
}
ListNode* removeNthFromEnd( ListNode* head, int n) {
    if (head == NULL)
        return NULL;
    ListNode* front = gotofromend(head, n - 1);
    ListNode* behind = head;
    if (front->next == NULL) {
        front = head;
        head = front->next;
    }
    else {
        while (front->next->next) {
            front = front->next;
            behind = behind->next;
        }
        front = behind->next;
        behind->next = front->next;
    }
    free(front);
    return head;
}
// 虚拟头节点法，有点像扫雷给个外圈儿
ListNode* removeNthFromEnd1(ListNode* head, int n) {
    ListNode* dummyHead = malloc(sizeof(ListNode));
    dummyHead->next = head;
    ListNode* fast = dummyHead;
    ListNode* slow = dummyHead;
    while (n--) {
        fast = fast->next;
    }
    fast = fast->next;

    while (fast) {
        fast = fast->next;
        slow = slow->next;
    }
    slow->next = slow->next->next;
    return dummyHead->next;
}