#include <bits/stdc++.h>
using namespace std;

pair<bool,pair<long long,long long>> calc(long long x,long long y)
{
    long long a = x+y;
    if(a&1)
        return {false,{0,0}};
    a /= 2;
    long long b = a-x;
    return {true,{a,b}};
}

void solve() {
    long long x,y;
    cin>>x>>y;
    auto ans = calc(x,y);
    bool ok = ans.first;
    auto [a,b] = ans.second;

    if(ok && a+b==x && abs(a-b)==y)
        cout<<a<<" "<<b<<endl;
    else 
    {
        auto ans = calc(y,x);
        bool ok = ans.first;
        auto [a,b] = ans.second;
        

        assert(ok);
        cout<<a<<" "<<b<<endl;
    }
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    int t = 1;
    //cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
