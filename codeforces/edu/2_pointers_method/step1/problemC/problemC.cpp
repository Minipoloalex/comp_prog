#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    int n, m;
    cin >> n >> m;
    vector<int> a(n), b(m);
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int j = 0; j < m; j++) cin >> b[j];

    auto cnt = [](int i, vector<int> &vec) -> int {
        int aux = i;
        for (; aux < int(vec.size()) && vec[i] == vec[aux]; aux++);
        return aux;
    };

    int64_t ans = 0;
    int i = 0, j = 0;
    while (i < n && j < m) {
        if (a[i] < b[j]) {
            i++;
        }
        else if (a[i] > b[j]) {
            j++;
        }
        else {
            assert(a[i] == b[j]);
            int new_i = cnt(i, a);
            int64_t cnta = new_i - i;
            i = new_i;
            int new_j = cnt(j, b);
            int64_t cntb = new_j - j;
            j = new_j;
            ans += cnta * cntb;
        }
    }
    cout << ans << '\n';
    return 0;
}
