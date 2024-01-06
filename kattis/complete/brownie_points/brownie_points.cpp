#include <bits/stdc++.h>
using namespace std;

struct point_i {
  int x, y;                                      // use this if possible
  point_i() { x = y = 0; }                       // default constructor
  point_i(int _x, int _y) : x(_x), y(_y) {}      // constructor
};

typedef vector<point_i> vpi;

vpi points;

int main() {
    int n;
    while (cin >> n) {
        points.resize(n);
        if (n == 0) break;
        int x_limit = 0;
        int y_limit = 0;
        for (int i = 0; i < n; i++) {
            int x, y;
            cin >> x >> y;
            points[i] = point_i(x, y); 
            if (i == n/2) {
                x_limit = x;
                y_limit = y;
            }
        }
        int count_a = 0;
        int count_b = 0;
        
        for (const point_i &p: points) {
            if (p.x > x_limit && p.y > y_limit) {   // 1st
                count_a++;
            }
            else if (p.x < x_limit && p.y < y_limit) {  // 3rd
                count_a++;
            }
            else if (p.x != x_limit && p.y != y_limit) count_b++;   // 2nd and 4th
        }
        cout << count_a << " " << count_b << endl;
    }
    return 0;
}
