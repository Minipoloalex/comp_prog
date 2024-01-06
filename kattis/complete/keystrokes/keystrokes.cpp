#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    string inp;
    cin >> inp;
    list<char> res;
    auto cursor = res.begin();
    for (char c: inp) {
        switch (c) {
            case 'L':
                cursor--;
                break;
            case 'R':
                cursor++;
                break;
            case 'B':
                cursor--;
                cursor = res.erase(cursor);
                break;
            default:
                cursor = res.insert(cursor, c);
                cursor++;
        }
    }
    for (char c: res) cout << c;
    cout << endl;
    return 0;
}
