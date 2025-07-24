#include <bits/stdc++.h>
using namespace std;

void solve()
{
    int64_t n, k;
    cin >> n >> k;

    vector<int64_t> a(2 * n);
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
        a[i + n] = a[i];
    }

    vector<int> ans(n, -1);

    auto start = [&](int p)
    {
        int st = p;
        int64_t cur = a[p];
        if (p == n - 1)
        {
            while (p < 2 * n && cur <= a[p])
            {
                p++;
                cur += k;
            }
            ans[st] = p;
        }
        else
        {
            if (cur + k > a[p + 1])
            {
                ans[st] = p + 1;
            }
            else
            {
                p = ans[p + 1];
                cur += k * (p - st);
                while (p < 2 * n && cur <= a[p])
                {
                    p++;
                    cur += k;
                }
                ans[st] = p;
            }
        }
    };

    for (int i = int(n) - 1; i >= 0; i--)
    {
        start(i);
    }

    for (int i = 0; i < n; i++) {
        cout << (ans[i] % n) + 1 << " \n"[i == n - 1];
    }
}

int main()
{
    cin.tie(0)->ios::sync_with_stdio(0);
    int t = 1;
    // cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}
