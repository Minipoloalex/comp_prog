#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    int n;
    int64_t s;
    cin >> n >> s;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    int64_t curr_sum = 0, ans = 0;
    for (int l = 0, r = 0; l < n; ) {
        // must contain value at position l
        while (curr_sum < s && r < n) {  // while need to add
            curr_sum += a[r++];
        }

        if (curr_sum >= s) {
            ans += 1 + (n - r); // considering only segments with elements from the front
        }
        else {
            // not enough in the rest of the array to get s
            break;
        }
        curr_sum -= a[l++];
    }
    cout << ans << '\n';
    return 0;
}
