#include <bits/stdc++.h>
using namespace std;

int ps(int x1,int y1,int x2,int y2,vector<vector<int>> &a)
{
    if(x1<=x2&&y1<=y2)
        return a[x2][y2]-a[x1-1][y2]-a[x2][y1-1]+a[x1-1][y1-1];
    return 0;
}
void solve() {
    int n,m;
    cin>>n>>m;
    vector<vector<int>> a(n+1,vector<int>(m+1,0));
    int x,y;
    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=m;++j)
        {
            cin>>a[i][j];
            if(a[i][j]<0)
                x = i, y = j;
            a[i][j] += a[i-1][j]+a[i][j-1];
            a[i][j] -= a[i-1][j-1];
        }
    }
    int ans = a[n][m];
    ans = max(ans, ps(x+1,1,n,m,a));
    ans = max(ans, ps(1,1,x-1,m,a));
    ans = max(ans, ps(1,1,n,y-1,a));
    ans = max(ans, ps(1,y+1,n,m,a));
    cout<<ans<<endl;
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
