#include <bits/stdc++.h>
using namespace std;

int n, m, q;
vector<int64_t> teachers;

int64_t solve(int64_t a) {
    int64_t lo = 0, hi = m - 1;
    int64_t smaller = -INT_MAX, bigger = INT_MAX;
    while (lo <= hi) {
        int64_t med = (lo + hi) / 2;
        if (teachers.at(med) > a) {
            bigger = min(bigger, teachers[med]);
            hi = med - 1;
        }
        else {
            assert(teachers.at(med) < a);
            smaller = max(smaller, teachers[med]);
            lo = med + 1;
        }
    }
    #ifdef HELLO
    cout << smaller << " " << a << " " << bigger << endl;
    #endif
    if (smaller == -INT_MAX) {
        return bigger - 1;
    }
    else if (bigger == INT_MAX) {
        return n - smaller;
    }
    else {
        // int64_t max_diff = max(bigger - a, a - smaller);
        // int64_t min_diff = min(bigger - a, a - smaller);

        return (bigger - smaller) / 2;
    }
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    int t;
    cin >> t;
    while (t--) {
        cin >> n >> m >> q;
        teachers.resize(m);
        for (int i = 0; i < m; i++) {
            cin >> teachers[i];
        }
        sort(teachers.begin(), teachers.end());

        for (int i = 0; i < q; i++) {
            int64_t ai;
            cin >> ai;
            int64_t tm = solve(ai);
            cout << tm << '\n';
        }
    }    
    return 0;
}
