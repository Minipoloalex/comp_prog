#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;
typedef vector<char> vc;
typedef vector<vc> vvc;

vi a;
vvc ct_to_char;


int main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        a.resize(n);
        ct_to_char.assign(n + 1, vc());
        for (int i = 0; i < 26; i++) {
            ct_to_char[0].push_back('a' + (char) i);
        }
        string line;
        for (int i = 0; i < n; i++) {
            int v;
            cin >> v;
            vc &chars = ct_to_char[v];
            char c = chars[chars.size() - 1];
            // cout << c << '\n';
            line += c;
            chars.pop_back();

            ct_to_char[v + 1].push_back(c);
        }
        cout << line << '\n';
    }
    return 0;
}
