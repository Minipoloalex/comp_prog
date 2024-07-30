#include <bits/stdc++.h>
using namespace std;

int main() {
    string pattern = "problem";
    int m = (int) pattern.size();

    string text;
    while (getline(cin, text)) {
        // cout << text << '\n';
        int n = (int) text.size();

        for (int i = 0; i < n; i++) text[i] = (char) tolower(text[i]);

        bool found = false;
        for (int i = 0; i < n - m + 1 && !found; i++) {
            // cout << text[i] << " ";
            bool possible = true;
            for (int j = 0; j < m && possible; j++) {
                if (text[i + j] != pattern[j]) possible = false;
            }
            if (possible) {
                cout << "yes" << '\n';
                found = true;
            }
        }
        if (!found) cout << "no" << '\n';
    }
    return 0;
}
