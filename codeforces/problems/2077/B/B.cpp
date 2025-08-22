#include <bits/stdc++.h>
using namespace std;


void solve() {
    // int x = 0, y = 0;
    string sq1;
    for (int i = 0; i < 15; i++) {  // "0" followed by 14 times "10"
        sq1 += "10";
    }
    cout << stoi(sq1, nullptr, 2) << endl;
    int q1val = int(bitset<30>(sq1).to_ulong());

    int q1ans;
    cin >> q1ans;
    string s1 = bitset<31>(q1ans).to_string();

    reverse(sq1.begin(), sq1.end());
    reverse(s1.begin(), s1.end());

    bitset<30> done;
    bitset<30> x, y;

    int carry1 = 0;
    for (int i = 0; i < 30; i++) {
        int d1 = s1[i] - '0';
        int dq1 = sq1[i] - '0';
        if (dq1 == 0) {
            if (d1 != carry1) {
                // one of them has it
                done.set(i);
                x.set(i);
            }
            else {
                // either both have, or none
            }
        }
        else if (dq1 == 1) {
            if (i > 0 && !done[i - 1]) {
                done.set(i - 1);
                if (d1 == 1) {
                    // means that carry was 1, meaning that both previous bits were actually one
                    x.set(i-1);
                    y.set(i-1);
                }
            }
            carry1 = 1;
        }
    }

    string sq2;
    for (int i = 0; i < 15; i++) {  // "1" followed by 14 times "01"
        sq2 += "01";
    }
    int q2val = int(bitset<30>(sq2).to_ulong());
    cout << stoi(sq2, nullptr, 2) << endl;

    int q2ans;
    cin >> q2ans;
    string s2 = bitset<31>(q2ans).to_string();

    reverse(sq2.begin(), sq2.end());
    reverse(s2.begin(), s2.end());

    // int carry2 = 1;
    for (int i = 0; i < 30; i++) {
        int d2 = s2[i] - '0';
        int dq2 = sq2[i] - '0';
        if (dq2 == 0) {
            // we know we had a 1 before, so we know carry2 is 1
            if (d2 == 0) {
                x.set(i);
                done.set(i);
            }
            else {
                // unknown for now
            }
        }
        else if (dq2 == 1) {
            if (i > 0 && !done[i - 1]) {
                done.set(i - 1);
                if (d2 == 1) {
                    x.set(i - 1);
                    y.set(i - 1);
                }
            }
        }
    }

    int xv = int(x.to_ulong());
    int yv = int(y.to_ulong());
    cout << "!" << endl;
    int m;
    cin >> m;
    // for (int i = 0; i < 30; i++) {
    //     if (!done[i]) {
    //         cout << i << endl;
    //     }
    // }
    auto correct = [&](int qval, int qans) {
        return (xv | qval) + (yv | qval) == qans;
    };
    if (!done[29]) {
        done.set(29);
        if (!correct(q1val, q1ans) || !correct(q2val, q2ans)) {
            xv |= (1 << 29);
            if (!correct(q1val, q1ans) || !correct(q2val, q2ans)) {
                yv |= (1 << 29);
            }
        }
    }
    assert(correct(q1val, q1ans) && correct(q2val, q2ans));
    // cout << xv << " " << yv << " ";

    cout << (xv | m) + (yv | m) << endl;
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
