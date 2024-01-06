#include <bits/stdc++.h>
using namespace std;

vector<int> v;


int main() {
    int t, n;
    cin >> t;
    while (t--) {
        cin >> n;
        if (n == 0) continue;
        
        int val;
        cin >> val;
        bool before = val % 2;
        int currSum = val;
        int best = currSum;
        for (int i = 1; i < n; i++) {
            cin >> val;

            if (currSum < 0 || val % 2 == before) {
                currSum = val;
            }
            else {
                currSum += val;
            }

            if (currSum > best) {
                best = currSum;
            }
            before = val % 2;
        }
        cout << best << endl;
    }
    return 0;
}
