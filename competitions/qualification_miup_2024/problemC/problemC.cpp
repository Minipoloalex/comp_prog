#include <bits/stdc++.h>
using namespace std;

int get_int(char c) {
    if (c == 'X') return 1;
    assert(c == '.');
    return 0;
}
char get_char(int v) {
    if (v == 1) return 'X';
    assert(v == 0);
    return '.';
}


int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    int R, K;
    cin >> R >> K;
    string s;
    cin >> s;
    int rules[8];
    for (int i = 0; i < 8; i++) {
        int d = R % 2;
        rules[i] = d;
        R /= 2;
    }
    int n = int(s.size());

    auto get_result = [&](int i) -> char {
        int prev, curr, after;
        curr = get_int(s.at(i));

        if (i == 0) prev = 0;
        else prev = get_int(s.at(i - 1));

        if (i == n - 1) after = 0;
        else after = get_int(s.at(i + 1));

        return get_char(rules[prev * 4 + curr * 2 + after]);
    };

    while (K--) {
        string ns;
        ns.resize(n);
        for (int i = 0; i < n; i++) {
            ns[i] = get_result(i);
        }
        cout << ns << '\n';
        s = ns;
    }
    return 0;
}
