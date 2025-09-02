#include <bits/stdc++.h>
#define MAX 2e7
using namespace std;

long long ps[int(MAX)+10];

void solve() {
    int n,m;
    cin>>n>>m;
    for(int i=0;i<n;++i)
    {
        int p;
        cin>>p;
        ps[i*100] = p;
    }

    for(int i=1;i<=MAX;++i)
        ps[i] += ps[i-1];
        
    vector<int> x(m);
    for(int &xx:x)cin>>xx;
    sort(x.begin(),x.end());
    long long ans = 0;
    for(int i=0;i<=MAX;++i)
    {
        auto it = upper_bound(x.begin(),x.end(),i);
        int prv = -1e9, nxt = 1e9;
        if(it!=x.begin())
        {
            --it;
            prv = *it;
            ++it;
            if(prv==i)
                continue;
        }


        if(it!=x.end())
            nxt = *it;
        
        int l = (prv+i+1)/2, r = (nxt+i)/2;
        int lrem = (prv+i)%2, rrem = (nxt+i)%2;

        for(int j=-1;j<=+1;++j)
        {
            int ll = l, rr = r;

            if(j==0)
            {
                if(rrem==0)
                    rr--;
                if(lrem==0)
                    ll++;
            }
            else if(j==-1)
            {
                if(rrem==0)
                    rr--;
            }
            else
            {
                if(lrem==0)
                    ll++;
            }

            ll = max(0,ll);
            rr = min(rr,int(MAX));

            ans = max(ans, ps[rr]-(ll>0?ps[ll-1]:0));
        }
    }

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
