#include <bits/stdc++.h>
using namespace std;

bool valid(int x,int y,int n,int m)
{
    return 0<=x&&x<n&&0<=y&&y<m;
}

bool dfs(pair<int,int> src, pair<int,int> &dest, vector<vector<bool>> &vis, vector<string> &v)
{
    if(dest==src)
        return true;

    int n = (int)vis.size(), m = (int)vis.front().size();
    vis[src.first][src.second] = true;
    int dx[] = {0, 0, +1, -1}, dy[] = {+1, -1, 0, 0};
    for(int i=0;i<4;++i)
    {
        int x = src.first+dx[i];
        int y = src.second+dy[i];
        if(valid(x,y,n,m)&&!vis[x][y]&&(v[x][y]=='.'||v[x][y]=='H'))
        {
            if(dfs({x,y},dest,vis, v))
                return true;
        }
    }

    return false;
}

void solve() {
    int n, m, d;
    cin>>n>>m>>d;
    map<char,pair<int,int>> dir;
    dir['>'] = {0,+1};
    dir['<'] = {0, -1};
    dir['^'] = {-1, 0};
    dir['v'] = {+1, 0};

    vector<string>v(n);
    for(auto &s:v)cin>>s;
    pair<int,int> src, dest;
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;++j)
        {
            if(v[i][j]=='F')
                src = {i, j};
            if(v[i][j]=='H')
                dest = {i,j};
            if(dir.find(v[i][j])==dir.end())
                continue;
            auto [x,y] = dir[v[i][j]];
            for(int k=1;k<=d;++k)
            {
                int xx = i+k*x, yy = j+k*y;
                if(!valid(xx,yy,n,m))
                    break;
                if(v[xx][yy]=='F'||v[xx][yy]=='H')
                {
                    cout<<"NO"<<endl;
                    return;
                }
                if(v[xx][yy]=='#'||dir.find(v[xx][yy])!=dir.end())
                    break;
                v[xx][yy] = '!'; 
            }
        }
    }

    vector<vector<bool>> vis(n, vector<bool>(m, false));

    if(dfs(src, dest, vis, v))
        cout<<"YES"<<endl;
    else cout<<"NO"<<endl;
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    solve();
    return 0;
}
