#include <bits/stdc++.h>
using namespace std;

// A border of a string is a prefix that is also a suffix of the string but not the whole string.
// KMP[i + 1]: contains the length of the longest border of the prefix of P that ends at i
// Example: "abacababc": kmp = [-1, 0, 0, 1, 0, 1, 2, 3, 2, 0]

// Don't confuse the prefix of the border definition with this prefix.
// Here, the prefix that ends at i takes the role of the whole string in the border definition

// Pattern preprocessed (back jumps): [-1, 0, ...]
vector<int> kmp;

// pattern p
void kmpPreprocess(const string &p) {
    int sz = int(p.size());
    kmp.resize(sz + 1);

    int l = -1, r = 0;
    kmp[0] = -1;
    while (r < sz) {    // l < r
        while (l >= 0 && p[r] != p[l]) l = kmp[l];
        l++; r++;

        // Here, we have l >= 0 and r >= 1
        // Comparison of the i'th character corresponds to
        // the (i + 1)'th position in the array
        kmp[r] = l;
    }
}


string solve() {
    string s;
    cin >> s;
    int n = int(s.size());

    int l = 0, r = n - 1;
    while (l < r && s[l] == s[r]) {
        l++; r--;
    }
    // Prefix s[0:l-1] is palindrome with s[r+1:n-1]
    // Cannot assume s[l] == s[r]
    // The whole string is palindrome if l >= r
    // if l == r, mid character is the same (odd size)
    // if l > r, we have checked every character (even size)

    if (l >= r) return s;
    int sz_mid = r - l + 1;
    string mid = s.substr(l, sz_mid); // substring s[l:r]

    string rev = mid;
    reverse(rev.begin(), rev.end());

    auto find_longest = [](string &normal, string &reversed) {
        string pref_kmp = normal + '#' + reversed;
        kmpPreprocess(pref_kmp);
        int ksz = (int) kmp.size();
        return kmp[ksz - 1];
    };
    int longest_pref = find_longest(mid, rev);
    int longest_suf = find_longest(rev, mid);

    string mid_ans;
    if (longest_pref > longest_suf) {
        mid_ans = mid.substr(0, longest_pref);
    }
    else {
        mid_ans = rev.substr(0, longest_suf);
    }
    return s.substr(0, l) + mid_ans + s.substr(r + 1);
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    int t;
    cin >> t;
    while (t--) {
        cout << solve() << '\n';
    }
    return 0;
}
