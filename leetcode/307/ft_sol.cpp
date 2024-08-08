#include <bits/stdc++.h>
using namespace std;

#define LSO(n) ((n) & (-(n)))

class NumArray {
private:
    vector<int> _nums;
    vector<int> ft;
    int size;
    int rsq(int i) {
        int sum = 0;
        for (; i; i -= LSO(i)) sum += ft[i];
        return sum;
    }
    void _update(int i, int val) {
        for (; i < size; i += LSO(i)) ft[i] += val;
    }
public:
    NumArray(vector<int> &nums) {
        _nums = nums;
        size = (int) nums.size() + 1;

        ft.assign(size, 0);
        for (int i = 1; i <= (int) nums.size(); i++) {
            ft[i] += nums[i - 1];   // copy nums[0:n] -> ft[1:n+1]

            int p = i + LSO(i);     // add ft[i] only to immediate parent of each index
            if (p < size) {
                ft[p] += ft[i];
            }
        }
        // for (int i = 0; i < size; i++) {
        //     cout << ft[i] << " ";
        // }
        // cout << '\n';
        
    }
    void update(int index, int val) {
        int diff = val - _nums[index];
        _nums[index] = val;

        index++;
        _update(index, diff);
    }
    int sumRange(int left, int right) {
        left++;
        right++;
        // cout << '\n';
        // cout << right << ": " << rsq(right) << ", " << left - 1 << ": " << rsq(left - 1) << '\n';
        return rsq(right) - rsq(left - 1);
    }
};

int main() {
    vector<int> nums;
    // nums = {1, 3, 5};
    // NumArray na(nums);
    // cout << na.sumRange(0, 2) << '\n';
    // na.update(1, 2);
    // cout << na.sumRange(0, 2) << '\n';

    nums = {7, 2, 7, 2, 0};
    NumArray na(nums);
    na.update(4, 6);
    na.update(0, 2);
    na.update(0, 9);
    // 9, 2, 7, 2, 6
    cout << na.sumRange(4, 4) << " ";   // 6
    na.update(3, 8);
    // 9, 2, 7, 8, 6
    cout << na.sumRange(0, 4) << " ";   // 32
    na.update(4, 1);
    // 9, 2, 7, 8, 1
    cout << na.sumRange(0, 3) << " " << na.sumRange(0, 4) << '\n';  // 26 27
    na.update(0, 4);
    return 0;
}
