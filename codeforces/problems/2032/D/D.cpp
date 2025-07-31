#include <bits/stdc++.h>
using namespace std;

int ask(int a, int b) {
    cout << "? " << a << " " << b << endl;
    int r;
    cin >> r;
    if (r == -1) exit(0);
    return r;
}
void finish(vector<int> p, int n) {
    cout << "!";
    for (int i = 1; i < n; i++) {
        cout << " " << p[i];
    }
    cout << endl;
}

void solve() {
    int n;
    cin >> n;
    int smallest = -1;
    vector<int> p(n);
    p[1] = 0;
    for (int i = 2; i < n; i++) {
        if (ask(1, i) == 0) {
            p[i] = 1;
            smallest = i;
            break;
        }
        else {
            p[i] = 0;
        }
    }
    int cur = 2;
    for (int i = smallest + 1; i < n; i++) {
        for (int j = cur; j < n; j++) {
            if (ask(i, j) == 0) {
                p[i] = j;
                cur = j + 1;
                break;
            }
        }
    }

    // test with ~flat tree
    // 0 1, 0 2, 0 3, 0 4, 0 5, 1 6, 6 7: |queries| = 2 * n - 6 (exactly the limit)
    finish(p, n);
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
