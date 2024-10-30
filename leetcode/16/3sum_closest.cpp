#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int threeSumClosest(vector<int>& nums, int target) {
        sort(nums.begin(), nums.end());
        int n = (int) nums.size();

        int min_diff = INT_MAX;
        int ans = -1;
        for (int i = 0; i < n; i++) {
            
            int lb = 0, ub = n - 1;
            while (lb < ub) {
                if (lb == i) {
                    lb++;
                    continue;
                }
                if (ub == i) {
                    ub--;
                    continue;
                }
                int sum = nums[i] + nums[lb] + nums[ub];
                int curr = abs(target - sum);
                if (curr < min_diff) {
                    ans = sum;
                    min_diff = curr;
                }
                if (sum == target) break;
                else if (sum > target) {
                    ub--;
                }
                else {
                    lb++;
                }
            }
        }
        return ans;
    }
};

int main() {
    Solution s;
    vector<int> nums = {1, 2, 3, 4};
    cout << s.threeSumClosest(nums, 5) << endl;
    nums = {-1,2,1,-4};
    cout << s.threeSumClosest(nums, 1) << endl;
    nums = {0,0,0};
    cout << s.threeSumClosest(nums, 1) << endl;
    return 0;
}
