#include <bits/stdc++.h>
using namespace std;

int solve_lis(vector<int> &r) {
    int n = (int) r.size();
    vector<int> ans(1, r[0]);
    for (int i = 1; i < n; i++) {
        auto it = lower_bound(ans.begin(), ans.end(), r[i]);    // smallest element x >= r[i]
        if (it == ans.end()) {    // no element (i.e. r[i] > ans.back())
            ans.push_back(r[i]);
        }
        else {
            *it = r[i];
        }
    }
    return (int) ans.size();
}

int solve_lcs_via_lis(const vector<int> &a, const vector<int> &b) {
    // Reducing LCS problem with permutations to LIS
    // assumes equal size of both sequences
    // permutations of 1-n
    assert(a.size() == b.size());

    int n = (int) b.size();
    vector<int> b_positions(n);
    for (int i = 0; i < n; i++) {
        b_positions[b[i] - 1] = i;
    }

    vector<int> r(n);
    for (int i = 0; i < n; i++) {
        r[i] = b_positions[a[i] - 1];
    }

    int lcs_ans = solve_lis(r);
    return lcs_ans;
}

vector<int> el[200010];
bitset<200010> vis;

map<int64_t, int> treemap;

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    int n, m, d;
    cin >> n >> m >> d;

    vector<int> ranking;
    int id = 1;
    for (int i = 0; i < m; i++) {
        int64_t a, b;
        cin >> a >> b;
        auto [itA, sucA] = treemap.insert({a, id});
        if (sucA) id++;

        auto [itB, sucB] = treemap.insert({b, id});
        if (sucB) id++;

        el[itA->second].push_back(itB->second);
    }
    assert(n == id - 1);

    auto topo_sort = [&](int a, auto &&self) -> void {
        vis[a] = 1;
        for (int b: el[a]) {
            if (!vis[b]) {
                self(b, self);
            }
        }
        ranking.push_back(a);
    };

    for (int i = 1; i <= n; i++) {
        if (!vis[i]) {
            topo_sort(i, topo_sort);
        }
    }
    reverse(ranking.begin(), ranking.end());

    vector<int> panda_ranking;
    for (int i = 0; i < n; i++) {
        int64_t c;
        cin >> c;

        auto it = treemap.find(c);
        if (it == treemap.end()) panda_ranking.push_back(n + 1);    // "invalid" number
        else panda_ranking.push_back(it->second);
    }

    // for (int i = 0; i < (int) ranking.size(); i++) {
    //     cout << ranking[i] << " ";
    // }
    // cout << '\n';
    // for (int i = 0; i < (int) panda_ranking.size(); i++) {
    //     cout << panda_ranking[i] << " ";
    // }
    // cout << '\n';

    // Get the LCS between both sequences (ranking and panda_ranking), through LIS
    int lcs = solve_lcs_via_lis(ranking, panda_ranking);
    cout << (n - lcs) * 2 << '\n';
    return 0;
}
