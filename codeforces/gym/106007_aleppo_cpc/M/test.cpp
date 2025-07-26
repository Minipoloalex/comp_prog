#include <bits/stdc++.h>
using namespace std;

void solve() {
    string line;
    while (getline(cin, line)) {
        istringstream iss(line);
        vector<int> arr;
        int v;
        while (iss >> v) {
            arr.push_back(v);
        }
        int ans = 0;
        int n = int(arr.size());
        set<int> s;
        for (int i = 0; i < n; i++) {
            s.insert(arr[i]);
            ans = max(ans, arr[i] | arr[(i + 1) % n]);
        }
        if ((ans == n || (popcount((unsigned int) n) == 1 && ans == n + 2)) && int(s.size()) == n && 
        *s.begin() == 1 && *s.rbegin() == n) {

        }
        else {
            cout << "Wrong: " << n << " " << ans << endl;
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
