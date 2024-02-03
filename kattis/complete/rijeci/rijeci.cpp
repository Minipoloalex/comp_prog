#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> ii;  // (count A, count B)
const int MAX_N = 50;
ii ct[MAX_N];

int main() {
    int k;
    cin >> k;
    ct[0] = make_pair(1, 0);
    ct[1] = make_pair(0, 1);
    for (int i = 2; i <= k; i++) {
        int ct_a1 = ct[i - 1].first;
        int ct_b1 = ct[i - 1].second;
        int ct_a2 = ct[i - 2].first;
        int ct_b2 = ct[i - 2].second;
        ct[i] = make_pair(ct_a1 + ct_a2, ct_b1 + ct_b2);
    }
    cout << ct[k].first << " " << ct[k].second << '\n';
    return 0;
}
