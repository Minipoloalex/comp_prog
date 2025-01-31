#include <bits/stdc++.h>
using namespace std;

typedef list<int> li;

li read_list(int n) {
    li l;
    for (int i = 0; i < n; i++) {
        int a;
        cin >> a;
        l.push_back(a);
    }
    return l;
}

int main() {
    cin.tie(NULL)->ios::sync_with_stdio(false);
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        li ma = read_list(n);
        li mb = read_list(n);

        int left_a = 0, left_b = 0;
        int total_a = 0, total_b = 0;
        for (auto ita = ma.begin(), itb = mb.begin(); ita != ma.end(); ) {
            int a = *ita;
            int b = *itb;

            if (a == b && a != 0) { // harder decision required
                ita++;
                itb++;
                left_a += a;
                left_b += b;
                continue;
            }
            else if (a > b) {    // choose a
                total_a += a;
            }
            else if (b > a) {   // choose b
                total_b += b;
            }
            ita = ma.erase(ita);
            itb = mb.erase(itb);
        }

        for (auto ita = ma.begin(), itb = mb.begin(); ita != ma.end(); ita++, itb++) {
            int a = *ita;
            int b = *itb;

            int sums_a = left_a + total_a;
            int sums_b = left_b + total_b;
            if (a == -1) {  // also b == -1
                if (sums_a > sums_b || (sums_a == sums_b && total_a > total_b)) {
                    total_a += a;
                    // cout << "Chose a" << endl;
                }
                else {
                    total_b += b;
                    // cout << "Chose b" << endl;
                }
            }
            else if (a == 1) {
                if (sums_a > sums_b || (sums_a == sums_b && total_a > total_b)) {
                    total_b += b;
                    // cout << "Chose b" << endl;
                }
                else {
                    total_a += a;
                    // cout << "Chose a" << endl;
                }
            }
            left_a -= a;
            left_b -= b;
        }
        cout << min(total_a, total_b) << '\n';
    }

    return 0;
}
