#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, k;
    cin >> n >> k;

    map<uint32_t,int> cnt;
    vector<vector<int>> machines(n);
    auto convert = [&](vector<int> &reqr) {
        uint32_t res = 0;
        for (int i = 0; i < k; i++) {
            res |= reqr[i] << (4 * i);
        }
        return res;
    };
    function<void(int,int,vector<int>&,int)> add = [&](int id, int i, vector<int> &cur, int to_add) {
        if (i == k) {
            int bits = convert(cur);
            cnt[bits] += to_add;
            return;
        }
        for (int j = 0; j <= machines[id][i]; j++) {
            cur[i] += j;
            add(id, i + 1, cur, to_add);
            cur[i] -= j;
        }
    };
    vector<int> def(k);
    auto conn = [&](int id) {
        add(id, 0, def, +1);
    };
    auto disc = [&](int id) {
        add(id, 0, def, -1);
    };
    int machid = 0;
    while (n--) {
        char c;
        cin >> c;
        if (c == 'C') {
            int r;
            cin >> r;
            vector<int> mach(k);
            for (int i = 0; i < r; i++) {
                int ti;
                cin >> ti;
                mach[ti - 1]++;
            }
            machines[machid] = mach;
            conn(machid);
            machid++;
        }
        else if (c == 'J') {
            int r;
            cin >> r;
            vector<int> job(k);
            for (int i = 0; i < r; i++) {
                int ti;
                cin >> ti;
                job[ti - 1]++;
            }
            uint32_t jobint = convert(job);
            cout << cnt[jobint] << '\n';
        }
        else {
            assert(c == 'D');
            int id;
            cin >> id;
            id--;
            disc(id);
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
