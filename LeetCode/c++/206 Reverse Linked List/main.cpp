// https://leetcode.com/problems/reverse-linked-list/

#include <iostream>
#include <stack>
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

//ListNode* reverseList(ListNode* head) {
//    ListNode* pList = head;
//    stack<int> st;
//    while (pList != nullptr) {
//        st.push(pList->val);
//        pList = pList->next;
//    }
//    pList = head;
//    while (pList != nullptr) {
//        pList->val = st.top();
//        st.pop();
//        pList = pList->next;
//    }
//    return head;
//}

ListNode* reverseList(ListNode* head) {
    if (head == nullptr) {
        return nullptr;
    }
    ListNode* pList = head, *pLast = new ListNode(head->val, nullptr), *pCur;
    pList = pList->next;
    while (pList != nullptr) {
        pCur = new ListNode(pList->val, pLast);
        pLast = pCur;
        pList = pList->next;
    }
    return pLast;
}

int main() {
    ListNode *l1 = vectorToList({1, 2, 3, 4, 5});

    printList(reverseList(l1));
    return 0;
}
