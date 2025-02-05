#include <bits/stdc++.h>
using namespace std;

const int MOD = int(1e9) + 7;

const int MAX_STRING_SIZE = int(1e6);

int trie[MAX_STRING_SIZE][26];
bool stop[MAX_STRING_SIZE];  // modify to int if non-unique words
int node_cnt = 0;

void trie_insert(const string &word) {
    int node = 0;
    for (char c: word) {
        int ch = c - 'a';
        if (trie[node][ch] == 0) {
            trie[node][ch] = ++node_cnt;
        }
        node = trie[node][ch];
    }
    stop[node] = true;
}
string s;
int n;
vector<int> dp;
int solve_dp(int i) {
    if (i == n) return 1;

    int &ans = dp[i];
    if (ans != -1) return ans;

    int cur = 0;
    int node = 0;
    for (int j = i; j < n; j++) {
        int ch = s[j] - 'a';
        node = trie[node][ch];
        if (node == 0) break;   // does not exist in the trie
        if (stop[node]) {
            (cur += solve_dp(j + 1)) %= MOD;
        }
    }
    cur = (cur + MOD) % MOD;
    return ans = cur;
}

void solve() {
    cin >> s;
    n = int(s.size());
    dp.assign(n, -1);

    int k;
    cin >> k;
    while (k--) {
        string word;
        cin >> word;
        trie_insert(word);
    }
    int ans = solve_dp(0);
    cout << ans << '\n';
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    solve();
    return 0;
}
