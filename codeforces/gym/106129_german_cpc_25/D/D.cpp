#include <bits/stdc++.h>
using namespace std;

void solve()
{
    int n = 2500;

    auto is_prime = [](int n)
    {
        for (int i = 2; i * i <= n; i++)
        {
            if (n % i == 0)
                return false;
        }
        return true;
    };
    int cnt = 0;
    for (int i = 2; i <= n; i++)
    {
        if (is_prime(i))
            cnt++;
    }

    cout << cnt << endl;
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
