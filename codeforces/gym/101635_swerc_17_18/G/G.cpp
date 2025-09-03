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

#define X first
#define Y second
typedef pair<int,int> ii;

int dist(ii &a, ii &b) {
    return abs(a.X - b.X) + abs(a.Y - b.Y);
}

void solve() {
    int n, m;
    cin >> n >> m;
    vector<pair<int,int>> b(n), c(m);
    for (auto &[x, y]: b) cin >> x >> y;
    for (auto &[x, y]: c) cin >> x >> y;
    pair<int,int> r;
    cin >> r.X >> r.Y;
    for (int i = m; i < m + n - 1; i++) {   // n - 1 to ensure at least one
        c.push_back(r);
    }

    int64_t ans = 0;
    for (int i = 0; i < n; i++) {
        ans += dist(r, b[i]);
    }

    m = m + n - 1;
    vector<vector<int>> mat(n, vector<int>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            mat[i][j] = dist(b[i], c[j]);
        }
    }
    auto [add, matching] = hungarian(mat);
    ans += add;
    cout << ans << '\n';
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
