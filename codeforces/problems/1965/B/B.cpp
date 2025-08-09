#include <bits/stdc++.h>
using namespace std;

const int64_t MAX = int64_t(1e9);

void solve() {
    int n;
    int64_t k;
    cin >> n >> k;
    vector<int64_t> ans;
    int i = 1;
    int64_t sm = 0;
    while (sm + i < k)  {
        ans.push_back(i);
        sm += i;
        i <<= 1;
    }
    ans.push_back(k - i);
    ans.push_back(k + 1);
    ans.push_back(k + 1 + i);
    i <<= 1;
    while (ans.size() < 25 && i <= MAX) {
        ans.push_back(i);
        i <<= 1;
    }
    cout << ans.size() << '\n';
    for (int64_t v: ans) {
        cout << v << " ";
    }
    cout << '\n';
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
