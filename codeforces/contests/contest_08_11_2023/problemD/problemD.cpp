#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;

vi v;

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;
        v.resize(n);
        for (int i = 0; i < n; i++) {
            cin >> v[i];
        }
        sort(v.begin(), v.end());
        // for (int a: v) {
        //     cout << a << " ";
        // }
        // cout << '\n';
        // e.g.: 1 2 3 10 12 14 16, k = 3
        // e.g.: 1 2 4 5 6, k = 1 (n = 5)
        // 1 3 3 4 5 7 8 10, k = 1 (n = 8)
        // too different leads to:
        // either rm others or rm what came before (continue loop)
        int min_to_remove = INT_MAX;
        int curr_start = 0;
        for (int i = 1; i < n; i++) {
            int after = v[i];
            int before = v[i - 1];
            if (after - before > k) {
                // check removing others
                // must consider current_start
                int val = n - i + curr_start;
                if (val < min_to_remove) {
                    min_to_remove = val;
                }
                curr_start = i;
            }
            else if (i == n - 1 && curr_start < min_to_remove) {
                // last iter
                min_to_remove = curr_start;
            }
        }
        if (min_to_remove == INT_MAX) {
            min_to_remove = 0;
        }
        cout << min_to_remove << '\n';
    }
    return 0;
}
