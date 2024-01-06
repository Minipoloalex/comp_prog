#include <bits/stdc++.h>
using namespace std;

int number_of_digits_of_factorial(int n) {  // use log(a * b) = log(a) + log(b)
    double res = 0;
    for (int i = 2; i <= n; i++) {
        res += log2(i);
    }
    return (int) floor(1 + res - 1e-9);
}

int main() {
    int n;
    while (cin >> n) {
        if (n == 0) break;
        int ten = (n - 1960) / 10;
        int bits = 4 * (1 << ten);
        int a = 3;
        int b = bits;
        int best = 0;
        while (a <= b) {
            int m = (a + b) / 2;
            int bin_digits = number_of_digits_of_factorial(m);
            if (bin_digits <= bits) {
                if (m > best) best = m;
                a = m + 1;
            }
            else b = m - 1;
        }
        cout << best << endl;
        
    }
    return 0;
}
