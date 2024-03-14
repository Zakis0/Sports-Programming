// https://leetcode.com/problems/linked-list-cycle/

#include <iostream>
#include <vector>
#include <set>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

//ListNode *detectCycle(ListNode *head) {
//    set<ListNode*> st;
//    ListNode *temp = head;
//    while (temp != nullptr) {
//        if (st.count(temp) == 0) {
//            st.insert(temp);
//        }
//        else {
//            return temp;
//        }
//        temp = temp->next;
//    }
//    return nullptr;
//}

ListNode *detectCycle(ListNode *head) {
    ListNode *fast = head, *slow = head;
    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
        if (fast == slow) {
            slow = head;
            while (fast != slow){
                slow = slow->next;
                fast = fast->next;
            }
            cout << fast->val << endl;
            return fast;
        }
    }
    cout << "null" << endl;
    return nullptr;
}

int main() {
    ListNode *l1, *l2, *l3, *l4, *l5;

    l5 = new ListNode(5, nullptr);
    l4 = new ListNode(4, l5);
    l3 = new ListNode(3, l4);
    l2 = new ListNode(2, l3);
    l1 = new ListNode(1, l2);

    l5->next = l2;

    detectCycle(l1);
    return 0;
}
