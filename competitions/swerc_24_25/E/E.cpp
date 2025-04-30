#include <bits/stdc++.h>
using namespace std;


const int MAX_COORD = int(1e9);

struct P {
    int x, y;
    P(): x(0), y(0) {}
    P(int _x, int _y): x(_x), y(_y) {}

    friend istream &operator>>(istream &iss, P &p) {
        return iss >> p.x >> p.y;
    }
    bool operator<(const P &p) const {
        return x < p.x || (x == p.x && y < p.y);
    }
    bool operator==(const P &p) const {
        return x == p.x && y == p.y;
    }
};

void solve() {
    int n;
    cin >> n;
    vector<P> pts(n);
    int mnx = INT_MAX;
    int mny = INT_MAX, mxy = INT_MIN;
    map<int,set<int>> mp;
    for (auto &p: pts) {
        cin >> p;
        mnx = min(mnx, p.x);
        mny = min(mny, p.y);
        mxy = max(mxy, p.y);
        mp[p.x].insert(p.y); // sorted by ascending y
    }
    if (mny == 1 && mny == mxy) {
        // handle boring edge case :(
        // note how it is not possible to have 3 points with same X and same Y
        // all points have y = 1
        mp[mnx].insert(2);
    }

    vector<P> ans;
    // group points by x, then go up (ascending y)
    // can just check equality with last element from ans to avoid duplicate points
    ans.emplace_back(mnx, 1);
    vector<P> bottom;
    for (auto &[x, ys]: mp) {
        vector<P> to_insert;
        for (int y: ys) {
            P p{x, y};
            if (x != mnx && y == 1) {
                bottom.emplace_back(x, y);
                continue;
            }
            if (ans.back() == p) continue;
            to_insert.emplace_back(x, y);   // in ascending order by y
        }
        if (x == MAX_COORD) {
            // handle differently
            // careful with all having the same X
            reverse(to_insert.begin(), to_insert.end());
        }
        if (!to_insert.empty()) {
            if (x == MAX_COORD) {
                P aux{x, 2};
                if (ans.back() == aux) {
                    ans.pop_back();
                }
                else {
                    P aux2{x - 1, 2};
                    if (!(ans.back() == aux2)) {
                        ans.push_back(aux2);
                    }
                }
                for (P p: to_insert) {
                    ans.push_back(p);
                }
                if (!(ans.back() == aux)) {
                    ans.push_back(aux);
                }
            }
            else {
                if (x != mnx) {
                    P p{x, 2};
                    if (!(p == ans.back())) {
                        ans.push_back(p);
                    }
                }
                bool inserted = false;
                for (P p: to_insert) {
                    if (p == ans.back()) continue;
                    inserted = true;
                    ans.push_back(p);
                }
                if (inserted) {
                    ans.emplace_back(x + 1, 2);
                }
            }
        }
    }
    reverse(bottom.begin(), bottom.end());
    for (P &p: bottom) {
        ans.push_back(p);
    }
    cout << ans.size() << '\n';
    for (P &p: ans) {
        cout << p.x << " " << p.y << '\n';
    }

    // debugging on submit
    // set<P> aux(ans.begin(), ans.end());
    // if (aux.size() != ans.size()) {
    //     while(1);
    // }
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
