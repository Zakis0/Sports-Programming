// https://leetcode.com/problems/add-two-numbers/

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

pair<int, int> getSum(int a, int b) {
    if (a + b > 9) {
        return make_pair((a + b) % 10, 1);
    }
    return make_pair(a + b, 0);
}

ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
    ListNode *list, *pListCur, *pListLast, *pL1 = l1, *pL2 = l2;
    int remainder;
    pair<int, int> s = getSum(l1->val, l2->val);
    remainder = s.second;

    list = new ListNode(s.first, nullptr);
    pListLast = list;

    pL1 = pL1->next;
    pL2 = pL2->next;

    while (true) {
        if (pL1 == nullptr && pL2 == nullptr) {
            break;
        }
        if (pL1 == nullptr) {
            s = getSum(pL2->val, remainder);
            pListCur = new ListNode(s.first, nullptr);
            remainder = s.second;

            pListLast->next = pListCur;
            pListLast = pListCur;
            pL2 = pL2->next;
        }
        else if (pL2 == nullptr) {
            s = getSum(pL1->val, remainder);
            pListCur = new ListNode(s.first, nullptr);
            remainder = s.second;

            pListLast->next = pListCur;
            pListLast = pListCur;
            pL1 = pL1->next;
        }
        else {
            s = getSum(pL1->val, pL2->val + remainder);
            pListCur = new ListNode(s.first, nullptr);
            remainder = s.second;

            pListLast->next = pListCur;
            pListLast = pListCur;
            pL1 = pL1->next;
            pL2 = pL2->next;
        }
    }
    if (remainder != 0) {
        pListCur = new ListNode(remainder, nullptr);
        pListLast->next = pListCur;
    }
    return list;
}

int main() {
    ListNode *l1 = vectorToList({9, 9, 9, 9, 9, 9, 9});
    ListNode *l2 = vectorToList({9, 9, 9, 9});

    printList(addTwoNumbers(l1, l2));
    return 0;
}
