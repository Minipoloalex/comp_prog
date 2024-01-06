#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;

int main() {
    srandom(0);
    int n = random() % 1000 + 1;
    int m = random() % 200 + 1;
    int k = random() % 100 + 1;
    vi c;
    for (int i = 0; i < n; i++) {
        c.push_back((random() % m) +  1);   // [1, m]
    }
    ofstream of("in_custom.txt");
    ostringstream oss;
    oss << n << " " << m << " " << k << endl;
    for (int flav: c) {
        oss << flav << endl;
    }
    of << oss.str();
    return 0;
}
