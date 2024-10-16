#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    int64_t C;
    int m;
    cin >> C >> m;
    int64_t values[2];
    int idx = 0;
    for (int i = 0; i < m; i++) {
        int64_t ai;
        cin >> ai;
        if (C % ai == 0) {
            values[idx++] = ai;
        }
    }
    cout << min(values[0], values[1]) << " " << max(values[0], values[1]) << '\n';
    return 0;
}
