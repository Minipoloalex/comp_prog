#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    int n, m;
    cin >> n >> m;
    vector<int> a(n), b(m);
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i < m; i++) cin >> b[i];
  
    vector<int> res;
    {
        int i = 0, j = 0;
        while (i < n && j < m) {
            if (a[i] <= b[j]) res.push_back(a[i++]);
            else res.push_back(b[j++]);
        }
        while (i < n) res.push_back(a[i++]);
        while (j < m) res.push_back(b[j++]);
    }
    for (int v: res) {
        cout << v << " ";
    }
    cout << '\n';
    return 0;
}
