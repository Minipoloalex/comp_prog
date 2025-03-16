#include <bits/stdc++.h>
using namespace std;

const int MAX_AI = int(1e6);
vector<int> cnt(MAX_AI + 1);
void solve() {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int ai;
        cin >> ai;
        cnt[ai]++;
    }
    for (int g = MAX_AI; g >= 1; g--) {
        int total = 0;
        for (int j = g; j <= MAX_AI; j += g) {
            total += cnt[j];
        }
        if (total >= 2) {
            cout << g << '\n';
            break;
        }
    }
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
