/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode* mergeTwoLists(struct ListNode* list1, struct ListNode* list2) {
    struct ListNode* head1 = list1;
    struct ListNode* head2 = list2;
    struct ListNode* final = malloc(sizeof(struct ListNode));
    final->next = NULL;
    struct ListNode* f = final;
    while (head1 && head2) {
        if (head1->val < head2->val) {
            f->next = head1;
            head1 = head1->next;
        }
        else {
            f->next = head2;
            head2 = head2->next;
        }
        f = f->next;
    }
    if (head1 != NULL) {
        f->next = head1;
    }
    else if (head2 != NULL) {
        f->next = head2;
    }
    else {
        f->next = NULL;
    }
    f = final->next;
    free(final);
    return f;
}