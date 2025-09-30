#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n; cin >> n;
    map<string,int> mp;
    vector<string> wordssss(n);

    vector<pair<int,int>> words(n);
    for (int i = 0; i < n; i++) {
        auto &[x, y] = words[i];
        cin >> wordssss[i] >> x >> y;
        mp[wordssss[i]] = i;
    }
    auto dot = [&](int i, int j) {
        auto &[xi, yi] = words[i];
        auto &[xj, yj] = words[j];
        return (xi * xj) + (yi * yj);
    };
    int m; cin >> m;
    vector<string> kb(m);
    for (auto &wrd: kb) cin >> wrd;
    auto handle = [&](vector<string> &qry, int k) -> int {
        int SZ = int(qry.size());
        vector<string> Q;
        for (int i = SZ - k; i < SZ; i++) {
            Q.emplace_back(qry[i]);
        }
        vector<int> cnt(n);
        for (int i = 0; i + k < m; i++) {
            bool possible = true;
            for (int j = 0; j < k; j++) {
                if (kb[i+j] != Q[j]) {
                    possible = false;
                    break;
                }
            }
            if (possible) {
                string word = kb[i + k];
                if (mp.count(word)) {
                    int id = mp[word];
                    cnt[id]++;
                }
            }
        }
        if (accumulate(cnt.begin(), cnt.end(), 0LL) == 0LL) return -1;

        vector<int64_t> similarity(n);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                int simi = dot(i, j);
                similarity[i] += simi * cnt[j];
            }
        }
        int mxid = int(max_element(similarity.begin(), similarity.end()) - similarity.begin());
        return mxid;
    };
    int q, k; cin >> q >> k;
    while (q--) {
        int f;
        cin >> f;
        vector<string> qry(f);
        for (auto &s: qry) cin >> s;
        int ans = -1;
        for (int i = k; i >= 1 && ans == -1; i--) {
            ans = handle(qry, i);
        }
        string s;
        if (ans == -1) s = "*";
        else s = wordssss[ans];

        for (auto &qs: qry) cout << qs << " ";
        cout << s << '\n';
    }
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
