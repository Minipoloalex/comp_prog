#include <bits/stdc++.h>
using namespace std;

using ii = pair<int, int>;
using vi = vector<int>;
using vvi = vector<vi>;

class Solution {
private:
    vector<int> taken;
    set<ii> pq;
    int n;

    int man_dist(int u, int v, vvi &pts) {
        return abs(pts[u][0] - pts[v][0]) + abs(pts[u][1] - pts[v][1]);
    }
    void process(int u, vvi &pts) {
        taken[u] = 1;
        for (int v = 0; v < n; v++) {
            if (u == v || taken[v]) continue;
            pq.emplace(man_dist(u, v, pts), v);
        }
    }
public:
    int minCostConnectPoints(vector<vector<int>>& points) {
        taken.assign(points.size(), 0);
        n = (int) points.size();
        
        int cost = 0, num_taken = 0;
        process(0, points);
        while (!pq.empty()) {
            auto it = pq.begin();
            auto [w, u] = *it;
            pq.erase(it);
            if (taken[u]) continue;

            cost += w; num_taken++;
            process(u, points);
            if (num_taken == n - 1) break;
        }
        return cost;
    }
};

int main() {
    return 0;
}
