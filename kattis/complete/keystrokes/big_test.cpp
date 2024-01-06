#include <bits/stdc++.h>
using namespace std;

int main() {
    ostringstream oss;
    for (int i = 0; i < 1000000; i++) {
        oss << 'a';
    }
    oss << endl;
    ofstream of("big_test.txt");
    of << oss.str();
    return 0;
}
