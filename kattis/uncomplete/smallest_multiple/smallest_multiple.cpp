#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long ull;

int main() {
    string line;
    while (getline(cin, line)) {
        istringstream iss(line);
        ull n;
        ull _lcm = 1;
        while (iss >> n) _lcm = lcm(_lcm, n);
        cout << _lcm << endl;
    }
    return 0;
}

// WA
