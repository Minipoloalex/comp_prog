#include <bits/stdc++.h>
using namespace std;

int toInt(string s)
{
    int ans = 0;
    for(auto c:s)
        ans *= 10, ans += c-'0';
    return ans;
}
int mex(set<int> st)
{
    for(int i=0;;++i)
    {
        if(st.find(i)==st.end())
            return i;
    }
    return 0;
}
void solve() {
    int n;
    cin>>n;
    set<int> st;
    for(int i=0;i<n;++i)
    {
        string s;
        cin>>s;
        if(s.front()=='-')
            continue;
        reverse(s.begin(),s.end());
        while(s.size()>1&&s.back()=='0')
            s.pop_back();
        if(s.size()>7)
            continue;
        reverse(s.begin(),s.end());
        st.insert(toInt(s));
    }
    cout<<mex(st)<<endl;
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
