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
            for (int j = i + 1; j < n; j++) {
                int xj = points[j][0];
                int yj = points[j][1];
                int line_dy = yj - yi;
                int line_dx = xj - xi;
                int cur = 2;
                for (int k = j + 1; k < n; k++) {
                    int xk = points[k][0];
                    int yk = points[k][1];
                    int other_dy = yk - yi;
                    int other_dx = xk - xi;
                    /*
                    line_dy / line_dx = other_dy / other_dx
                    */
                   if (line_dy * other_dx == other_dy * line_dx) cur++;
                }
                ans = max(cur, ans);
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
