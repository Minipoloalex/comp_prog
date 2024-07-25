#include <bits/stdc++.h>
using namespace std;

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        int max_count = 0;
        int current_count = -1;
        for (int i = 0; i < n; i++) {
            char c;
            cin >> c;
            // cout << "'" << c << "'" << endl;
            if (c == 'A') {
                max_count = max(max_count, current_count);
                current_count = 0;
            }
            else if (c == 'P') {
                if (current_count != -1) {
                    current_count++;
                    max_count = max(max_count, current_count);
                }
            }
        }
        cout << max_count << endl;
    }
    return 0;
}
