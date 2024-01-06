#include <bits/stdc++.h>
using namespace std;

int main() {
    string text;
    getline(cin, text);
    string res;
    for (uint i = 0; i < text.size(); i++) {
        if (text[i] == '<') {
            res.pop_back();
        }
        else res.push_back(text[i]);
    }
    cout << res << endl;
    return 0;
}
