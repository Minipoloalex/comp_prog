#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int64_t> a(n);
        int64_t left_sum = 0;
        for (int i = 0; i < n - 2; i++) {
            int ai;
            cin >> ai;
            left_sum += ai;
        }
        int64_t prev, last;
        cin >> prev >> last;
        int64_t ans = last - prev + left_sum;
        cout << ans << '\n';
    }
    return 0;
}
