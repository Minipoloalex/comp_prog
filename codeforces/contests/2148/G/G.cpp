#include <bits/stdc++.h>
using namespace std;

vector<int> divisors(int n) {
    vector<int> ans;
    for (int i = 1; 1LL * i * i <= n; i++) {
        if (n % i == 0) {
            ans.push_back(i);
            if (n / i != i) ans.push_back(n / i);
        }
    }
    ans.erase(ans.begin()); // remove 1
    return ans;
}

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto &ai: a) cin >> ai;
    vector<int> cnt(n + 1);
    vector<int> cnt_to_cnt(n + 1);
    cnt_to_cnt[0] = n;
    int cur_max = 0;    // doesn't consider divisors with (i + 1) count
    for (int i = 0; i < n; i++) {
        vector<int> divs = divisors(a[i]);
        for (int divi: divs) {
            cnt_to_cnt[cnt[divi]]--;
            cnt[divi]++;
            cnt_to_cnt[cnt[divi]]++;

            if (cnt[divi] < i + 1) {
                cur_max = max(cur_max, cnt[divi]);
            }
        }
        if (cnt_to_cnt[i] > 0) cur_max = i;

        cout << cur_max << " ";
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
