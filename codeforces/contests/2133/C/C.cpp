#include <bits/stdc++.h>
using namespace std;

int ask(int root, vector<int> const&nodes) {
    cout << "? " << root << " " << nodes.size();
    for (int node: nodes) cout << " " << node;
    cout << endl;
    int ans;
    cin >> ans;
    if (ans == -1) exit(1);
    return ans;
}
void finish(vector<int> nodes) {
    cout << "! " << nodes.size();
    for (int node: nodes) cout << " " << node;
    cout << endl;
}

void solve() {
    int n;
    cin >> n;
    vector<vector<int>> dist(n + 1);
    vector<int> all(n);
    iota(all.begin(), all.end(), 1);
    int mx_dist = 0;
    int root = -1;
    for (int i = 1; i <= n; i++) {
        int d = ask(i, all);
        if (d > mx_dist) {
            root = i;
            mx_dist = d;
        }
        dist[d].push_back(i);
    }
    assert(root != -1);
    int cur_dist = mx_dist - 1;
    vector<int> ans = {root};
    while (cur_dist >= 1) {
        vector<int> qry;
        for (int d = 0; d < cur_dist; d++) {
            for (int node: dist[d]) {
                qry.push_back(node);
            }
        }
        for (int node: ans) {
            qry.push_back(node);
        }
        for (int dist_node: dist[cur_dist]) {
            qry.push_back(dist_node);
            int obtained_distance = ask(root, qry);
            if (obtained_distance == mx_dist) {
                ans.push_back(dist_node);
                break;
            }
            qry.pop_back();
        }
        cur_dist--;
    }
    finish(ans);
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
