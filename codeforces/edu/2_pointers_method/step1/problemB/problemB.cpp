#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    
    int n, m;
    cin >> n >> m;
    vector<int> a(n), b(m);
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int j = 0; j < m; j++) cin >> b[j];

    int i = 0;
    for (int j = 0; j < m; j++) {
        for (; i < n && a.at(i) < b.at(j); i++);
        cout << i << " ";
    }
    cout << '\n';
    return 0;
}
