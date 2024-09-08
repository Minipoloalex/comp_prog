#include <bits/stdc++.h>
using namespace std;

int main() {
    // ["aadddd", "qwertyyy"]
    string s = "qwertyyy";
    sort(s.begin(), s.end());
    do {
        cout << s << endl;
    } while(next_permutation(s.begin(), s.end()));
    cout << endl;
    return 0;
}
