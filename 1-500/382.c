/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

typedef struct {
    struct ListNode *head;
    int size;
} Solution;


Solution* solutionCreate(struct ListNode* head) {
    Solution *obj = malloc(sizeof(Solution));
    struct ListNode *p;
    obj->head = head;
    obj->size = 0;
    for (p = head; p != NULL; p = p->next) {
        ++obj->size;
    }
    srand(time(NULL));
    return obj;
}

int solutionGetRandom(Solution* obj) {
    struct ListNode *p = obj->head;
    int pos = rand() % obj->size;
    while (pos > 0) {
        p = p->next;
        --pos;
    }
    return p->val;
}

void solutionFree(Solution* obj) {
    struct ListNode *p, *q;
    p = obj->head;
    while(p != NULL) {
        q = p->next;
        free(p);
        p = q;
    }
    free(obj);
}

/**
 * Your Solution struct will be instantiated and called as such:
 * Solution* obj = solutionCreate(head);
 * int param_1 = solutionGetRandom(obj);
 
 * solutionFree(obj);
*/
