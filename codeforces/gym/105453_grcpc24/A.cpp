#include <bits/stdc++.h>
using namespace std;


int length;
int read_egg() {
    string s;
    cin >> s;
    length = (int) s.size();
    int ans = 0;
    for (char c: s) {
        ans <<= 1;
        ans += c - '0';
    }
    return ans;
}

string to_bin(int value) {
    int sz = length;
    string s;
    for (int i = sz - 1; i >= 0; i--) {
        int ch = (value & (1 << i)) >> i;
        char c = char('0' + ch);
        s += c;
    }
    return s;
}


void solve() {
    int n, m, k;
    cin >> n >> m >> k;
    vector<int> egg(n);
    for (auto &e: egg) {
        e = read_egg();
    }
    
    vector<int> dep(n, -1);

    while (m--) {
        int a, b;
        cin >> a >> b;
        a--;b--;
        dep[b] = a;
    }
    vector<int> negg(n);
    while (--k) {
        for (int i = 0; i < n; i++) {
            negg[i] = egg[i];
            if (dep[i] != -1) {
                negg[i] ^= egg[dep[i]];
            }
        }
        egg = negg;
    }
    for (int i = 0; i < n; i++) {
        cout << to_bin(egg[i]) << " \n"[i == n - 1];
    }
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    solve();
    return 0;
}
