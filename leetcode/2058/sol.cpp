#include <bits/stdc++.h>
using namespace std;

// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *_next) : val(x), next(_next) {}

    static ListNode *toListNode(const vector<int> &a) {    // no garbage collection because yes!
        ListNode *res = nullptr;
        for (auto it = a.rbegin(); it != a.rend(); it++) {
            res = new ListNode(*it, res);
        }
        return res;
    }
};

class Solution {
public:
    vector<int> nodesBetweenCriticalPoints(ListNode *head) {
        int before = -1;
        int before2 = -1;

        int first_critical = -1;
        int min_dist = INT_MAX;
        int last_critical = -1;
        int index = 0;
        while (head != nullptr) {
            int curr = head->val;
            if (before2 != -1 && before != -1) {
                if ((before > before2 && before > curr) || (before < before2 && before < curr)) {
                    // max || min

                    if (first_critical == -1) {
                        first_critical = index;
                    }
                    else {
                        min_dist = min(min_dist, index - last_critical);
                    }
                    last_critical = index;
                }
                
            }

            before2 = before;
            before = head->val;
            head = head->next;
            index++;
        }
        if (min_dist == INT_MAX) {
            return {-1, -1};
        }
        return {min_dist, last_critical - first_critical};
    }
};

int main() {
    Solution s;
    ListNode *ln = ListNode::toListNode({5,3,1,2,5,1,2});
    vector<int> v = s.nodesBetweenCriticalPoints(ln);
    cout << v[0] << " " << v[1] << endl;
    return 0;
}
