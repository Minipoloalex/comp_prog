#include <bits/stdc++.h>
using namespace std;

vector<int> el[200010];
vector<int> a;

const int64_t limit = int64_t(1e9);

bool subtree_atleast(int i, int64_t value) {
    if (value > limit) return false;
    if (value <= a[i] && el[i].empty()) return true;
    if (el[i].empty()) return false;

    if (a[i] < value) value = value + value - a[i];     // a[i] + (value - a[i]) * 2

    for (int c: el[i]) {
        if (!subtree_atleast(c, value)) return false;
    }
    return true;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        a.resize(n);

        int64_t sum = 0;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            sum += a[i];
            el[i].clear();
        }
        for (int i = 1; i < n; i++) {
            int p;
            cin >> p;
            el[p - 1].push_back(i);
        }

        auto possible = [&](int64_t value) -> bool {
            if (value <= a[0]) return true;
            if (el[0].empty()) return false;

            for (int c: el[0]) {
                if (!subtree_atleast(c, value - a[0])) return false;
            }
            return true;
        };

        int64_t mn = a[0], mx = min(int64_t(2e9), sum);
        int64_t ans = mn;
        while (mn <= mx) {
            int64_t middle = (mn + mx) / 2;
            if (possible(middle)) {
                mn = middle + 1;
                ans = middle;
            }
            else {
                mx = middle - 1;
            }
        }
        cout << ans << '\n';
    }
    return 0;
}
