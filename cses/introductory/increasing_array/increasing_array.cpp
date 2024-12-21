#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    int n;
    cin >> n;

    int curr = 1;
    int64_t ans = 0;
    for (int i = 0; i < n; i++) {
        int a;
        cin >> a;
        int aux = max(a, curr);
        ans += max(0, curr - a);
        curr = aux;
    }
    cout << ans << '\n';
    return 0;
}
