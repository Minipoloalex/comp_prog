#include <bits/stdc++.h>
#define MAX 100000
using namespace std;
vector<int> v[MAX+10];
void dfs(int x,vector<bool> &vis)
{
    vis[x] = true;
    for(int y:v[x])
        if(!vis[y])
            dfs(y,vis);
}
void solve() {
    int n,m;
    cin>>n>>m;
    while(m--)
    {
        int x,y;
        cin>>x>>y;
        v[x].push_back(y);
    }
    vector<bool> vis_a(n+1,false);

    int a, b;
    cin>>a>>b;
    dfs(a,vis_a);

    vector<bool> vis_b(n+1,false);
    dfs(b,vis_b);
    for(int i=1;i<=n;++i)
    {
        if(vis_a[i]&&vis_b[i])
        {
            cout<<"yes"<<endl;
            cout<<i<<endl;
            return;
        }
    }
    cout<<"no"<<endl;
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
