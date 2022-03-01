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