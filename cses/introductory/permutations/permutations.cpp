#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    int n;
    cin >> n;
    if (n > 1 && n <= 3) {
        cout << "NO SOLUTION\n";
    }
    else if (n == 4) {
        cout << "3 1 4 2\n";
    }
    else {
        vector<int> ans;
        for (int i = 1; i <= n; i += 2) {
            cout << i << " ";
        }
        for (int i = 2; i <= n; i += 2) {
            cout << i << " ";
        }

        cout << '\n';
    }
    return 0;
}
