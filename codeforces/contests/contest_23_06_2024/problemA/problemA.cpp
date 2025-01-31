#include <bits/stdc++.h>
using namespace std;

int main() {
    int t;
    cin >> t;
    while (t--) {
        int x1, x2, x3;
        cin >> x1 >> x2 >> x3;
        int smallest = 100;
        for (int a = 1; a <= 10; a++) {
            int current = abs(x1 - a) + abs(x2 - a) + abs(x3 - a);
            if (current < smallest) {
                smallest = current;
            }
        }
        cout << smallest << '\n';
    }    
    return 0;
}
