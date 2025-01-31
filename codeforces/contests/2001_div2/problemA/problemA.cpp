#include <bits/stdc++.h>
using namespace std;

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        // a = a[i], b = a[i + 1]
        // a < b

        vector<int> freq(n + 1, 0);
        for (int i = 0; i < n; i++) {
            int ai; cin >> ai;
            freq.at(ai)++;
        }
        int most_freq = 0;
        for (int i = 1; i < (int) freq.size(); i++) {
            most_freq = max(most_freq, freq[i]);
        }
        cout << n - most_freq << '\n';
    }
    return 0;
}
