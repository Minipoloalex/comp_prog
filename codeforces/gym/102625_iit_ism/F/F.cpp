#include <bits/stdc++.h>
using namespace std;
vector<long long> ans;
int d[3];
void go(long long i,int sm,int cnt,int a[10])
{
    if(i>(long long)1e9)
        return;
    if(cnt>0&&sm%cnt==0)
    {
        int k = sm/cnt;
        bool ok = false;
        for(int j=0;j<3;++j)
            ok |= k==d[j]&&a[d[j]]>0;
        if(ok)
            ans.push_back(i);
    }
    for(int j=0;j<3;++j)
    {
        a[d[j]]++;
        go(i*10+d[j],sm+d[j],cnt+1,a);
        a[d[j]]--;
    }
        
}
void solve() {
    set<int> v;
    for(int i=0;i<3;++i)
    {
        cin>>d[i];
        if(d[i]>0)
            v.insert(d[i]);
    }
    for(int x:v) 
    {
        int a[10];
        for(int i=0;i<10;++i)a[i]=0;
        go(x,x,1,a);
    }   
    sort(ans.begin(),ans.end());
    auto it = unique(ans.begin(),ans.end());
    ans.resize(it-ans.begin());

    int q;
    cin>>q;
    pair<long long,int> res = {-1,-1};
    for(int i=1;i<=q;++i)
    {
        int l,r;
        cin>>l>>r;
        long long sz = upper_bound(ans.begin(),ans.end(),r)-lower_bound(ans.begin(),ans.end(),l);
        res = max(res,{sz,-i});
    }
    cout<<-res.second<<endl;
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
