#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);

    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    vector<pair<int64_t, int>> segs;
    for (int i = 0; i < n; i++) {
        int64_t sum = a[i];
        int cnt = 1;
        while (!segs.empty() && (double(sum) / cnt) < (double(segs.back().first) / segs.back().second)) {
            auto [s, c] = segs.back();
            segs.pop_back();
            sum += s;
            cnt += c;
        }
        segs.emplace_back(sum, cnt);
    }
    

    for (auto &[sum, cnt]: segs) {
        double val = double(sum) / cnt;
        for (int i = 0; i < cnt; i++) {
            cout << fixed << setprecision(10) << val << '\n';
        }
    }
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    solve();
    return 0;
}
