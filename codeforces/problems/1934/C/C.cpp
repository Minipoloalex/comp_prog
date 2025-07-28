#include <bits/stdc++.h>
using namespace std;

int ask(int x, int y) {
    cout << "? " << x << " " << y << endl;
    int d;
    cin >> d;
    return d;
}
void finish(int x, int y) {
    cout << "! " << x << " " << y << endl;
}

void solve() {
    int n, m;
    cin >> n >> m;
    int d = ask(1, 1);
    int rl = min(1 + d, n);
    int cl = 1 + max(0, 1 + d - n);
    int rr = 1 + max(0, 1 + d - m);
    int cr = min(1 + d, m);

    int dl = ask(rl, cl);
    int dr = ask(rr, cr);

    int fromleft_r = rl - dl / 2, fromleft_c = cl + dl / 2;
    int dlast = ask(fromleft_r, fromleft_c);
    if (dlast == 0) {
        finish(fromleft_r, fromleft_c);
    }
    else {
        finish(rr + dr / 2, cr - dr / 2);
    }
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    int t = 1;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
