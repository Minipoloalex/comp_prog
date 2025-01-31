#include <bits/stdc++.h>
using namespace std;

int h, n;
vector<int64_t> a, c;
/**
 * @brief Binary search solution: leads to overflow (on calculating the attack damage)
 * 

bool dead(int64_t rounds) {
    int64_t hp = h;
    for (int i = 0; i < n && hp > 0; i++) {
        int64_t atk_cnt = (rounds - 1) / c[i] + 1;
        int64_t dmg = atk_cnt * a[i];   // overflow here
        hp -= dmg;
    }
    return hp <= 0;
}

void solve() {
    cin >> h >> n;
    a.resize(n); c.resize(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i < n; i++) cin >> c[i];
    int64_t mn = 1, mx = int64_t(1e11);
    int64_t ans = 0;
    while (mn <= mx) {
        int64_t middle = (mn + mx) / 2;
        if (dead(middle)) {
            ans = middle;
            mx = middle - 1;
        }
        else mn = middle + 1;
    }
    cout << ans << '\n';
}

*/

/**
 * @brief Priority queue solution
 * 
 */
void solve() {
    cin >> h >> n;
    a.resize(n); c.resize(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i < n; i++) cin >> c[i];

    set<pair<int64_t, int>> s;
    for (int i = 0; i < n; i++) {
        s.emplace(1, i);
    }

    int64_t ans = 0;
    while (h > 0) {
        auto it = s.begin();
        auto [rnd, i] = *it;
        s.erase(it);
        h -= (int) a[i];
        ans = rnd;

        rnd += c[i];
        s.emplace(rnd, i);
    }
    cout << ans << '\n';
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);

    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
