#include <bits/stdc++.h>
using namespace std;

vector<int> freq;
int n, m, cnt;

const int MAX = int(1e5);
vector<int> factors[MAX + 10];

void setup_factors() {
    for (int i = 1; i <= MAX; i++) {
        for (int j = i; j <= MAX; j += i) { // harmonic series thingy
            factors[j].push_back(i);
        }
    }
}

void include(int value) {
    for (int factor: factors[value]) {
        if (factor > m) break;
        if (freq[factor]++ == 0) cnt++;
    }
}

void exclude(int value) {
    for (int factor: factors[value]) {
        if (factor > m) break;
        if (--freq[factor] == 0) cnt--;
    }
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    int t;
    cin >> t;
    setup_factors();
    while (t--) {
        cin >> n >> m;
        vector<int> a(n);
        for (auto &x: a) cin >> x;
        sort(a.begin(), a.end());

        freq.assign(m + 1, 0);
        cnt = 0;

        int ans = INT_MAX;
        for (int r = 0, l = 0; r < n; r++) {
            include(a[r]);

            while (cnt == m) {
                ans = min(ans, a[r] - a[l]);
                exclude(a[l++]);
            }
        }

        if (ans == INT_MAX) ans = -1;
        cout << ans << '\n';
    }
    return 0;
}
