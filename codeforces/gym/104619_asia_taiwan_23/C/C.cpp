#include <bits/stdc++.h>
using namespace std;
const int INF = int(1e9);
const int MAX = int(1e5);
string x;
unsigned long long b;

int dp[MAX+10][25];

int go(int i,int prev_size)
{
    if(i==x.size())
        return 0;
        
    auto &mem = dp[i][prev_size];
    if(mem!=-1)
        return mem;

    int l = i-prev_size, r = i-1;
    unsigned long long prev = 0;

    //cout<<"HERE "<<l<<" "<<r<<'\n';
    while(l<=r)
    {
        prev *= 10;
        prev += int(x[l]-'0');
        l++;
    }
        

    mem = INF;
    __int128_t cur = 0;

    for(int j=i;j<x.size();++j)
    {
        cur *= 10;
        cur += int(x[j]-'0');
        if(cur>b)
            break;
        //cout<<prev<<"_"<<cur<<'\n';
        if(cur>=prev&&(j+1==x.size()||x[j+1]!='0'))
            mem = min(mem,1+go(j+1,j-i+1));
    }

    return mem;
}

void solve() {
    cin>>x>>b;
    x = "0"+x;
    for(int i=0;i<x.size();++i)
        for(int j=0;j<25;++j)
            dp[i][j] = -1;
    auto ans = go(1,1);
    if(ans>=INF)
    {
        cout<<"NO WAY"<<'\n';
        return;
    }
    cout<<ans-1<<endl;
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
