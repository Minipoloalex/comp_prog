#include <bits/stdc++.h>
using namespace std;

pair<bool,int> calc(int x)
{
    pair<bool,int> p;
    int c = 0;
    while(x%2==0)
    {
        c++;
        x /= 2;
    }
    return {x==1,c};
}

void solve() {
    int x,y;
    cin>>x>>y;
    auto xx = calc(x), yy = calc(y);
    if(xx.first||yy.first)
    {
        if(xx.first&&!yy.first)
            cout<<"-inf\n";
        else if(!xx.first&&yy.first)
            cout<<"inf\n";
        else 
            cout<<-yy.second+xx.second<<'\n';
    }
    else if(x%2==1&&y%2==1)
        cout<<(y-x)/2<<'\n';
    else if(x%2==1&&y%2==0)
        cout<<"inf\n";
    else if(x%2==0&&y%2==1)
        cout<<"-inf\n";
    else 
    {
        if(xx.second==yy.second)
        {
            int p2 = 1<<(xx.second+1);
            cout<<(y-x)/p2<<'\n';
        }
        else if(yy.second>xx.second)
            cout<<"inf\n";
        else 
            cout<<"-inf\n";
    }
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    int t = 1;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
