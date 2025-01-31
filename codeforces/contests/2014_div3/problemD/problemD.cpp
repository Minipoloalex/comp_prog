#include <bits/stdc++.h>
using namespace std;

#define f first
#define s second
using ii = pair<int, int>;

vector<ii> jobs;

ii solve(int n, int d) {
    // cout << "Solving for " << n << " " << d << endl;
    int mn = INT_MAX, mx = INT_MIN;
    int mn_end = -1, mx_end = -1;
    vector<int> cnt_new(n, 0);
    vector<int> cnt_remove(n, 0);
    for (auto &[li, ri]: jobs) {
        cnt_new[li]++;
        if (ri < n - 1) {
            cnt_remove[ri + 1]++;
        }
    }
    // cout << "COUNT NEW:\t";
    // for (int i = 0; i < n; i++) {
    //     cout << cnt_new[i] << " ";
    // }
    // cout << endl;
    // cout << "COUNT REMOVE:\t";
    // for (int i = 0; i < n; i++) {
    //     cout << cnt_remove[i] << " ";
    // }
    // cout << endl;
    int curr = 0;
    for (int i = 0; i < d - 1; i++) {
        curr += cnt_new[i];
    }
    for (int i = d - 1; i < n; i++) {
        curr += cnt_new[i];
        curr -= cnt_remove[i - d + 1];

        if (curr < mn) {
            mn = curr;
            mn_end = i;
        }
        if (curr > mx) {
            mx = curr;
            mx_end = i;
        }
    }
    // cout << "ANS: " << mx << " " << mn << endl;
    return {mx_end - d + 1, mn_end - d + 1};
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    int t;
    cin >> t;
    while (t--) {
        int n, d, k;
        cin >> n >> d >> k;
        jobs.resize(k);
        for (int i = 0; i < k; i++) {
            int li, ri;
            cin >> li >> ri;
            jobs[i] = make_pair(li - 1, ri - 1);
        }
        ii ans = solve(n, d);
        cout << ans.f + 1 << " " << ans.s + 1 << '\n';
    }
    return 0;
}
