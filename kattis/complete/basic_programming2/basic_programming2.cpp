#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;
bool sum_2(vi &a, int obj = 7777) {
    sort(a.begin(), a.end());
    
    int l = 0, r = a.size() - 1;
    
    while (l != r && a[l] + a[r] != obj) {  // if l == r, then x = y so val == obj is false;
        if (a[l] + a[r] > obj) r--;
        else if (a[l] + a[r] < obj) l++;
        else while(1);
    }
    return a[l] + a[r] == obj;  // no need to assure a[r] != a[l] since 7777 is not even
}

bool all_unique(vi &a) {
    sort(a.begin(), a.end());
    for (int i = 1; i < (int)a.size(); i++) {
        if (a[i - 1] == a[i]) return false;
    }
    return true;
}

void print_very_common_integer(vi &a) {
    int count_to_print = (int)a.size() / 2 + 1;
    sort(a.begin(), a.end());

    bool found = false;
    int cur = -1, cur_count = 0;
    for (int i = 0; i < (int)a.size(); i++) {
        if (cur == a[i]) cur_count++;
        else {
            cur = a[i];
            cur_count = 1;
        }
        if (cur_count >= count_to_print) {
            cout << a[i] << endl;
            found = true;
            break;
        }
    }
    if (!found) cout << -1 << endl;
}
void print_median(vi &a) {
    sort(a.begin(), a.end());
    if (a.size() % 2 == 0) cout << a[a.size() / 2 - 1] << " " << a[a.size() / 2] << endl; 
    else cout << a[a.size() / 2] << endl;
}

void print_integers_between(vi &a, int min = 100, int max = 999) {
    vi res;
    for (int i = 0; i < (int) a.size(); i++) {
        if (a[i] >= min && a[i] <= max) res.push_back(a[i]);
    }
    sort(res.begin(), res.end());
    for (int i = 0; i < (int) res.size(); i++) {
        if (i == (int) res.size() - 1) cout << res[i] << endl;
        else cout << res[i] << " ";
    }
}

int main() {
    int n, t;
    cin >> n >> t;
    vi a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    vi res;
    switch (t) {
        case 1:
            if (sum_2(a)) cout << "Yes" << endl;
            else cout << "No" << endl;
            break;
        case 2:
            if (all_unique(a)) cout << "Unique" << endl;
            else cout << "Contains duplicate" << endl;
            break;
        case 3:
            print_very_common_integer(a);
            break;
        case 4:
            print_median(a);
            break;
        case 5:
            print_integers_between(a);
            break;
    }
    return 0;
}
