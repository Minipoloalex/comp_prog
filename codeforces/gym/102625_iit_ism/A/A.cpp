#include <bits/stdc++.h>
using namespace std;

#define int int64_t

void solve()
{
    int cnt = 0;
    for (int i = 0; i <= 9; i++)
    {
        for (int j = 0; j <= 9; j++)
        {
            for (int k = 0; k <= 9; k++)
            {
                if (i + j + k <= 10) cnt ++;
            }
        }
    }

    cout << cnt << endl;
}

signed main()
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
