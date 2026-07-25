#include <bits/stdc++.h>
using namespace std;

char ch[3] = {'R', 'G', 'B'};

void solve() {
    array<pair<int,char>,3> a;
    for (int i = 0; i < 3; i++) {
        cin >> a[i].first;
        a[i].second = ch[i];
    }
    sort(a.begin(), a.end());

    string ans;
    int cnt3 = 0;
    while (a[0].first + a[1].first > a[2].first) {
        a[0].first--;
        a[1].first--;
        a[2].first--;
        cnt3++;
    }
    // it's ensured that there are enough a[2]'s to fill the a[0] and a[1]
    while (a[0].first > 0) {
        ans += a[2].second;
        ans += a[0].second;
        a[0].first--;
        a[2].first--;
    }
    while (a[1].first > 0) {
        ans += a[2].second;
        ans += a[1].second;
        a[1].first--;
        a[2].first--;
    }
    if (a[2].first > 0) {
        a[2].first--;
        ans += a[2].second;
    }
    array<int,3> id = {0,1,2};
    auto get_cidx = [&](char c) {
        for (int i = 0; i < 3; i++) {
            if (a[i].second == c) return i;
        }
        return -1;
    };
    if (ans.size() >= 2) {
        id[0] = get_cidx(ans[ans.size()-2]);
        id[1] = get_cidx(ans[ans.size()-1]);
        for (int j = 0; j < 3; j++) {
            if (j != id[0] && j != id[1]) {
                id[2] = j;
            }
        }
    }
    else if (ans.size() == 1) {
        swap(id[get_cidx(ans[0])], id[1]);
    }
    for (int i = 0; i < cnt3; i++) {
        for (int j = 0; j < 3; j++) {
            int idx = id[(j+i)%3];
            ans += a[idx].second;
        }
    }
    cout << ans << '\n';
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int t = 1;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
