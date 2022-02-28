struct ListNode {
     int val;
   struct ListNode *next;
 };
struct ListNode* reverseList(struct ListNode* head) {
    if (head == NULL || head->next == NULL)
        return head;
    struct ListNode* fakehead = head;
    struct ListNode* tmp = head;
    while (fakehead->next) {
        struct ListNode* move = fakehead->next;
        fakehead->next = move->next;
        move->next = tmp;
        tmp = move;
    }
    return tmp;
}