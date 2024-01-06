#include <bits/stdc++.h>
using namespace std;

/*
Observations - robot will never move left
*/
typedef long long ll;

char m[2][1000000];

int main() {
    ll n;
    cin >> n;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < n; j++) {
            cin >> m[i][j];
            cout << m[i][j];
        }
        cout << endl;
    }
    return 0;
}
