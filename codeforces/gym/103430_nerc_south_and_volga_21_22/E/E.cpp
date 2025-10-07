#include <bits/stdc++.h>
using namespace std;

const int maxn = 42 * int(2e5 + 10);
const int Z = 33;
int t[Z];
int total = 0;
struct node {
    int cnt = 0;
    array<int, 2> next = { 0, 0 };
};

node trie[maxn];

bool trie_insert(string& s) {
    bool ans = true;
    int cur = 0, j = 0;
    int used[Z];
    
    trie[cur].cnt++;
    used[j] = 0;
    if (trie[cur].cnt > t[j++]) {
        ans = false;
    }

    for (int i = 0; i < 32; i++) {
        int bit = s[i] - '0';

        if (trie[cur].next[bit] == 0) {
            trie[cur].next[bit] = ++total;
        }
        cur = trie[cur].next[bit];
        used[j] = cur;

        trie[cur].cnt++;
        if (trie[cur].cnt > t[j++]) {
            ans = false;
        }
    }
    assert(j == Z);

    if (!ans) {
        for (int i = 0; i < Z; i++) trie[used[i]].cnt--;
    }
    return ans;
}

void solve() {
    for (int i = 0; i < Z; i++) cin >> t[i];

    auto parse = [] (string& ip) {
        istringstream iss(ip);
        uint32_t r = 0, num;
        while (iss >> num) {
            r = (r << 8) + num;
            iss.ignore();
        }
        return r;
    };

    auto to_binary = [] (uint32_t n) {
        string r;
        for (uint32_t i = 0; i < 32; i++) {
            if (n & (1LL << i)) r += "1";
            else r += "0";
        }
        reverse(r.begin(), r.end());
        return r;
    };

    int q; cin >> q;
    while (q--) {
        string s; cin >> s;
        uint32_t ip = parse(s);
        string bin = to_binary(ip);

        cout << (trie_insert(bin) ? 'a' : 'b') << '\n';
    }
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    // int t = 1;
    // cin >> t;
    // while (t--) {
        solve();
    // }
    return 0;
}
