#include <bits/stdc++.h>
using namespace std;

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        string s;
        cin >> s;
        cout << ((s[0] == s[n - 1]) ? "NO\n" : "YES\n");
    }
    return 0;
}