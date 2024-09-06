#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(NULL); ios::sync_with_stdio(false);
    unordered_set<int> s;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int val;
        cin >> val;
        s.insert(val);
    }
    for (int i = 0; i < n - 1; i++) {
        int val;
        cin >> val;
        s.erase(s.find(val));
    }
    int res = *s.begin();
    cout << res << endl;
    return 0;
}
