#include <bits/stdc++.h>
using namespace std;

long long go(int i, vector<long long>&dp, vector<vector<int>> &v, vector<int> &ts, int &t, vector<long long> &ps)
{
    if(i==(int) v.size())
        return 0;
    if(dp[i]!=LLONG_MIN)
        return dp[i];
    
    dp[i] = v[i][2]+go(i+1, dp, v, ts, t, ps);
    int j = int(lower_bound(ts.begin(), ts.end(), v[i][0]+t)-ts.begin());
    if (j == i) j++;
    dp[i] = max(dp[i], v[i][1]+ps[j-1]-ps[i]+go(j, dp, v, ts, t, ps));
    
    return dp[i];
}

void solve() {
    int n,t;
    cin>>n>>t;
    if (n == 0) {
        cout << "0\n";
        return;
    }
    vector<vector<int>> v(n+1, vector<int>(3));
    vector<int> ts(n + 1, -1);
    for(int i=1;i<=n;i++)
    {
        for(int j=0;j<3;++j)
            cin>>v[i][j];
        ts[i] = v[i][0];
    }
    vector<long long> dp(n+1, LLONG_MIN), ps(n+1);
    ps[0] = 0;
    for(int i=1;i<=n;++i)
        ps[i] = v[i][2]+ps[i-1];
    cout<<go(1, dp, v, ts, t, ps)<<endl;
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    solve();
    return 0;
}
