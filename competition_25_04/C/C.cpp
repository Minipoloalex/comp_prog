#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;

    vector<int> mins(n, 0);

    int c, lmin;
    cin >> c;
    mins[0] = c;

    for (int i = 1; i < n; i++) {
        lmin = INT_MAX;
        for (int j = max(0, i - k - 1); j < i; j++) {
            lmin = min(lmin, mins[j]);
        }
        cin >> c;
        mins[i] = lmin + c;
    }

    cout << mins[n - 1] << '\n';

    return 0;
}