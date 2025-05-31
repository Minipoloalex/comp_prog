#include <bits/stdc++.h>
using namespace std;

const int INF = int(1e6);

vector<int> get_divs(int x) {
    vector<int> ans;
    for (int i = 1; i * i <= x; i++) {
        if (x % i == 0) {
            ans.push_back(i);
            if (x / i != i) {
                ans.push_back(x / i);
            }
        }
    }
    sort(ans.begin(), ans.end());
    return ans;
}

void solve() {
    int x, y, k;
    cin >> x >> y >> k;
    int g = gcd(x, y);
    x /= g;
    y /= g;
    vector<int> dp;
    function<int(int,vector<int>&)> go = [&](int i, vector<int> &divs) {
        if (i == 0) return 0;

        int &ans = dp[i];
        if (ans != -1) return ans;

        int cur = INF;
        for (int j = 0; j < i; j++) {
            if (divs[i] % divs[j] == 0) {
                int div = divs[i] / divs[j];
                if (div <= k) {
                    cur = min(cur, go(j, divs) + 1);
                }
            }
        }
        return ans = cur;
    };
    
    vector<int> divx = get_divs(x), divy = get_divs(y);

    dp.assign(divx.size(), -1);
    int ansx = go((int)divx.size() - 1, divx);

    dp.assign(divy.size(), -1);
    int ansy = go((int)divy.size() - 1, divy);

    if (ansx >= INF || ansy >= INF) {
        cout << "-1\n";
    }
    else {
        cout << ansx + ansy << '\n';
    }
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
