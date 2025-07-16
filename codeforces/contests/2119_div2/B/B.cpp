#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    int64_t px, py, qx, qy;
    cin >> px >> py >> qx >> qy;
    vector<int64_t> arr(n);
    for (auto &ai: arr) cin >> ai;

    bool ans;

    int64_t total_dist = accumulate(arr.begin(), arr.end(), 0LL);    
    int64_t total_dist_sq = total_dist*total_dist;

    int64_t dx = px-qx;
    int64_t dy = py-qy;
    int64_t dist_sq = (dx*dx)+(dy*dy);

    if (dist_sq == total_dist_sq) {
        ans = true;
    }
    else if (total_dist_sq < dist_sq) {
        ans = false;
    }
    else {
        int64_t mx = *max_element(arr.begin(), arr.end());
        int64_t min_distance = max(int64_t(0), mx - (total_dist - mx));
        int64_t min_distance_sq = min_distance * min_distance;
        if (min_distance_sq > dist_sq) {
            ans = false;
        }
        else {
            ans = true;
        }
    }

    cout << (ans ? "Yes" : "No") << '\n';
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
