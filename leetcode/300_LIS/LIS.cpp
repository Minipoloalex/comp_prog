#include <bits/stdc++.h>
using namespace std;


class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        int n = (int) nums.size();
        vector<int> ans;
        ans.push_back(nums[0]);
        for (int i = 1; i < n; i++) {
            if (nums[i] > ans.back()) {
                ans.push_back(nums[i]);
            }
            else {
                int idx = (int) (lower_bound(ans.begin(), ans.end(), nums[i]) - ans.begin());
                ans[idx] = nums[i];
            }
        }
        return ans.size();
    }
};
