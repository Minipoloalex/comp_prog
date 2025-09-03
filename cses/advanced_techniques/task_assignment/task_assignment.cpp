#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;
#define sz(v) int(v.size())
#define all(v) begin(v), end(v)

/**
 * Given a weighted bipartite graph, matches every node on
 * the left with a node on the right such that no
 * nodes are in two matchings and the sum of the edge weights is minimal. Takes
 * cost[N][M], where cost[i][j] = cost for L[i] to be matched with R[j] and
 * returns (min cost, match), where L[i] is matched with
 * R[match[i]]. Negate costs for max cost. Requires N <= M.
 * Time: O(N^2 * M)
 */
pair<int, vi> hungarian(const vector<vi> &a) {
	if (a.empty()) return {0, {}};
	int n = sz(a) + 1, m = sz(a[0]) + 1;
	vi u(n), v(m), p(m), ans(n - 1);
	for (int i = 1; i < n; i++) {
		p[0] = i;
		int j0 = 0; // add "dummy" worker 0
		vi dist(m, INT_MAX), pre(m, -1);
		vector<bool> done(m + 1);
		do { // dijkstra
			done[j0] = true;
			int i0 = p[j0], j1, delta = INT_MAX;
			for (int j = 1; j < m; j++) if (!done[j]) {
				auto cur = a[i0 - 1][j - 1] - u[i0] - v[j];
				if (cur < dist[j]) dist[j] = cur, pre[j] = j0;
				if (dist[j] < delta) delta = dist[j], j1 = j;
			}
			for (int j = 0; j < m; j++) {
				if (done[j]) u[p[j]] += delta, v[j] -= delta;
				else dist[j] -= delta;
			}
			j0 = j1;
		} while (p[j0]);
		while (j0) { // update alternating path
			int j1 = pre[j0];
			p[j0] = p[j1], j0 = j1;
		}
	}
    for (int j = 1; j < m; j++) if (p[j]) ans[p[j] - 1] = j - 1;
	return {-v[0], ans}; // min cost
}

void solve_rev() {
    // for this problem, it doesn't matter whether we make
    // employees workers or the tasks the workers (because n == m)
    // here, we do employees=jobs, tasks=workers
    int n;
    cin >> n;
    vector<vector<int>> mat(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> mat[i][j];
        }
    }
    auto [res, matching] = hungarian(mat);
    cout << res << '\n';
    vector<int> ans(n);
    for (int i = 0; i < n; i++) {   // loop through tasks
        ans[i] = matching[i];
    }
    for (int i = 0; i < n; i++) {
        cout << i + 1 << " " << ans[i] + 1 << '\n';
    }
}

void solve() {
    // here, we do normal workers=employees, jobs=tasks
    int n;
    cin >> n;
    vector<vector<int>> mat(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> mat[j][i];
        }
    }
    auto [res, matching] = hungarian(mat);
    cout << res << '\n';
    vector<int> ans(n);
    for (int i = 0; i < n; i++) {   // loop through tasks
        ans[matching[i]] = i;
    }
    for (int i = 0; i < n; i++) {
        cout << i + 1 << " " << ans[i] + 1 << '\n';
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
