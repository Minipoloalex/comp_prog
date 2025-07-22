#include <bits/stdc++.h>
using namespace std;

/**
 * 2D Fenwick Tree implementation (point update, 2D range queries)
 * O(n * m) build, O(log^2 n) updates and queries
 * All cell locations are 0-indexed
 */
template <typename T>
class BIT2D {
  private:
	const int n, m;
	vector<vector<T>> bit;

	/** Efficient O(n*m) build from input 2D grid */
	void build(const vector<vector<T>> &a) {
        bit.assign(n + 1, vector<T>(m + 1, 0));
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                bit[i][j] = a[i-1][j-1];
            }
        }
        // push each bit[i][j] to its children
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                int i2 = i + (i & -i);
                int j2 = j + (j & -j);
                if (j2 <= m) bit[i][j2] += bit[i][j];
                if (i2 <= n) bit[i2][j] += bit[i][j];
                if (i2 <= n && j2 <= m) bit[i2][j2] -= bit[i][j];
            }
        }
    }

  public:
	BIT2D(int _n, int _m) : n(_n), m(_m), bit(n + 1, vector<T>(m + 1)) {}
	BIT2D(const vector<vector<T>> &a): n(int(a.size())), m(int(a[0].size())) {
		build(a);
	}

	/** adds val to the point (r, c) */
	void add(int r, int c, T val) {
		r++, c++;
		for (; r <= n; r += r & -r) {
			for (int i = c; i <= m; i += i & -i) { bit[r][i] += val; }
		}
	}

	/** @returns sum of points with row in [0, r] and column in [0, c] */
	T rect_sum(int r, int c) {
		r++, c++;
		T sum = 0;
		for (; r > 0; r -= r & -r) {
			for (int i = c; i > 0; i -= i & -i) { sum += bit[r][i]; }
		}
		return sum;
	}

	/** @returns sum of points with row in [r1, r2] and column in [c1, c2] */
	T rect_sum(int r1, int c1, int r2, int c2) {
		return rect_sum(r2, c2) - rect_sum(r2, c1 - 1) - rect_sum(r1 - 1, c2) +
		       rect_sum(r1 - 1, c1 - 1);
	}
};

void solve() {
    int n, q;
    cin >> n >> q;
    vector<vector<int>> forest(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        string s; cin >> s;
        for (int j = 0; j < n; j++) {
            forest[i][j] = s[j] == '*' ? 1 : 0;
        }
    }
    BIT2D<int> ft(forest);
    while (q--) {
        int type;
        cin >> type;
        if (type == 1) {
            int y, x;
            cin >> y >> x;
            y--;x--;
            int prev = forest[y][x];
            forest[y][x] = 1 - forest[y][x];
            ft.add(y, x, forest[y][x] - prev);
        }
        else {
            assert(type == 2);
            int y1, x1, y2, x2;
            cin >> y1 >> x1 >> y2 >> x2;
            y1--;x1--;y2--;x2--;
            cout << ft.rect_sum(y1, x1, y2, x2) << '\n';
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
