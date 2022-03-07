/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
//_____________________________________________________________________________________
//不改变原linklist；
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
//——————————————————————————————————————
//原linklist变为空；
typedef int ElementType;
typedef struct Node *PtrToNode;
struct Node {
    ElementType Data;
    PtrToNode   Next;
};
typedef PtrToNode List;
List Merge( List L1, List L2 )
{
    List L;
    L=(List)malloc(sizeof(struct Node));
    L->Next=NULL;
     
    List p1=L1->Next,p2=L2->Next,p=L;
    while(p1&&p2)
    {
        if(p1->Data<=p2->Data)
        {
            p->Next=p1;
            p1=p1->Next;
            L1->Next=p1;
        }else{
            p->Next=p2;
            p2=p2->Next;
            L2->Next=p2;
        }
        p =p->Next;
    }
    if(p1)
    {
        p->Next=p1;
        L1->Next=NULL;      
    }
    if(p2)
    {
        p->Next=p2;
        L2->Next=NULL;
         
    }
 
    return L;
}
