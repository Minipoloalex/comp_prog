#include <bits/stdc++.h>
using namespace std;
#define MAX 200000
vector<int> v[MAX+10];
vector<int> g[MAX+10];
bool vis[MAX+10];
vector<pair<int,int>> ans;
void dfs1(int x)
{
    vis[x] = 1;
    for(int y:v[x])
    {
        if(vis[y])
            continue;
        g[x].push_back(y);
        g[y].push_back(x);
        dfs1(y);
    }
}

int dfs2(int x)
{
    vis[x] = 1;
    vector<int> tmp;
    for(int y:g[x])
    {
        if(vis[y])
            continue;
        auto z = dfs2(y);
        if(z>0)
            tmp.push_back(z);
    }

    while(tmp.size()>1)
    {
        int a = tmp.back();
        tmp.pop_back();
        int b = tmp.back();
        tmp.pop_back();

        ans.push_back({a,b});
    }

    if(tmp.empty())
        return x;
    
    ans.push_back({x,tmp.front()});
    return 0;
}

void solve() {
    int n,m;
    cin>>n>>m;
    while(m--)
    {
        int x,y;
        cin>>x>>y;
        v[x].push_back(y);
        v[y].push_back(x);
    }
    
    for(int i=1;i<=n;++i)
        if(!vis[i])
            dfs1(i);
    
    for(int i=1;i<=n;++i)
        vis[i] = 0;
    
    for(int i=1;i<=n;++i)
    {
        if(!vis[i])
            dfs2(i);
    }

    cout<<ans.size()<<endl;
    for(auto [x,y]:ans)
        cout<<x<<" "<<y<<endl;
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
