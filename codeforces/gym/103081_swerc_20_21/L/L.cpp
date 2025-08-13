#include <bits/stdc++.h>
using namespace std;

using PQ = priority_queue<pair<int,int>>;

void solve() {
    int n, m;
    cin >> n >> m;

    vector<int> cap(m);
    for (auto &ci: cap) cin >> ci;

    vector<int> cidx(n);
    vector<vector<int>> customer_preferences(n);

    // from restaurant and customer to restaurant's preference of customer
    vector<map<int,int>> restaurant_preference_level(m);
    vector<PQ> current_customers(m);

    cin.ignore();
    for (int i = 0; i < n; i++) {
        string line;
        getline(cin, line);
        istringstream iss(line);
        int rid;
        while (iss >> rid) {
            rid--;
            customer_preferences[i].push_back(rid);
        }
    }
    for (int i = 0; i < m; i++) {
        string line;
        getline(cin, line);
        istringstream iss(line);
        int cid;
        int preference_level = 0;
        while (iss >> cid) {
            if (cid == 0) break;
            cid--;
            restaurant_preference_level[i][cid] = preference_level++;
        }
    }
    queue<int> q;
    for (int i = 0; i < n; i++) {
        q.push(i);
    }
    while (!q.empty()) {
        int c = q.front();
        q.pop();
        int idx = cidx[c];
        int nr_preferences = int(customer_preferences[c].size());
        if (idx < nr_preferences) {
            // push it to another if possible
            int desired_restaurant = customer_preferences[c][idx];
            PQ &occupants = current_customers[desired_restaurant];
            int restaurant_preference = restaurant_preference_level[desired_restaurant][c];
            if (int(occupants.size()) < cap[desired_restaurant]) {
                occupants.emplace(restaurant_preference, c);
            }
            else if (occupants.top().first > restaurant_preference) {
                auto [_, removed_customer] = occupants.top();
                occupants.pop();

                occupants.emplace(restaurant_preference, c);
                q.push(removed_customer);
            }
            else {
                q.push(c);
            }
            cidx[c]++;
        }
    }
    vector<int> ans;
    for (int r = 0; r < m; r++) {
        while (!current_customers[r].empty()) {
            auto [_, c] = current_customers[r].top();
            current_customers[r].pop();
            ans.push_back(c);
        }
    }
    sort(ans.begin(), ans.end());
    for (int c: ans) cout << c + 1 << '\n';
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
