
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

void solve() {
    string s;
    cin >> s;
    kmpPreprocess(s);

    int n = int(s.size());
    vector<int> cnt(n + 1, 0);
    for (int i = 1; i < (int) kmp.size(); i++) {
        cnt[kmp[i]]++;
    }

    // Follows the tree drawn on paper
    // THIS DOES NOT WORK!!!
    // because we need to process big numbers before processing smaller numbers
    // for (int i = int(kmp.size() - 1); i > 0; i--) {  // i means kmp location
    //     if (kmp[i] > 0) {
    //         // does not account for bigger values having "contained" smaller values
    //         // for example:
    //         // ... 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 ...
    //         // maybe the 10 includes a 5 like ABABA + ABABA
    //         // so, when we account for that 5, we cannot just add 1 to its kmp parent
    //         // we need to add as many times as it occurred

    //         cnt[kmp[kmp[i]]]++;
    //     }
    // }

    // process each number separately in descending order
    for (int i = n - 1; i > 0; i--) { // i means kmp value
        cnt[kmp[i]] += cnt[i];      // notice the +=
    }

    int j = n;
    vector<pair<int,int>> ans;
    while (j > 0) {
        ans.emplace_back(j, cnt[j] + 1);
        j = kmp[j];
    }

    reverse(ans.begin(), ans.end());
    cout << ans.size() << '\n';
    for (auto &[li, ci]: ans) {
        cout << li << " " << ci << '\n';
    }
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    solve();
    return 0;
}
