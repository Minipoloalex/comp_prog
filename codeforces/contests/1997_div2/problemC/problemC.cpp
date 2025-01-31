#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;   // even
        string s;
        cin >> s;

        int64_t ans = 0;
        vector<int> open(1, 0); // indices of currently open parenthesis
        for (int i = 1; i < n; i++) {
            if (s[i] == ')') {
                ans += (i - open.back());
                open.pop_back();
            }
            else if (s[i] == '(') {
                open.push_back(i);
            }
            else {  // s[i] == '_'
                if (open.empty()) {
                    open.push_back(i);
                }
                else {
                    // open.size() == 2
                    ans += (i - open.back());
                    open.pop_back();
                }
            }
        }
        cout << ans << '\n';
    }
    return 0;
}
