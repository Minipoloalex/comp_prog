#include <bits/stdc++.h>
using namespace std;

const double EPS = 1e-9;

struct point
{
    double x, y;                                  // only used if more precision is needed
    point() { x = y = 0.0; }                      // default constructor
    point(double _x, double _y) : x(_x), y(_y) {} // user-defined
    bool operator==(point other) const
    {
        return (fabs(x - other.x) < EPS && (fabs(y - other.y) < EPS));
    }
    bool operator<(const point &p) const
    {
        return x < p.x || (abs(x - p.x) < EPS && y < p.y);
    }
    friend istream &operator>>(istream &iss, point &p) {
        return iss >> p.x >> p.y;
    }
};

// returns the area of polygon P
double area(const vector<point> &P)
{
    double ans = 0.0;
    for (int i = 0; i < (int)P.size() - 1; ++i) // Shoelace formula
        ans += (P[i].x * P[i + 1].y - P[i + 1].x * P[i].y);
    return ans / 2.0; // only do / 2.0 here
}

void solve(int n)
{
    vector<point> poly(n);
    for (auto &p : poly) cin >> p;
    poly.push_back(poly.front());

    double a = area(poly);
    if (a > 0) {
        cout << "CCW ";
    }
    else cout << "CW ";
    cout << fixed << setprecision(1) << fabs(a) << '\n';
}

int main()
{
    cin.tie(0)->ios::sync_with_stdio(0);
    int n;
    while (cin >> n, n)
    {
        solve(n);
    }
    return 0;
}
