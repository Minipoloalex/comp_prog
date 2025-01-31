#include <bits/stdc++.h>
using namespace std;

bitset<1000000> bs;
bitset<1000000> bsa;
bitset<1000000> bsb;

typedef vector<int> vi;

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n, m, k;
        cin >> n >> m >> k;
        int half_k = k/2;
        vi a(n), b(m);
        int sz_a = 0;
        
        bs.reset();
        bsa.reset();
        bsb.reset();

        for (int i = 0; i < n; i++) {
            int v;
            cin >> v;
            if (v <= k) {
                a[i] = v;
                sz_a++;
                bs.set(v);
                bsa.set(v);
            }
        }
        int sz_b = 0;
        for (int i = 0; i < m; i++) {
            int v;
            cin >> v;
            if (v <= k) {
                b[i] = v;
                sz_b++;
                bs.set(v);
                bsb.set(v);
            }
        }
        bool over = false;
        for (int i = 1; i <= k; i++) {
            if (!bs[i]) {
                cout << "NO" << '\n';
                over = true;
                break;
            }
        }
        if (over) continue;
        int cta_unique = 0, ctb_unique = 0;
        for (int i = 1; i <= k; i++) {
            if (bsa[i] && !bsb[i]) {
                cta_unique++;
            }
            else if (!bsa[i] && bsb[i]) {
                ctb_unique++;
            }
        }
        if (cta_unique > half_k || ctb_unique > half_k) {
            cout << "NO" << '\n';
            over = true;
        }
        if (over) continue;
        cout << "YES" << '\n';
    }
    return 0;
}
