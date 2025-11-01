#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, q;
    cin >> n >> q;

    map<string, int> bank;
    map<string, int> trans;

    string prev, p;
    int mx_tr = 0;
    for (int i = 0; i < q; i++) {
        string name; int cnt;
        cin >> name >> cnt;

        if (bank.find(name) == bank.end()) {
            bank[name] = 100;
        }
        bank[name] -= cnt;

        if (trans.find(name) == trans.end()) {
            trans[name] = 1;
        } else {
            if (prev == name) {
                trans[name]++;
                if (trans[name] > mx_tr) {
                    mx_tr = trans[name];
                    p = name;
                }
            }
            else trans[name] = 1;
        }

        prev = name;
    }

    for (auto & [name, amt] : bank) {
        if (name == p) continue;
        amt += mx_tr;
    }
    bank[p] -= (n - 1) * mx_tr;

    int mna = INT32_MAX, mxa = INT32_MIN;   
    for (auto& [_, amt] : bank) {
        mna = min(mna, amt);
        mxa = max(mxa, amt);
    }

    cout << mxa - mna << '\n';
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
