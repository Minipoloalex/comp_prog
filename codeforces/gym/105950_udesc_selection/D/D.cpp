#include <bits/stdc++.h>
using namespace std;
int mx[] = {0,0,+1,-1};
int my[] = {+1,-1,0,0};
bool valid(int x,int y,int n,int m)
{
    return 1<=x&&x<=n&&1<=y&&y<=m;
}
bool check(int x,int y,long long mask, vector<vector<long long>> &v,int n,int m)
{
    queue<pair<int,int>> q;
    q.push({x,y});
    vector<vector<bool>> vis(n+1,vector<bool>(m+1,false));
    vis[x][y] = true;
    while(!q.empty())
    {
        auto [a,b] = q.front();
        q.pop();
        if(a==n&&b==m)
            return true;
        for(int i=0;i<4;++i)
        {
            int xx = a+mx[i], yy = b+my[i];
            if(valid(xx,yy,n,m)&&!vis[xx][yy])
            {
                long long t = mask&v[xx][yy];
                if(t!=v[xx][yy])
                    continue;
                vis[xx][yy] = true;
                q.push({xx,yy});
            }
        }
    }
    return false;
}
long long go(int x,int y,vector<vector<long long>> &v,int n,int m)
{
    long long mask = 1LL<<33;
    mask--;
    for(int i=32;i>=0;--i)
    {
        mask ^= 1LL<<i;
        if(!check(x,y,mask,v,n,m))
            mask ^= 1LL<<i;
    }
    return mask;
}
void solve() {
    int n, m; cin >> n >> m;
    int x,y;
    cin>>x>>y;
    vector<vector<long long>> v(n+1,vector<long long>(m+1));
    for(int i=1;i<=n;++i)
        for(int j=1;j<=m;++j)
            cin>>v[i][j];
    cout<<go(1,1,v,n,m)<<" "<<go(x,y,v,n,m)<<endl;

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
