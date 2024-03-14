// https://leetcode.com/problems/linked-list-cycle-ii/

#include <iostream>
#include <vector>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

bool hasCycle(ListNode *head) {
    ListNode *fast = head, *slow = head;
    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
        if (fast == slow) {
            return true;
        }
    }
    return false;
}

int main() {
    ListNode *l1, *l2, *l3, *l4, *l5;

    l5 = new ListNode(5, nullptr);
    l4 = new ListNode(4, l5);
    l3 = new ListNode(3, l4);
    l2 = new ListNode(2, l3);
    l1 = new ListNode(1, l2);

//    l5->next = l2;

    cout << hasCycle(l1) << endl;
    return 0;
}
