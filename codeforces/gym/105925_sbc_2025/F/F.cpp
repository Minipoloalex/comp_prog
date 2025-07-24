#include <bits/stdc++.h>
using namespace std;
#define MAX 16001
#define SHIFT 8000
#define MAXN 1001
long long dp[MAXN+10][MAX+10][5];
int a[MAXN+10];
int n;
long long go(int i,int sum,int k)
{
    if(k==0)
        return sum==0;
    
    if(i==n)
        return 0;
    int s = sum+SHIFT;
    //cout<<i<<" "<<s<<" "<<sum<<" "<<k<<endl;
    if(dp[i][s][k]!=-1)
        return dp[i][s][k];
    return dp[i][s][k] = go(i+1,sum-a[i],k-1)+go(i+1,sum,k);
}
void solve() {
    cin>>n;
    for(int i=0;i<n;++i)
    {
        cin>>a[i];
        for(int j=0;j<=MAX;++j)
            for(int k=0;k<=4;++k)
                dp[i][j][k] = -1;
    }
    sort(a, a + n);
    // for(int i=-(SHIFT/2);i<=SHIFT/2;++i)
    //     go(0,i,4);
    int q;
    cin>>q;
    while(q--)
    {
        int x;
        cin>>x;
        cout<<go(0,x,4)<<'\n';
    }
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
