#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<vvi> vvvi;

const int MAX_TIME = 30;

void solve() {
    map<string,int> score;
    map<string,vector<string>> gstr;
    string line;
    int n = 0;
    while (getline(cin, line)) {
        n++;
        istringstream iss(line);
        string trash, u;
        iss >> trash;
        iss >> u;
        iss >> trash >> trash;
        string rate;
        iss >> rate;
        rate = rate.substr(5);
        rate = rate.substr(0,rate.size()-1);
        int rt = stoi(rate);
        score[u] = rt;

        for (int i = 0; i < 4; i++) iss >> trash;
        string v;
        while (iss >> v) {
            bool finish = v.size() == 2;
            if (v.size() == 3) {
                v.pop_back();
            }
            gstr[u].push_back(v);
            if (finish) break;
        }
    }
    map<string,int> id;
    int curid = 0;
    int cnt = 0;
    vector<int> rt;
    for (auto &[s, rate]: score) {
        if (rate != 0) {
            cnt++;
            id[s] = curid++;
            rt.push_back(rate);
        }
    }
    for (auto &[s, rate]: score) {
        if (rate == 0) {
            id[s] = curid++;
        }
    }
    vector<vector<int>> g(n);
    for (auto &[u, edges]: gstr) {
        int uid = id[u];
        for (string &v: edges) {
            int vid = id[v];
            g[uid].push_back(vid);
        }
    }

    int complete = (1 << cnt)-1;
    vvvi dp(1<<cnt,vvi(n,vi(MAX_TIME+1,-1)));
    function<int(int,int,int)> go = [&](int mask, int u, int tm) {
        if (mask == complete || tm == 0) return 0;
        if (tm < 0) return INT_MIN;

        int &mem = dp[mask][u][tm];
        if (mem != -1) return mem;

        int best = 0;
        if (u < cnt && (mask & (1 << u)) == 0) {
            best = max(best, rt[u]*(tm-1) + go(mask | (1 << u), u, tm-1));
        }
        for (int v: g[u]) {
            best = max(best, go(mask, v, tm-1));
        }
        return mem = best;
    };

    int ans = go(0,id["AA"],30);
    cout << ans << '\n';

    int ans2 = 0;
    for (int mask = 0; mask < complete; mask++) {
        int other = (~mask) & complete;
        ans2 = max(ans2, go(mask,id["AA"],26) + go(other,id["AA"],26));
    }
    cout << ans2 << '\n';
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    // cin.exceptions(cin.failbit);
    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
