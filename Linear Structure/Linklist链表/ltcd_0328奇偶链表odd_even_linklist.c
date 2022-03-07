struct ListNode* oddEvenList(struct ListNode* head){
    if (head == NULL || head->next == NULL || head->next->next == NULL)
        return head;
    struct ListNode* odd = malloc(sizeof(struct ListNode));
    struct ListNode* even = malloc(sizeof(struct ListNode));
    struct ListNode* tmp = head;
    struct ListNode* start =odd;
    struct ListNode* mid = even;
    while (tmp) {
        odd->next = tmp;
        even->next = tmp->next;
        odd = odd->next;
        even = even->next;
        if (tmp->next == NULL)
            break;
        else
            tmp = tmp->next->next;
    }odd->next = mid->next;
    head = start->next;
    free(start);
    free(mid);
    return head;
}
