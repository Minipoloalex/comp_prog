#include <bits/stdc++.h>
using namespace std;

int main() {
    int T;
    cin >> T;
    cin.ignore();   // ignore \n
    while (T--) {
        string text;
        getline(cin, text);
        list<char> res;
        auto cursor = res.begin();
        for (uint i = 0; i < text.size(); i++) {
            if (text[i] == '<') {
                if (cursor != res.begin()) {
                    cursor--;
                    cursor = res.erase(cursor);
                }
            }
            else if (text[i] == '[') {
                cursor = res.begin();
            }
            else if (text[i] == ']') {
                cursor = res.end();
            }
            else {
                cursor = res.insert(cursor, text[i]);
                cursor++;
            }
        }
        for (char c: res) {
            cout << c;
        }
        cout << endl;
    }
    return 0;
}
