#include <bits/stdc++.h>
using namespace std;

int n, l, w;

typedef pair<double, double> dd;
vector<dd> sprinklers;

bool cmp(dd &s1, dd &s2) {
    // should sort not by biggest size, but by increasing left and after by decreasing right
    // this way we sort them by meaningful size at each step
    return s1.first < s2.first || (s1.first == s2.first && s1.second > s2.second);
}

int main() {
    while (cin >> n >> l >> w) {
        // r <= 10e3
        // n <= 10e4
        sprinklers.clear();
        for (int i = 0; i < n; i++) {
            int x, r;
            cin >> x >> r;
            if (2 * r < w) continue;

            // need right and left limits, i.e. x_l and x_r
            double dx = sqrt((double)r * r - w * w / 4.0);
            // a sprinkler only covers the rectangle delimited with length W and not the complete radius of its circle

            sprinklers.emplace_back(x - dx, x + dx);
        }
        // greedy choice of interval
        // choose the interval that's most to the right that still covers to the left at each step
        
        // sorting the sprinklers
        sort(sprinklers.begin(), sprinklers.end(), cmp);

        // for (dd s: sprinklers) {
        //     cout << s.first << ", " << s.second << endl;
        // }
        double covered = 0;
        int res = 0;
        for (uint i = 0; i < sprinklers.size() && covered < l; i++) {
            if (sprinklers[i].first > covered) {
                // cout << sprinklers[i].first << ", " << sprinklers[i].second << ", the first exceeds covered: " << covered << endl;
                break;
            }
            if (sprinklers[i].second < covered) continue;
            double x_r_max = sprinklers[i].second;
            uint selected = i;

            for (uint j = i + 1; j < sprinklers.size(); j++) {
                dd s = sprinklers[j];
                // if can still cover, pick the max of the x_r
                if (s.first > covered) break; // does not fully cover
                if (s.second > x_r_max) {
                    x_r_max = s.second;
                    selected = j;
                } 
            }
            covered = x_r_max;
            res++;
            i = selected;
            // cout << "Chose sprinkler: " << selected << ", next i: " << i + 1 << ", current res: " << res << ", covered: " << covered << endl;
        }
        if (covered < l) {
            cout << -1 << endl;
        }
        else cout << res << endl;
    }

    return 0;
}
