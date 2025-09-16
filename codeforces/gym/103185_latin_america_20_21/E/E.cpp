#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin>>n;
    vector<int> v(n);
    for(int &x:v)cin>>x;
    stack<int> prev_g,next_g;
    vector<int> l(n,-1), r(n,n);
    for(int i=0;i<n;++i)
    {
        while(!prev_g.empty()&&v[prev_g.top()]<v[i])
            prev_g.pop();
        if(!prev_g.empty())
            l[i] = prev_g.top();
        prev_g.push(i);
    }
    for(int i=n-1;i>=0;--i)
    {
        while(!next_g.empty()&&v[next_g.top()]<v[i])
            next_g.pop();
        if(!next_g.empty())
            r[i] = next_g.top();
        next_g.push(i);
    }

    vector<int> d(n+2,0);
    for(int i=0;i<n;++i)
    {
        if(l[i]==-1)
        {
            d[0]++;
            d[i]--;
        }
        else
        {
            int m1 = (l[i]+i)/2;
            m1++;
            
            d[m1]++;
            d[i]--;
        }
        

        if(r[i]==n)
        {
            d[i+1]++;
        }
        else
        {
            int m2 = (r[i]+i+1)/2;
            m2--;
            
            d[i+1]++;
            d[m2+1]--;
        }

    }

    for(int i=0;i<n;++i)
    {
        if(i>0)
            d[i] += d[i-1];
        cout<<d[i]<<" ";
    }
    cout<<'\n';
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
