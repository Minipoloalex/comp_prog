#include <bits/stdc++.h>
using namespace std;

void askswap(int x) {
    cout << "swap " << x + 1 << endl;
}
int askthrow(int x) {
    cout << "throw " << x + 1 << endl;
    int ret;
    cin >> ret;
    return ret;
}

void finish(vector<int> ans) {
    cout << "!";
    for (int a: ans) cout << " " << a;
    cout << endl;
}

void solve() {
    int n;
    cin >> n;
    vector<int> order(n);
    iota(order.begin(), order.end(), 0);
    vector<int> d(n + 2);
    vector<int> p(n);
    auto swap_stuff = [&](int x) {
        askswap(x);
        swap(order[x], order[x + 1]);
        swap(p[x], p[x + 1]);
    };
    for (int i = n - 1; i >= 0; i--) {
        if (d[i + 1] == d[i + 2]) {
            // need to use previous guy to help me out
            if (i == 0) {
                swap_stuff(i);  // swap 0 with 1
                int dist = askthrow(i + 1);
                // now it's as if we were on index i + 1 actually
                assert(d[i + 2] != d[i + 3]);
                if (dist == d[i + 2] + 1) {
                    p[i + 1] = 1;
                }
                else {
                    p[i + 1] = 2;
                }
                break;  // or continue
            }
            int dist = askthrow(i - 1);
            if (dist == d[i + 1] + 1) {
                p[i - 1] = 2;
            }
            else {
                assert(dist == d[i + 1] + 2);
                p[i - 1] = 1;
            }
            swap_stuff(i - 1);   // swap i - 1 with i
            d[i] = d[i + p[i]] + 1;
        }
        else {
            int dist = askthrow(i);
            if (dist == d[i + 1] + 1) {
                p[i] = 1;
            }
            else {
                assert(dist == d[i + 2] + 1);
                p[i] = 2;
            }
            d[i] = dist;
        }
    }

    vector<int> ans(n);
    for (int i = 0; i < n; i++) {
        ans[order[i]] = p[i];
    }
    finish(ans);
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
