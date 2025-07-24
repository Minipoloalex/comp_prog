#include <bits/stdc++.h>
using namespace std;

#define int int64_t

void solve() {
    int n, m, r, c;
    cin >> n >> m >> r >> c;
    
    array<int, 2> pos = {1, 1};
    vector<array<int, 2>> agents(4, {r, c});

    auto update_agents = [&]() {
        agents[0][0] -= 1;
        if (agents[0][0] == 0) agents[0][0] = 2;
        
    };  
    for (; pos[0] <= m; pos[0]++) {

    }

    cout << "No collisions!\n";
}

signed main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    int t = 1;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
