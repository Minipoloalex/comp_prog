#include <bits/stdc++.h>
using namespace std;

int main() {
    string s;
    cin >> s;
    int n = int(s.size());

    int max_merge = 0;
    string ans;
    for (int j = 1; j < n; j++) {
        int k = 0;
        for (; k < n && j + k < n && s[k] == s[j + k]; k++);
        if (k - j > max_merge && j + k == n) {
            max_merge = k - j;
            ans = s.substr(0, k);
        }
    }
    // cout << max_merge << '\n';
    if (ans.empty()) cout << "NO\n";
    else cout << "YES\n" << ans << '\n';
    return 0;
}
