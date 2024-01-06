#include <bits/stdc++.h>
using namespace std;

int numberOfDigits(int a) {
    return (int) floor(1+log2((double)a));
}

int main() {
    cin.tie(0); ios::sync_with_stdio(0);
    int Q;
    cin >> Q;
    
    int m[4] = {0, 0, 0, 0};
    int a, b, c, d;
    char t;
    
    cin >> a >> t >> b >> t >> c >> t >> d;
    m[0] = a; m[1] = b; m[2] = c; m[3] = d;
    Q--;
    bool diff[4] = {false, false, false, false};
    while (Q--) {
        int ai, bi, ci, di; // [0, 255]
        cin >> ai >> t >> bi >> t >> ci >> t >> di;
        if (ai != a) diff[0] = true;
        if (bi != b) diff[1] = true;
        if (ci != c) diff[2] = true;
        if (di != d) diff[3] = true;
        m[0] = max(ai, m[0]);
        m[1] = max(bi, m[1]);
        m[2] = max(ci, m[2]);
        m[3] = max(di, m[3]);
    }
    int first = 4;
    for (int i = 0; i < 4; i++) {
        if (diff[i]) {
            first = i;
            break;
        }
    }
    // cout << first << endl;
    int min_bits = 0;
    for (int i = first; first < 4; first++) {
        int bits = numberOfDigits(m[i]);
        min_bits += bits;
    }
    int res = 32 - min_bits;
    if (res == 0) cout << 32 << endl;
    else cout << res << endl;
    // never output 0
    return 0;
}
