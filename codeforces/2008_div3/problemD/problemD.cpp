#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;

const int MAX_N = int(2e5) + 10;
bitset<MAX_N> bs;

vi p;
vi vis;
vi curr;

void dfs(int i) {
    vis[i] = 1; curr.push_back(i);
    int nxt = p[i];
    if (vis[nxt] == 0) {    // new idx
        dfs(nxt);
    }
    // else if (vis[nxt] == 1) {   // already visited (closed the cycle)
    //     return;
    // }
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        p.resize(n);
        for (int i = 0; i < n; i++) {
            cin >> p[i];
            p[i]--;
        }
        bs.reset();
        for (int i = 0; i < n; i++) {
            char si;
            cin >> si;
            if (si == '0') bs.set(i);
        }
        vis.assign(n, 0);
        vector<vi> cycles;

        for (int i = 0; i < n; i++) {
            if (!vis[i]) {
                curr.clear();
                dfs(i);
                cycles.push_back(curr);
            }
        }
        vi ans(n, 0);
        for (vi &cycle: cycles) {
            int cycle_ans = 0;
            for (int i: cycle) {
                cycle_ans += bs[i];
            }
            for (int i: cycle) {
                ans[i] = cycle_ans;
            }
        }
        for (int a: ans) {
            cout << a << " ";
        }
        cout << '\n';
    }    
    return 0;
}
