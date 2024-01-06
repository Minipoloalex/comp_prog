#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;
vi boxes;
typedef unsigned long long ull;

int main() {
    int t, n;
    cin >> t;
    while (t--) {
        cin >> n;
        boxes.resize(n);
        for (int i = 0; i<n;i++) {
            cin >> boxes[i];
        }
        sort(boxes.begin(), boxes.end());
        ull sumLeast = 0;
        ull sumMost = 0;
        ull maxDiff = 0;
        for (int b = 1; b <= n; b++) {
            sumLeast += boxes[b - 1];
            sumMost += boxes[n - b];
            cout << b << " " << sumLeast << " " << sumMost << endl;
            if (n % b != 0) continue;
            if (sumMost - sumLeast > maxDiff) {
                maxDiff = sumMost - sumLeast;
            }
        }
        cout << maxDiff << endl;
    }
    return 0;
}
