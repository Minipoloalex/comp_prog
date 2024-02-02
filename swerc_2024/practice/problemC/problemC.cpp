#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long ul;

int main() {
    ul m, k;
    cin >> m >> k;
    if (m % k == 0) {
        cout << "Yes" << '\n';
    }
    else {
        cout << "No" << '\n';
    }
    return 0;
}
