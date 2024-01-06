#include <bits/stdc++.h>
using namespace std;

struct point_i {
  int x, y;                                      // use this if possible
  point_i() { x = y = 0; }                       // default constructor
  point_i(int _x, int _y) : x(_x), y(_y) {}      // constructor
};

double dist(point_i p1, point_i p2) {                // Euclidean distance
  // hypot(dx, dy) returns sqrt(dx*dx + dy*dy)
  return hypot(p1.x-p2.x, p1.y-p2.y);            // return double
}

int arr[3][3] ;

point_i find_val(int val) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (arr[i][j] == val) return point_i(i, j);
        }
    }
    return point_i(0, 0);
}

int main() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cin >> arr[i][j];
        }
    }
    
    double total_dist = 0;
    point_i curr = find_val(1);
    point_i next;
    for (int p = 2; p <= 9; p++) {
        next = find_val(p);
        total_dist += dist(curr, next);
        curr = next;
    }
    cout << fixed << setprecision(10) << total_dist << endl;    
    return 0;
}
