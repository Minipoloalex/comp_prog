#include <bits/stdc++.h>
using namespace std;

void solve()
{
    string s;
    cin >> s;
    int n = int(s.size());

    const string T = "ODOO";
    int ans = int(1e9);

    for (int i = 0; i < n - 3; i++) {
        string r = s.substr(i, 4);
        assert(r.size() == 4);
        int c = i;
        for (int j = 0; j < 4; j++) {
            if (T[j] != r[j])
                c++;
        }
        c += n - 4 - i;
        ans = min(c, ans);
    }

    cout << ans << '\n';
}

int main()
{
    cin.tie(0)->ios::sync_with_stdio(0);
    int t = 1;
    cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}
