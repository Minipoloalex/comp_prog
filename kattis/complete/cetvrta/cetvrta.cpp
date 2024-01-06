#include <bits/stdc++.h>
using namespace std;

struct point_i {
  int x, y;                                      // use this if possible
  point_i() { x = y = 0; }                       // default constructor
  point_i(int _x, int _y) : x(_x), y(_y) {}      // constructor
};

int main() {
    vector<int> x(3);
    vector<int> y(3);
    for (int i = 0; i < 3; i++) cin >> x[i] >> y[i];
    sort(x.begin(), x.end());
    sort(y.begin(), y.end());
    point_i res = point_i(x[0], y[0]);
    if (x[0] == x[1]) res.x = x[2];
    if (y[0] == y[1]) res.y = y[2];
    cout << res.x << " " << res.y << endl;
    return 0;
}
