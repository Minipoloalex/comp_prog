#include <bits/stdc++.h>
using namespace std;

int ask(int i, int x) {
    cout << "? " << i << " " << x << endl;
    int res;
    cin >> res;
    if (res == -1) exit(1);
    return res;
}

vector<int> ask(vector<int> &qry, int bit) {
    vector<int> ans; ans.reserve(qry.size());
    for (int ind: qry) {
        ans.push_back(ask(ind,1<<bit));
    }
    return ans;
}

void finish(int x) {
    cout << "! " << x << endl;
}

void solve() {
    int n;
    cin >> n;
    vector<int> active(n-1);
    iota(active.begin(), active.end(), 1);
    vector<int> nxt; nxt.reserve(n);
    array<int,2> freq{}, real{};
    int x = 0;
    for (int bit = 0; bit < 20; bit++) {
        vector<int> res = ask(active,bit);
        freq[0] = freq[1] = real[0] = real[1] = 0;
        for (int val: res) {
            freq[val]++;
        }
        int mask = ((1 << bit) - 1);
        for (int i = 1; i <= n; i++) {
            if (((mask & i) == x)) {
                real[bool((1<<bit)&i)]++;
            }
        }
        int chosen = freq[0] < real[0] ? 0 : 1;
        if (chosen) {
            x |= (1 << bit);
        }
        for (int i = 0; i < int(active.size()); i++) {
            if (res[i] == chosen) {
                nxt.push_back(active[i]);
            }
        }
        swap(nxt,active);
        nxt.clear();
    }
    finish(x);
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int t = 1;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
