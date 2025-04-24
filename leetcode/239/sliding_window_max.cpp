#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        multiset<int> s;
        int n = int(nums.size());
        vector<int> &a = nums;
        vector<int> ans;
        for (int i = 0; i < n; i++) {
            if (s.size() == k) {
                s.erase(s.find(a[i - k]));
            }
            s.insert(a[i]);
            if (s.size() == k) {
                ans.push_back(*s.rbegin());
            }
        }
        return ans;
    }
};

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    return 0;
}
