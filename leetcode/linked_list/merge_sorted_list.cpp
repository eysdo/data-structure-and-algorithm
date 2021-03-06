/**
 * @Author: Chacha 
 * @Date: 2019-01-06 22:50:09 
 * @Last Modified by: Chacha
 * @Last Modified time: 2019-02-18 22:11:29
 */

#include<iostream>
#include<string>
#include<vector>
using namespace std;

/** 
 * Definition for singly-linked list(单向链表)
 * Source: https://zh.wikipedia.org/wiki/链表
 */
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    /**
     * Merge two sorted linked lists and return it as a new list.
     * The new list should be made by splicing together the nodes of the first two lists.
     * 
     * Example: 
     *  Given 1->3->8->11->15->null, 2->null
     *  return 1->2->3->8->11->15->null
     * 
     * Source: https://leetcode.com/problems/merge-two-sorted-lists/
     * 
     * Operation steps:
     *  1. Exception handling, included in dummy->next
     *  2. Create the dummy and lastNode nodes, let the lastNode pointed to dummy node
     *  3. Loop processing for non-empty l1, l2, linking the smaller of l1/l2 to lastNode->next, recursing lastNode
     *  4. one of the linked lists in l1/l2 is empty to exit the while loop, 
     *     and the non-empty list header is linked to lastNode->next
     *  5. Return dummy->next, which is the final head pointer
     */ 
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        ListNode* dummy = new ListNode(0);
        ListNode* lastNode = dummy;
        
        while(l1 != NULL && l2 != NULL){

            if (l1->val < l2->val) {
                lastNode->next = l1;
                l1 = l1->next;
            } else {
                lastNode->next = l2;
                l2 = l2->next;
            }

            lastNode = lastNode->next;
        }

        lastNode->next = (l1 != NULL) ? l1 : l2;
        return dummy->next;
    }

    /**
     * Merge k sorted linked lists and return it as one sorted list.
     * 
     * Source:
     *  https://leetcode.com/problems/merge-k-sorted-lists/
     *  https://leetcode.com/problems/merge-k-sorted-lists/solution/
     *  https://www.kancloud.cn/kancloud/data-structure-and-algorithm-notes/73014#
     * 
     * 
     * Solution 1
     * @param lists: a list of ListNode
     * @return: The head of one sorted list.
     */
    ListNode* mergeKLists1(vector<ListNode *> &lists) {
        if (lists.empty()) return NULL;

        ListNode* dummy = new ListNode(INT_MAX);
        ListNode* lastNode = dummy;
        
        while(true) {
            int count = 0;
            int index = -1, tempVal = INT_MAX;

            for(int i = 0; i != lists.size(); ++i) {
                if (lists[i] == NULL) {
                    ++count;

                    if (count == lists.size()) {
                        lastNode->next = NULL;
                        return dummy->next;
                    }
                    continue;
                }
                
                // choose the min value in non-NULL ListNode
                if (lists[i] != NULL  && lists[i]->val <= tempVal) {
                    tempVal = lists[i]->val;
                    index = i;
                }
            }
            
            lastNode->next = lists[index];
            lastNode = lastNode->next;
            lists[index] = lists[index]->next;
        }
    }

    /**
     * Solution 2
     */
    ListNode* mergeKLists2(vector<ListNode *> &lists) {
        if (lists.empty()) return NULL;

        ListNode* head = lists[0];
        for(int i = 1; i != lists.size(); ++i) {
            head = mergeTwoLists(head, lists[i]);
        }

        return head;
    }
};

/* Function to print nodes in a given linked list */
void printList(ListNode *node) { 
    while (node != NULL) { 
        printf("%d ", node->val); 
        node = node->next; 
    }
}

int main() {
    ListNode* l1 = new ListNode(1);
    l1->next = new ListNode(3);
    l1->next->next = new ListNode(5);
    l1->next->next->next = new ListNode(7);
    l1->next->next->next->next = new ListNode(9);

    ListNode* l2 = new ListNode(2);
    l2->next = new ListNode(4);
    l2->next->next = new ListNode(6);
    l2->next->next->next = new ListNode(8);
    l2->next->next->next->next = new ListNode(10);

    ListNode* merged = Solution().mergeTwoLists(l1, l2);
    
    printList(merged);

    return 0;
}