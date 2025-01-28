#include <bits/stdc++.h>
using namespace std;

// The main difficulty in understanding the solution is why we don't need wrap-around
// It is not needed, because if it were needed, then it would be a contradiction with the sorting
// Also, the exit angle is always bigger than entrance because b > 0 (comes from acos: [0, PI])

/*
Example

Circle of the entry of a point Q:
    ||
  |    |
 |      |
|        P
 |      |
  |    |
    ||
If there was an exit of R after this entry of Q, then R's entry must have been processed before.
That's because entry < exit for every point.

*/
struct P {
    int x, y;
};

P to_point(vector<int> p) {
    return {p[0], p[1]};
}

class Solution {

public:
    double dist(P &a, P &b) {
        int xd = b.x - a.x;
        int yd = b.y - a.y;
        return sqrt(xd * xd + yd * yd);
    }
    int handle_pt(int i, vector<P> &pts, int n, int r) {
        int d = 2 * r;

        // vector<double> entrance,acosif it was for entrance, then the comparison function could not be the default)
        // anyway, maybe we should be careful of precision errors and comparisons used to sort
        vector<pair<double, bool>> angles;
        for (int j = 0; j < n; j++) {
            if (j == i) continue;
            double a = atan2(pts[j].y - pts[i].y, pts[j].x - pts[i].x);
            double cos_value = dist(pts[i], pts[j]) / d;
            if (cos_value > 1) continue;

            double b = acos(cos_value);
            double ent = a - b;
            double ex = a + b;
            angles.emplace_back(ent, false);
            angles.emplace_back(ex, true);
        }
        sort(angles.begin(), angles.end());

        int ans = 1, cur = 1;
        for (auto &[ang, exit]: angles) {
            if (exit) {
                cur--;
            }
            else cur++;
            ans = max(ans, cur);
        }
        return ans;
    }

    int numPoints(vector<vector<int>>& darts, int r) {
        int n = int(darts.size());
        vector<P> pts(n);
        for (int i = 0; i < n; i++) {
            pts[i] = to_point(darts[i]);
        }
        int ans = 0;
        for (int i = 0; i < n; i++) {
            ans = max(ans, handle_pt(i, pts, n, r));
        }
        return ans;
    }
};


int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    vector<vector<int>> darts = {{-2,0,},{2,0,},{0,2,},{0,-2,},};
    int r = 2;
    Solution s;
    int ans = s.numPoints(darts, r);
    cout << ans << '\n';
    return 0;
}
