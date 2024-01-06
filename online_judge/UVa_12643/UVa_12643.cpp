// Tennis rounds

#include <bits/stdc++.h>
using namespace std;

int main() {
    unsigned int n, i, j;
    while (cin >> n >> i >> j) {
        int round = 1;
        while (i != j) {
            i = (i + 1) / 2;
            j = (j + 1) / 2;
            round++;
        }
        cout << round - 1 << endl;
    }
    return 0;
}
