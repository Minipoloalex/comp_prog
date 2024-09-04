#include <bits/stdc++.h>
using namespace std;

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> ans;
        for (int i = 0; i < n; i++) {
            string s;
            cin >> s;
            for (int a = 0; a < (int) s.size(); a++) {
                if (s[a] == '#') {
                    ans.push_back(a + 1);
                    break;
                }
            }
        }
        reverse(ans.begin(), ans.end());
        for (int a: ans) {
            cout << a << " ";
        }
        cout << '\n';
    }
    return 0;
}