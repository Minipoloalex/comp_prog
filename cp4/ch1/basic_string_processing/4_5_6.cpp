#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long ll;
typedef vector<string> vs;
typedef vector<int> vi;
typedef pair<string, int> si;
typedef map<string, int> msi;

vs main_exercise_4() {
    string input = "i love cs3233 competitive programming. i also love algorithm";
    vs res;
    string current;
    for (ll i = 0; i < input.size(); i++) {
        char c = input[i];
        if (c == '.' || c == ' ') {
            if (!current.empty()) {
                res.push_back(current);
                current.clear();
            }
        }
        else current += c;
    }
    if (!current.empty()) {
        res.push_back(current);
    }

    sort(res.begin(), res.end());
    // cout << "[ ";
    // for (ll i = 0; i < res.size(); i++) {
    //     cout << res[i] << " ";
    // }
    // cout << "]\n";
    return res;
}

int main_exercise_5() {
    vs sorted_tokens = main_exercise_4();
    msi m;
    for (const string &s: sorted_tokens) {
        m[s]++;
    }
    string most_frequent;
    int mf = 0;
    for (const auto &[s, freq]: m) {
        if (freq > mf) {
            most_frequent = s;
            mf = freq;
        }
    }
    cout << "Most frequent string: " << most_frequent << ", frequency: " << mf << endl;
    return 0;
}

int size_unknown_string() {
    const char *input = "after the first input block, there will be one loooooooooooong line...";
    int i;
    for (i = 0; input[i] != '\0'; i++) {}
    int &size = i;
    cout << "Size of the string is: " << size << endl;
    return 0;
}

int main() {
    size_unknown_string();
    main_exercise_5();
    return 0;
}
