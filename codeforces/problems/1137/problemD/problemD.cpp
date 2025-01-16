#include <bits/stdc++.h>
using namespace std;

/*
// Much better implementation:

move_result({0, 1});
vector<int> groups = move_result({1});

while (groups[0] != groups[1]) {
    move_result({0, 1});
    groups = move_result({1});
}

while (groups[2] != groups[1]) {
    groups = move_result({0, 1, 2, 3, 4, 5, 6, 7, 8, 9});
}
*/

vector<int> move(vector<int> to_move) {
    cout << "next";
    for (int p: to_move) cout << " " << p;
    cout << endl;
    int g;
    cin >> g;
    vector<int> res(10, 0);
    int id = 1;
    while (g--) {
        string s;
        cin >> s;
        if (s == "stop") assert(1 == 0);
        for (char c: s) {
            res[c - '0'] = id;
        }
        id++;
    }
    return res;
}

void meet_up(int a, int b, int sa, int sb) {
    vector<int> res;
    while (res.empty() || res[a] != res[b]) {
        int i = 0;
        for (; i < sa && i < sb; i++) {
            res = move({a, b});
        }
        for (; i < sa; i++) res = move({a});
        for (; i < sb; i++) res = move({b});
    }
}
bool all_equal(vector<int> &res) {
    if (res.empty()) return true;
    int v = res[0];
    for (int val: res) {
        if (val != v) return false;
    }
    return true;
}

void complete() {
    vector<int> res;
    vector<int> everyone(10);
    iota(everyone.begin(), everyone.end(), 0);
    while (res.empty() || !all_equal(res)) {
        res = move(everyone);
    }
}

void solve() {
    int a = 0, b = 1;
    meet_up(a, b, 1, 2);
    complete();
    cout << "done" << endl;
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    solve();
    return 0;
}
