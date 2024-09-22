#include <bits/stdc++.h>
using namespace std;

int ask(string &s) {
    cout << "? " << s << '\n';
    cout.flush();
    int resp;
    cin >> resp;
    return resp;
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        string curr;
        bool found_limit = false;
        while (!found_limit && int(curr.size()) < n) {
            curr += '0';

            int resp = ask(curr);
            if (resp == 1) continue;

            curr[curr.size() - 1] = '1';
            resp = ask(curr);
            if (resp == 1) continue;
            else curr.pop_back();

            found_limit = true;
        }
        while (int(curr.size()) < n) {
            curr.insert(0, 1, '0');
            int resp = ask(curr);
            if (resp == 0) curr[0] = '1';
        }
        cout << "! " << curr << '\n';
        cout.flush();

    }
    return 0;
}
