#include <bits/stdc++.h>
using namespace std;

struct Point {
    int64_t x, y;
    Point operator-(Point &p2) const {
        return Point(x - p2.x, y - p2.y);
    }
    Point(int64_t _x, int64_t _y): x(_x), y(_y) {}
};

int64_t cross_product_z(Point p1, Point p2, Point p3) {
    // (p1 -> p2) X (p1 -> p3)
    Point v1 = p2 - p1;
    Point v2 = p3 - p1;
    int64_t ans = (v1.x * v2.y) - (v1.y * v2.x);
    return ans;
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    int t;
    cin >> t;
    while (t--) {
        int64_t x, y;
        cin >> x >> y;
        Point p1(x, y);
        cin >> x >> y;
        Point p2(x, y);
        cin >> x >> y;
        Point p3(x, y);
        int64_t ans = cross_product_z(p1, p2, p3);
        if (ans == 0) {
            cout << "TOUCH\n";
        }
        else if (ans < 0) {
            cout << "RIGHT\n";
        }
        else {
            cout << "LEFT\n";
        }
    }
    return 0;
}
