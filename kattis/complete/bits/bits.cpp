#include <bits/stdc++.h>
using namespace std;

int get_count_1s(uint n) {
    int count_1s = 0;
    while (n > 0) {
        count_1s += n % 2;
        n /= 2;
    }
    return count_1s;
}

int main() {
    int T;
    cin >> T;
    while (T--) {
        uint n;
        cin >> n;
        int max_count_1s = 0;
        while (n > 0) {
            int count_1s = get_count_1s(n);
            if (count_1s > max_count_1s) {
                max_count_1s = count_1s;
            }
            n /= 10;
        }
        cout << max_count_1s << endl;
    }
    return 0;
}
