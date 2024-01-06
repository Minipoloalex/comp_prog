#include <bits/stdc++.h>
using namespace std;

#define EPS 1e-9

double DEG_to_RAD(double d) { return d*M_PI/180.0; }

double RAD_to_DEG(double r) { return r*180.0/M_PI; }

struct point {
  double x, y;                                   // if need more precision
  point() { x = y = 0.0; }                       // default constructor
  point(double _x, double _y) : x(_x), y(_y) {}  // constructor
  bool operator < (point other) const {          // override < operator
    if (fabs(x-other.x) > EPS)                   // useful for sorting
      return x < other.x;                        // by x-coordinate
    return y < other.y;                          // if tie, by y-coordinate
  }
  // use EPS (1e-9) when testing equality of two floating points
  bool operator == (point other) const {
   return (fabs(x-other.x) < EPS && (fabs(y-other.y) < EPS));
  }
};

double dist(double x1, double x2, double y1, double y2) {                // Euclidean distance
  // hypot(dx, dy) returns sqrt(dx*dx + dy*dy)
  return hypot(x1 - x2, y1 - y2);            // return double
}


int main() {
    int n;
    while (cin >> n) {
        cin.ignore();
        if (n == 0) break;
        
        string line;
        vector<point> locations;
        double total_x = 0;
        double total_y = 0;
        for (int i = 0; i < n; i++) {
            getline(cin, line);
            istringstream iss(line);
            double x, y, angle = 0;
            iss >> x >> y;
            string instruction;
            
            while (iss >> instruction) {
                double val;
                iss >> val;
                if (instruction == "start") {
                    angle = val;
                }
                else if (instruction == "walk") {
                    x += val * cos(DEG_to_RAD(angle));
                    y += val * sin(DEG_to_RAD(angle));
                }
                else if (instruction == "turn") {
                    angle += val;
                }
            }
            total_x += x;
            total_y += y;
            // cout << i << ": " << x << ", " << y << endl;
            locations.emplace_back(x, y);
        }
        double avg_x = total_x / n;
        double avg_y = total_y / n;
        
        double max_dist = 0;
        for (const point &lc: locations) {
            double d = dist(avg_x, lc.x, avg_y, lc.y);
            if (d > max_dist) {
                max_dist = d;
            }
        }
        cout << avg_x << " " << avg_y << " " << max_dist << endl;
    }
    return 0;
}
