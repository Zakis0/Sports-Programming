// https://leetcode.com/problems/merge-two-sorted-lists/

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

ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
    ListNode *p1 = list1, *p2 = list2;
    ListNode *result, *pResult;

    if (p1 == nullptr && p2 == nullptr) {
        return nullptr;
    }
    else if(p2 == nullptr) {
        result = new ListNode(p1->val, nullptr);
        p1 = p1->next;
    }
    else if (p1 == nullptr) {
        result = new ListNode(p2->val, nullptr);
        p2 = p2->next;
    }
    else if (p1->val < p2->val) {
        result = new ListNode(p1->val, nullptr);
        p1 = p1->next;
    }
    else {
        result = new ListNode(p2->val, nullptr);
        p2 = p2->next;
    }
    pResult = result;
    while (true) {
        if (p1 == nullptr && p2 == nullptr) {
            break;
        }
        if (p1 != nullptr && p2 != nullptr) {
            if (p1->val < p2->val) {
                pResult->next = new ListNode(p1->val, nullptr);
                p1 = p1->next;
            }
            else {
                pResult->next = new ListNode(p2->val, nullptr);
                p2 = p2->next;
            }
        }
        else if (p2 == nullptr) {
            pResult->next = new ListNode(p1->val, nullptr);
            p1 = p1->next;
        }
        else {
            pResult->next = new ListNode(p2->val, nullptr);
            p2 = p2->next;
        }
        pResult = pResult->next;
    }
    return result;
}

int main() {
    ListNode *l1 = vectorToList({1, 2, 3, 4, 5});
    ListNode *l2 = vectorToList({1, 2, 3});

    printList(mergeTwoLists(l1, l2));
    return 0;
}
