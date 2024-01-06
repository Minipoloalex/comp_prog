#include <bits/stdc++.h>
using namespace std;

#define EPS 1e-9

typedef vector<uint> vi;
typedef struct interval {
    double ai;
    double bi;
} interval;

// All real numbers have at most digits after the decimal point
// The intervals can be given in any order
// All real numbers have at most digits after the decimal point

bool cmp(interval &a, interval &b) {
    return a.ai < b.ai || (a.ai == b.ai && a.bi > b.bi);
}

int main() {
    double A, B;
    uint n;
    while (cin >> A >> B >> n) {
        B += EPS;   // problems when A = B
        vector<interval> intervals;
        for (uint i = 0; i < n; i++) {
            double ai, bi;
            cin >> ai >> bi;
            intervals.push_back({ai, bi + EPS});   // problems when A = B
        }
        vi indices(n);
        for (uint i = 0; i < n; i++) indices[i] = i;
        
        sort(indices.begin(), indices.end(), [&intervals](uint i1, uint i2) {
            interval &a = intervals[i1];
            interval &b = intervals[i2];
            return a.ai < b.ai || (a.ai == b.ai && a.bi > b.bi);
        });
        
        vi chosen;
        double covered = A;
        for (uint i = 0; i < indices.size() && covered < B; i++) {
            interval &intval = intervals[indices[i]];
            if (intval.ai > covered) break; // if equal, it's still useful
            if (intval.bi < covered) continue;  // if equal, it's still useful
            uint selected = i;
            double max_right = intval.bi;
            for (uint j = i + 1; j < indices.size(); j++) {
                interval &intval2 = intervals[indices[j]];
                if (intval2.ai > covered) break;
                if (intval2.bi > max_right) {
                    max_right = intval2.bi;
                    selected = j;
                }
            }
            i = selected;
            covered = max_right;
            chosen.push_back(indices[selected]);
        }
        sort(chosen.begin(), chosen.end());
        if (covered < B) {
            cout << "impossible" << endl;
        }
        else {
            cout << chosen.size() << endl;
            for (uint index: chosen) {
                if (index == chosen.back()) {
                    cout << index << endl;
                }
                else cout << index << " ";
            }
        }
    }
    return 0;
}
