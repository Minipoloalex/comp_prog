#include <bits/stdc++.h>
using namespace std;

int main() {
    int c = 1;
    int n;
    while (cin >> n) {
        int val;
        int min = 1e9;
        int max = -1e9;
        while (n--) {
            cin >> val;
            if (val < min) min = val;
            if (val > max) max = val;
        }
        printf("Case %d: %d %d %d\n", c++, min, max, max - min);
    }
    return 0;
}
