#include <bits/stdc++.h>
using namespace std;

const int N = 21;
const int n = 6;

int a[1<<N];
pair<int,int> p[N];

int id[n][n];
int cnt[n];
vector<int> g[n];
bool vis[n];

void solve() {
    int m;
    cin>>m;
    int mask = 0;
    for(int i=0;i<m;++i)
    {
        int x,y;
        cin>>x>>y;
        x--;
        y--;
        mask |= 1<<(id[x][y]);
    }

    cout<<a[mask]<<'\n';
}



bool bfs(int src,int target)
{
    queue<int> q;
    q.push(src);
    vis[src] = true;
    int c = 0;

    while(!q.empty())
    {
        auto x = q.front();
        q.pop();
        c++;
        for(auto x1:g[x])
        {
            if(!vis[x1])
                q.push(x1), vis[x1] = true;
        }
    }

    return target==c;

}

bool check(int mask)
{
    if(mask==0)
        return false;

    for (int i = 0; i < n; i++) g[i].clear(), cnt[i] = 0, vis[i] = false;

    bitset<n> b;
    int src;
    for(int i=0;i<N;++i)
    {
        if(mask&(1<<i))
        {
            src = p[i].first;
            g[src].push_back(p[i].second);
            g[p[i].second].push_back(src);
            b[src] = true;
            b[p[i].second] = true;

            cnt[p[i].first]++;
            cnt[p[i].second]++;
        }
    }
    int odds = 0;
    for (int i = 0; i < n; i++) {
        if (cnt[i] & 1) odds++;
    }
    if (odds != 0 && odds != 2) return false;

    bool ans = bfs(src, b.count());
    return ans;
}

void precomp()
{
    int it = 0;
    for(int i=0;i<n;++i)
    {
        for(int j=i;j<n;++j)
        {
            id[i][j] = it;
            p[it++] = {i,j};
        }
    }

    // assert(p.size()==N);
    for(int i=0;i<(1<<N);++i)
        a[i] = check(i);


    for (int i = 0; i < N; i++) {
        for (int x = 0; x < (1 << N); x++) {
            if (x & (1 << i)) { a[x] += a[x ^ (1 << i)]; }
        }
    }

}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    precomp();
    int t = 1;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}