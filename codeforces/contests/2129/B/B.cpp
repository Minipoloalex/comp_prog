#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, s;
    cin >> n >> s;
    vector<int> a(n);
    array<int,3> freq = {0, 0, 0};
    int total = 0;
    for (auto &ai: a) {
        cin >> ai;
        freq[ai]++;
        total += ai;
    }
    bool possible = false;
    if (total > s) {
        possible = true;
    }
    if (s == total + 1) {
        possible = true;
    }

    if (!possible) {
        cout << "-1\n";
    }
    else {
        auto handle = [&](int nr) {
            for (int i = 0; i < freq[nr]; i++) {
                cout << nr << " ";
            }
        };
        handle(1);
        handle(2);
        handle(0);
        cout << '\n';
    }
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    int t = 1;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
