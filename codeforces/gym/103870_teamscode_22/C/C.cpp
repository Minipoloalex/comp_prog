#include <bits/stdc++.h>
using namespace std;


void solve() {
    vector<int> days = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    bitset<365> calendar;
    int n; cin >> n;
    for (int i = 0; i < n; i++) {
        int a, b, c;
        cin >> a >> b >> c;

        int day = b - 1;
        for (int j = 0; j < a - 1; j++) {
            day += days[j];
        }

        for (; day < 365; day += c) {
            calendar[day] = 1;
        }
    }

    int mx = 0;
    for (int i = 0; i < 365; i++) {
        if (calendar[i] == 1) continue;

        int j = i;
        while (j < 365 && calendar[j] == 0) j++;

        mx = max(mx, j - i);
        i = j;
    }

    cout << mx << '\n';
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
