#include <bits/stdc++.h>
using namespace std;

#define LSOne(S) ((S) & -(S))

typedef vector<int> vi;

struct point_i {
  int x, y;                                      // use this if possible
  point_i() { x = y = 0; }                       // default constructor
  point_i(int _x, int _y) : x(_x), y(_y) {}      // constructor
};

struct quad {
    int x_l, x_r, y_b, y_t;
    quad(point_i _bot_left, point_i _top_right) {
        x_l = _bot_left.x; x_r = _top_right.x;
        y_b = _bot_left.y; y_t = _top_right.y;
    }
};

int main() {
    int w, h;   // [1, 100]
    while (cin >> w >> h) {
        int n; cin >> n;    // [0, 20]
        vector<string> emp(n);
        vector<quad> v;
        for (int i = 0; i < n; i++) {
            int x1, x2, y1, y2; // 0 <= x1 <= x2 <= w; 0 <= y1 <= y2 <= h
            cin >> emp[i] >> x1 >> y1 >> x2 >> y2;
            v.emplace_back(point_i(x1, y1), point_i(x2, y2));
        }
        vector<vi> space(h, vi(w, 0));
        for (int i = 0; i < n; i++) {
            quad &q = v[i];
            for (int row = q.y_b; row < q.y_t; row++) {
                for (int col = q.x_l; col < q.x_r; col++) {
                    space[row][col] |= (1 << i);
                }
            }
        }
        int total_space = w * h;
        int unnalocated = 0;
        int contested = 0;
        vi emp_space(n, 0);
        for (int r = 0; r < (int) space.size(); r++) {
            for (int c = 0; c < (int) space[0].size(); c++) {
                if (space[r][c] == 0) unnalocated++;
                else {
                    vi people;
                    while (space[r][c] > 0) {
                        int two_pow_person = LSOne(space[r][c]);
                        int person = __builtin_ctz(two_pow_person);
                        people.push_back(person);
                        space[r][c] -= two_pow_person;
                        /*
                        int two_pow_j = LSOne(mask);    // least significant bit 1
                        int j = __builtin_ctz(two_pow_j);    // 2^j = two_pow_j, get j
                        */
                    }
                    if (people.size() == 1) {
                        emp_space[people.front()]++;
                    }
                    else contested++;
                }
            }
        }
        cout << "Total " << total_space << endl;
        cout << "Unallocated " << unnalocated << endl;
        cout << "Contested " << contested << endl;
        for (int i = 0; i < n; i++) {
            cout << emp[i] << " " << emp_space[i] << endl;
        }
        cout << endl;
    }
    return 0;
}
