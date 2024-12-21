#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    int n;
    cin >> n;
    vector<bool> visited(n, false);
    int nn = n;
    while (--nn) {
        int nr;
        cin >> nr;
        visited[nr - 1] = true;
    }
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            cout << i + 1 << '\n';
            break;
        }
    }
    return 0;
}
