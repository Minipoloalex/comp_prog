#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maxPoints(vector<vector<int>>& points) {
        int n = (int) points.size();

        int ans = min(2, n);
        for (int i = 0; i < n; i++) {
            int xi = points[i][0];
            int yi = points[i][1];

            map<float, int> cnt;
            // Maybe could use GCD instead of using floating points
            // dy = 6, dx = 2 -> [1, 3]
            for (int j = i + 1; j < n; j++) {
                int xj = points[j][0];
                int yj = points[j][1];
                int line_dy = yj - yi;
                int line_dx = xj - xi;
                float slope = 0;
                if (line_dx == 0) {
                    slope = FLT_MAX;
                }
                else slope = (float) line_dy / (float) line_dx;
                cnt[slope]++;
                ans = max(ans, 1 + cnt[slope]); // or just do it after in a loop
            }
        }
        return ans;
    }
};

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    vector<vector<int>> pts = {{1,1,},{3,2,},{5,3,},{4,1,},{2,3,},{1,4,},};//{{1,1,},{2,2,},{3,3,},};
    Solution s;
    int ans = s.maxPoints(pts);
    cout << ans << endl;
    return 0;
}

/*
ChatGPT solution that uses GCD and pairs of ints

// Helper function to compute gcd
int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}

int maxPoints(vector<vector<int>>& points) {
    int n = points.size();
    if (n <= 2) return n;

    int ans = 2; // At least two points can always form a line
    for (int i = 0; i < n; i++) {
        map<pair<int, int>, int> cnt; // To store reduced slopes as (dy, dx)
        for (int j = i + 1; j < n; j++) {
            int dy = points[j][1] - points[i][1];
            int dx = points[j][0] - points[i][0];

            // Normalize the slope using gcd
            int g = gcd(dy, dx);
            dy /= g;
            dx /= g;

            // Ensure consistency by making dx positive
            if (dx < 0) {
                dx = -dx;
                dy = -dy;
            }

            cnt[{dy, dx}]++;
            ans = max(ans, 1 + cnt[{dy, dx}]);
        }
    }
    return ans;
}

*/
