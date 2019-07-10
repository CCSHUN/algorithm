#include <iostream>
using namespace std;

/**
 * Definition for singly-linked list.
 * */
 struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
 };

/**
 * Reverse insertion list using forward insertion method
 */
 ListNode* reverse_list(ListNode* head) {
     if (head == nullptr || head->next == nullptr) {
         return head;
     }

    ListNode* ptr = head, *rhead = nullptr;

    while (ptr != nullptr){
        ListNode* node = ptr->next;
        ptr->next = rhead;
        rhead = ptr;
        ptr = node;
    }

    return rhead;
}
/**
 * Recursive method
 */
ListNode* reverse_list2(ListNode* head) {
     if (head == nullptr || head->next == nullptr) {
         return head;
     }

    ListNode* rhead = reverse_list2(head->next);

    head->next->next = head;
    head->next = nullptr;

    return rhead;
}

int main(int argc, char const *argv[]) {
    ListNode node0(0), node1(1), node2(2), node3(3), node4(4), node5(5);
    node0.next = &node1;
    node1.next = &node2;
    node2.next = &node3;
    node3.next = &node4;
    node4.next = &node5;

    ListNode* rhead = reverse_list2(&node0);

    for (ListNode* node = rhead; node != nullptr; node = node->next) {
        cout << node->val << endl;
    }

    return 0;
}
