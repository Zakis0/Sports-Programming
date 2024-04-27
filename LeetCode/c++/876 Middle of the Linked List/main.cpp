// https://leetcode.com/problems/middle-of-the-linked-list/

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

void printList(ListNode* l) {
    while (l != nullptr) {
        cout << l->val << " ";
        l = l->next;
    }
    cout << endl;
}

ListNode* vectorToList(vector<int> vector) {
    ListNode *list, *cur, *next;
    if (!vector.empty()) {
        list = new ListNode(vector[0], nullptr);
        cur = list;
    }
    else {
        return nullptr;
    }
    for (int i = 1; i < vector.size(); ++i) {
        next = new ListNode(vector[i], nullptr);
        cur->next = next;
        cur = next;
    }
    return list;
}

ListNode* middleNode(ListNode* head) {
    ListNode *list = head, *temp = head;
    int i = 1;
    while (temp != nullptr) {
        temp = temp->next;
        if (i++ % 2 == 0) {
            list = list->next;
        }
    }
    return list;
}

int main() {
    ListNode *l1 = vectorToList({1, 2, 3, 4, 5});
    printList(middleNode(l1));
    return 0;
}
