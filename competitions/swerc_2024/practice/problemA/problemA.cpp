#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long ul;

int main() {
    int n;
    cin >> n;
    
    ul first, before, mx = 0;
    cin >> first;
    before = first;
    for (int i = 1; i < n; i++) {
        ul curr;
        cin >> curr;
        if (curr > before && curr - first > mx) {
            mx = curr - first;
        }
        else if (curr < before) {
            first = curr;
        }
        before = curr;
    }
    cout << mx << '\n';
    return 0;
}
