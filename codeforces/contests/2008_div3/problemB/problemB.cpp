#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        string s;
        cin >> s;
        int sqsz = int(sqrt(n));
        bool result = true;
        if (sqsz * sqsz != n) {
            result = false;
        }
        for (int i = 0; i < sqsz && result; i++) {
            for (int j = 0; j < sqsz && result; j++) {
                char ch = s[i * sqsz + j];
                if (i == 0 || j == 0 || i == sqsz - 1 || j == sqsz - 1) {
                    if (ch != '1') {
                        result = false;
                    }
                }
                else {
                    if (ch != '0') {
                        result = false;
                    }
                }
            }
        }
        cout << (result ? "Yes" : "No") << '\n';
    }
    return 0;
}
