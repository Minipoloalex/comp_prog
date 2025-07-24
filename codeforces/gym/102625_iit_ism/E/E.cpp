#include <bits/stdc++.h>
using namespace std;

void solve() {
    int m,n;
    cin>>m>>n;
    set<array<int,2>> st;
    vector<array<int,3>> v(m);
    for(int i=0;i<m;++i)
    {
        int l,r,x;
        cin>>l>>r>>x;
        v[i] = {x,l-x,r-1-x};
    }
    sort(v.begin(),v.end());
    for(int i=0;i<n;++i)
    {
        int t;
        cin>>t;
        st.insert({t,i});
    }
    vector<int> ans(n,-1);
    for(auto [x,l,r]:v)
    {
        while(1)
        {
            auto p = st.lower_bound({l,-1});
            if(p!=st.end())
            {
                auto [t,i] = *p;
                if(t<=r)
                {
                    ans[i] = x;
                    st.erase(p);
                }
                else break;
            }
            else break;
        }
    }
    for(int x:ans)
        cout<<x<<endl;
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
