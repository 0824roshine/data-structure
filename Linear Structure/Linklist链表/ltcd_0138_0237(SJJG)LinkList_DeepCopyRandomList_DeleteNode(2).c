struct Node* copyRandomList(struct Node* head) {
    if(head == NULL)
        return NULL;
    struct Node* p   = head;
    while(p){
        struct Node* tmp = malloc(sizeof(struct Node));
        tmp->val = p->val;
        tmp->next = p->next;
        tmp->random = NULL;
        p->next = tmp;
        p =p->next->next;
    }
    p = head;
    while(p){
        if(p->random != NULL)
            p->next->random = p->random->next;
        else
            p->next->random = NULL;
        p = p->next->next;
    }
    p =head;
    struct Node* ret = head->next;
    while(p->next->next){
        struct Node* tmp = p->next->next;
        p->next->next = tmp->next;
        p->next = tmp;
        p =p->next;
    }
    return ret;
}
/**
 *2.删除节点
 * };
 */
void deleteNode(struct ListNode* node) {
    struct ListNode* tmp = node->next;
    node->val = tmp->val;
    node->next = tmp->next;
    free(tmp);
}