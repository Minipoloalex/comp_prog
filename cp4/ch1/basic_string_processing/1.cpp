#include <bits/stdc++.h>
using namespace std;

int main() {
    string r;
    string s;
    while (getline(cin, s)) {
        if (s.substr(0, 7) == ".......") {
            r += s;
            break;
        }
        else {
            r += s + " ";
        }
    }
    cout << r << endl;
}
