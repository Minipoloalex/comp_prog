#include <bits/stdc++.h>
using namespace std;

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        string s;
        cin >> s;
        int ans = INT_MAX;
        for (int i = 1; i < n; i++) {
            vector<int> nums;
            for (int j = 0; j < n; j++) {
                if (j == i - 1) continue;
                else if (j == i) {
                    nums.push_back((s[j - 1] - '0') * 10 + (s[j] - '0'));
                }
                else {
                    nums.push_back(s[j] - '0');
                }
            }
            sort(nums.begin(), nums.end());

            if (nums.front() == 0) {
                ans = 0;
                break;
            }
            int curr = 0;
            for (int num: nums) {
                if (num != 1) {
                    curr += num;
                }
            }
            if (curr == 0) curr = 1;
            ans = min(ans, curr);
        }
        cout << ans << endl;
    }
    return 0;
}
