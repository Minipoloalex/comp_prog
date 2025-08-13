#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, k; cin >> n >> k;
    cin.ignore();
    
    map<string, int> ids;
    map<int, string> id_to_s;
    map<string, int> f;

    int cur = 0;
    for (int i = 0; i < 3 * n; i++) {
        string s; 
        getline(cin, s);
        id_to_s[cur] = s;
        ids[s] = cur++;
        f[s]++;
    }
     
    vector<pair<int, int>> arr;
    for (auto& [s, c] : f) {
        arr.emplace_back(c, ids[s]);
    }

    sort(arr.begin(), arr.end());

    cur = 0;
    for (int i = int(arr.size()) - 1; cur < k && i >= 0; i--, cur++) {
        auto& [c, id] = arr[i];
        cout << id_to_s[id] << '\n';
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
