#include <bits/stdc++.h>
using namespace std;

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        int best = 0;
        int best_index = 0;
        for (int i = 0; i < n; i++) {
            int ai, bi;
            cin >> ai >> bi;
            if (ai > 10) continue;
            if (bi > best) {
                best = bi;
                best_index = i + 1;
            }
        }
        cout << best_index << endl;
    }
    return 0;
}
