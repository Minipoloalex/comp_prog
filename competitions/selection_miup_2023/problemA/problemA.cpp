#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0); ios::sync_with_stdio(0);
    int t1, f1, s1, p1, c1;
    int t2, f2, s2, p2, c2;
    cin >> t1 >> f1 >> s1 >> p1 >> c1;
    cin >> t2 >> f2 >> s2 >> p2 >> c2;
    cout << t1 * 6 + f1 * 3 + s1 * 2 + p1 + c1 * 2 << " " << t2 * 6 + f2 * 3 + s2 * 2 + p2 + c2 * 2 << endl;
    return 0;
}
