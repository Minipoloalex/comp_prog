#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;

int main(int argc, char const *argv[]) {
    if (argc != 2) {
        cout << "Wrong number of arguments" << endl;
        return 0;
    }
    string input = "I love CS3233 Competitive Programming. i also love AlGoRiThM";
    string p = argv[1];
    vi r;

    for (int i = 0; i <= input.size() - p.size(); i++) {
        if (input.substr(i, p.size()) == p) {
            r.push_back(i);
        }
    }
    for (int i : r) {
        cout << i << " ";
    }
    if (r.size() == 0) {
        cout << "-1";
    }
    cout << endl;
    return 0;
}
