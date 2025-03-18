#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    auto nxt_perfect = [](int x) {
        int aux = (int) ceil(sqrt(x));
        return aux * aux;
    };
    int target = nxt_perfect(n - 1);
    vector<int> ans(n);
    int cur = target - (n - 1);
    int cur_max = n - 1;
    for (int i = n - 1; i >= 0; i--) {
        ans[i] = cur;
        cur++;
        if (i > 0 && cur > cur_max) {
            target = nxt_perfect(i - 1);
            cur = target - (i - 1);
            cur_max = i - 1;
        }
    }
    for (int a: ans) cout << a << " ";
    cout << '\n';
    // for (int i = 0; i < n; i++) {
    //     int value = i + ans[i];
    //     int aux = int(sqrt(value));
    //     assert(aux * aux == value);
    // }
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
