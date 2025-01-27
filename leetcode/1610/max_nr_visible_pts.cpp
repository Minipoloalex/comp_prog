#include <bits/stdc++.h>
using namespace std;

const double EPS = 1e-9;

struct P {
    int x, y;
    int64_t operator*(P &p) {
        return (int64_t) x * p.y - (int64_t) y * p.x;
    }
    P operator-(const P &o) const {
        return {x - o.x, y - o.y};
    }
    friend P toVec(P p1, P p2) {
        return p2 - p1;
    }

    friend bool operator==(P a, P b) {
        return a.x == b.x && a.y == b.y;
    }
};

P to_point(vector<int> p) {
    return {p[0], p[1]};
}


double bigger(double a, double b) {
    return a - b > EPS;
}

class Solution {
public:
    int visiblePoints(vector<vector<int>>& points, int angle, vector<int>& location) {
        P loc = to_point(location);
        vector<P> pts;
        int coincident = 0;
        for (auto &p: points) {
            P pt = to_point(p);
            if (pt == loc) coincident++;
            else pts.push_back(pt);
        }
        // always be careful of collinear and coincident points
        // here coincident points are not in the actual list

        /*
        To sort using cross products:
        - We should first compare quadrants
        - And only after compare using cross products

        auto quadrant = [](P v) {
            if (v.x >= 0 && v.y >= 0) return 1; // First quadrant
            if (v.x <  0 && v.y >= 0) return 2; // Second quadrant
            if (v.x <  0 && v.y <  0) return 3; // Third quadrant
            return 4;                           // Fourth quadrant
        };

        int qa = quadrant(va), qb = quadrant(vb);
        if (qa != qb) return qa < qb; // Sort by quadrant first

        // If in the same quadrant, sort by cross product
        ...
        */
        vector<double> angles;
        for (P &p: pts) {
            double ang = atan2(p.y - loc.y, p.x - loc.x);
            angles.push_back(ang);
        }
        sort(angles.begin(), angles.end());

        int n = (int) angles.size();
        for (int i = 0; i < n; i++) {
            angles.push_back(angles[i] + 2 * M_PI);
        }

        n = (int) angles.size();
        double rad_angle = angle * M_PI / 180;
        int ans = 0;
        // int l = 0, r = 0;
        // while (r < n) {
        //     while (bigger(angles[r] - angles[l], rad_angle)) {
        //         l++;
        //     }
        //     r++;
        //     ans = max(ans, r - l);
        // }
        for (int l = 0, r = 0; r < n; r++) {
            while (bigger(angles[r] - angles[l], rad_angle)) {
                l++;
            }
            ans = max(ans, r - l + 1);
        }
        return ans + coincident;
    }
};

int main() {
    Solution s;
    vector<vector<int>> points = {
        {2, 1},
        {2, 2},
        {2, 3},
    };
    vector<int> location = {1, 1};
    int angle = 90;
    int ans = s.visiblePoints(points, angle, location);
    cout << ans << endl;
}
