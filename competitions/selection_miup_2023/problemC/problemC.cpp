#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0); ios::sync_with_stdio(0);
    string code;
    cin >> code;
    bool correct = false;
    vector<string> str;
    for (int t = 0; t < 7; t++) {
        string s;
        cin >> s;
        str.push_back(s);
    }
    for (int t = 0; t < 7 && !correct; t++) {
        string s = str[t];
        // cout << s << endl;
        bool matched[5] = {false,false,false,false,false};
        
        char to_print[5] = {'X','X','X','X','X'};
        for (int i = 0; i < 5; i++) {
            if (code[i] == s[i]) {
                to_print[i] = 'G';
                matched[i] = true;  // indicates code[i] == s[i]
            }
        }
        for (int i = 0; i < 5; i++) {   // through s
            for (int j = 0; j < 5; j++) {   // through code
                if (matched[j] == false && s[i] == code[j] && i != j && s[i] != code[i] && s[j] != code[j]) {
                    // cout << "i: " << i << ", s[i] = " << s[i] << ", j: " << j << ", s[j] = " << s[j] << endl;
                    matched[j] = true;
                    to_print[i] = 'Y';
                    break;
                }
            }
        }
        correct = true;
        for (int i = 0; i < 5; i++) {
            if (code[i] != s[i]) {
                correct = false;
                break;
            }
        }
        if (t == 6 || correct) {
            if (correct) {
                cout << "WINNER" << endl;
            }
            else cout << "LOSER" << endl;
        }
        else {
            for (int i = 0; i < 5; i++) {
                cout << to_print[i];
            }
            cout << endl;
        }
    }
    return 0;
}
