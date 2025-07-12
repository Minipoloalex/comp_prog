#include <bits/stdc++.h>
using namespace std;

int char_to_id(char c) {
    if (c >= 'a' && c <= 'z') return c - 'a';
    return c - 'A' + 26;
}

void solve() {
    int n;
    cin >> n;
    string s;
    cin >> s;
    vector<vector<int>> pos(52);
    for (int i = 0; i < n; i++) {
        char c = s[i];
        int id = char_to_id(c);
        pos[id].push_back(i);
    }

    sort(s.begin(), s.end());
    int smallest = n;
    vector<string> cand;
    do {
        for (int p = 1; p < n; p++) {
            bool possible = true;
            for (int i = 0; i + p < n; i++) {
                if (s[i] != s[i + p]) {
                    possible = false;
                    break;
                }
            }
            if (!possible) continue;

            if (p < smallest) {
                smallest = p;
                cand.clear();
                cand.push_back(s);
            }
            else if (p == smallest) {
                cand.push_back(s);
            }
            break;
        }
    } while (next_permutation(s.begin(), s.end()));

    auto diff = [&](const string &cur) {
        int ans = 0;
        vector<int> idxs(52, 0);
        for (int i = 0; i < n; i++) {
            char c = cur[i];
            int id = char_to_id(c);
            int j = pos[id][idxs[id]++];
            ans += abs(j - i);
        }
        return ans;
    };
    int min_diff = INT_MAX;
    for (auto &str: cand) {
        int d = diff(str);
        min_diff = min(min_diff, d);
    }
    if (min_diff == INT_MAX) min_diff = 0;
    cout << smallest << " " << min_diff << '\n';
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
