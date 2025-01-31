#include <bits/stdc++.h>
using namespace std;

char new_character(char a) {
    if (a == 'a') return 'b';
    return 'a';
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        string s;
        cin >> s;

        bool found = false;
        for (auto before = s.begin(), it = s.begin() + 1; it != s.end() && !found; before++, it++) {
            char c1 = *before, c2 = *it;
            if (c1 == c2) {
                s.insert(it, new_character(c1));
                found = true;
                break;  // avoid messing with invalid iterators (?)
            }
        }
        if (!found) {
            s.insert(s.begin(), new_character(s[0]));
        }

        cout << s << '\n';
    }
    return 0;
}
