#include <bits/stdc++.h>
using namespace std;

vector<int> divs(int n) {
    vector<int> ans;
    for (int64_t i = 1; i * i <= n; i++) {
        if (n % i == 0) {
            ans.push_back(int(i));
            ans.push_back(int(n / i));
        }
    }
    ans.push_back(n);
    sort(ans.begin(), ans.end());
    return ans;
}

void set_intersection(vector<int> &A, vector<int> &B, vector<int> &res) {
    for (int v: A) {
        auto it = lower_bound(B.begin(), B.end(), v);
        if (it != B.end() && *it == v) {
            res.push_back(v);
        }
    }
}

void solve() {
    int w, l;
    cin >> w >> l;
    vector<int> divW[3], divL[3];
    for (int i = w - 2; i <= w; i++) {
        divW[i - (w - 2)] = divs(i);
    }
    for (int i = l - 2; i <= l; i++) {
        divL[i - (l - 2)] = divs(i);
    }
    set<int> ans;
    for (int a = w - 2; a <= w; a++) {
        vector<int> &A = divW[a - (w - 2)];
        for (int b = w - 2; b <= w; b++) {
            vector<int> &B = divW[b - (w - 2)];
            for (int c = l - 2; c <= l; c++) {
                vector<int> &C = divL[c - (l - 2)];
                for (int d = l - 2; d <= l; d++) {
                    vector<int> &D = divL[d - (l - 2)];
                    if (a + b + c + d == w + w + l + l - 4) {
                        // possible, so let's get intersection of all
                        vector<int> resA, resB, res;
                        set_intersection(A, B, resA);
                        set_intersection(C, D, resB);
                        set_intersection(resA, resB, res);
                        for (int v: res) {
                            ans.insert(v);
                        }
                    }
                }
            }
        }
    }
    cout << ans.size();
    for (int v: ans) {
        cout << " " << v;
    }
    cout << '\n';
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
