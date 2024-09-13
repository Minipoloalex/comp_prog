#include <bits/stdc++.h>
using namespace std;

vector<int> kmp;

void kmpPreprocess(const string &p) {
    int sz = int(p.size());
    kmp.resize(sz + 1);

    int l = -1, r = 0;
    kmp[0] = -1;
    while (r < sz) {    // l < r
        while (l >= 0 && p[r] != p[l]) l = kmp[l];
        l++; r++;

        // Here, we have l >= 0 and r >= 1
        // Comparison of the i'th character corresponds to the (i + 1)'th position in the array)
        kmp[r] = l;
    }
}

/**
 * @brief 
 * 
 * @param p 
 * @param t 
 */
void kmpSearch(const string &p, const string &t) {
    int n = int(t.size());
    int m = int(p.size());
    int i = 0, j = 0;   // i loops through text, j through pattern
    while (i < n) {
        while (j >= 0 && t[i] != p[j]) j = kmp[j];
        i++; j++;
        if (j == m) {
            cout << "Match found starting at index " << i - j << '\n';
            j = kmp[j];  // continue looking for more matches 
        }
    }
}

int main() {
    // p: ["abra"]
    // t: ["abrabra", "abrakadabra"]
    string p = "ababaaba";
    string t = "abcabab abababaabac abababaabac";
    kmpPreprocess(p);
    for (int v: kmp) {
        cout << v << " ";
    }
    cout << endl;
    kmpSearch(p, t);

    return 0;
}
