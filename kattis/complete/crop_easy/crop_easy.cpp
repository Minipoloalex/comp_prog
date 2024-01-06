#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long ull;

struct point_i {
  ull x, y;                                      // use this if possible
  point_i() { x = y = 0; }                       // default constructor
  point_i(ull _x, ull _y) : x(_x), y(_y) {}      // constructor
};
ostream &operator<<(ostream &os, const point_i &p) {
  return os << "(" << p.x << ", " << p.y << ")";
}
int main() {
    int T;
    cin >> T;
    
    for(int t = 1; t <= T; t++) {
        ull n, a, b, c, d, x0, y0, m;
        cin >> n >> a >> b >> c >> d >> x0 >> y0 >> m;
        // parameters such that the input set of trees will not have duplicates
        vector<point_i> vpi(n);

        ull x = x0;
        ull y = y0;
        vpi.at(0) = point_i(x, y); // n [3, 100]
        for (ull i = 1; i < n; i++) {
            x = (a * x + b) % m;
            y = (c * y + d) % m;
            vpi.at(i) = point_i(x, y);
        }
        int count_trees = 0;
        for (ull t1 = 0; t1 < n; t1++) {
            for (ull t2 = t1 + 1; t2 < n; t2++) {
                for (ull t3 = t2 + 1; t3 < n; t3++) {
                    ull x1 = vpi[t1].x;
                    ull x2 = vpi[t2].x;
                    ull x3 = vpi[t3].x;
                    ull y1 = vpi[t1].y;
                    ull y2 = vpi[t2].y;
                    ull y3 = vpi[t3].y;
                    if ((x1 + x2 + x3) % 3 == 0 && (y1 + y2 + y3) % 3 == 0) {
                        // cout << vpi[t1] << " " << vpi[t2] << " " << vpi[t3] << endl;
                        count_trees++;
                    }
                }
            }
        }
        cout << "Case #" << t << ": " << count_trees << endl;
    }
    return 0;
}
