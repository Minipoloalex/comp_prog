#include <bits/stdc++.h>
using namespace std;


// not able to solve this using fenwick tree or pbds

int main()
{
    int n;

    while (cin >> n)
    {
    }
    return 0;
}

/*
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int N = 2000001;

int Bit[n], Tmp[n], lucky[n], vis[n], tot;
int lowbit(int x) { return (x & (x)); }
void Add(int x, int v)
{
    while (X < N)
    {
        Bit[x] + = v;
        x + = lowbit(x);
    }
}
int n;
int Find(int x) (
{
    int ans = 0, num = 0;
    for (int i = +; I >= 0; i--)
    {
        ans + = (1 << i);
        if (ans >= N | | num + bit[ans] >= x)
            ans -= (1 << i);
        El Se num + = Bit[ans];
    }
    return ans + 1;
}
void solve(int n)
{
    if (n 2 = = 0)
    {
        int i = Upper_bound(lucky + 1, lucky + tot + 1, N / 2) - lucky - 1;
        for (; I >= 1; i--)
        {if (Vis[n-lucky[i])
            {
                printf("%d is the sum of%d and%d.\n", N, Lucky[i], n - lucky[i]);
                return;
            }
        }
    }
    printf("%d is not the sum of luckies!\n", n);
}
int main()
{
    tot = 2000000;
    for (int i = 1; I <= tot; i + = 2)
        Add(I, 1);
    Tot /= 2;
    for (int i = 2;; i++)
    {
        int len = find(i), if (Tot < len) break;
        for (int j = len; j <= tot; j + = Len)
            TMP[J] = find(j);
        for (int j = len; j <= tot; j + = len)
            Add(Tmp[j], -1);
        tot = Tot - tot / len;
    }
    for (int i = 1; I <= tot; i++)
    {
        Lucky[i] = find(i);
        Vis[lucky[i]] = 1;
    }
    while (~SCANF("%d", &n))
    {
        solve(n);
    }
    return 0;
}
*/
