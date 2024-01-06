#include <bits/stdc++.h>
using namespace std;

int vp(int p, int n) {  // Legendre's formula
    int res = 0;
    for (int pi = p; pi <= n; pi *= p) { // sum(i=1 -> inf, floor(n/pi))
        res += n/pi;
    }
    return res;
}

int main() {
    cin.tie(NULL);
    ios::sync_with_stdio(false);
    string line;
    while (getline(cin, line)) {
        istringstream iss(line);
        uint n, m;
        while (iss >> n >> m) {
            bool divides;
            if (m == 0) divides = false;
            else if (m <= n) divides = true;
            else {
                // prime factors of m
                uint tmp = m;
                uint pf = 2;
                unordered_map<int, int> factors;
                while (tmp > 1 && ((long long) pf * pf <= tmp)) {
                    int power = 0;
                    while (tmp % pf == 0) {
                        tmp /= pf;
                        power++;
                    }
                    if (power > 0) factors[pf] = power;
                    pf++;
                }
                if (tmp > 1) factors[tmp] = 1;
                divides = true;
                for (auto &[p, e]: factors) {
                    // cout << "p: " << p << ", e: " << e << ", vp: " << vp(p, n) << endl;
                    if (vp(p, n) < e) { // if n! does not support p^e
                        divides = false;
                        break;
                    }
                }
            }
            cout << m << (divides ? " divides " : " does not divide ") << n << "!" << endl;
        }
    }
    return 0;
}
