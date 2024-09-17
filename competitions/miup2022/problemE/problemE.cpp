#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;
typedef pair<int, int> ii;

#define f first
#define s second

int n, m;
vi x, y;

int distance(int xinit, int yinit, int xpos, int ypos) {
    return abs(xinit - xpos) + abs(yinit - ypos);
}

int best_dist;
ii best_idxs;

ii calc_dist(int ncurr, int mcurr) {
    ii curr_idxs = {ncurr, mcurr};

    int dtl = distance(x.front(), y.front(), x.at(ncurr), y.at(mcurr));
    int dbr = distance(x.back(), y.back(), x.at(ncurr), y.at(mcurr));
    int diff = abs(dtl - dbr);

    if (diff < best_dist ||
        (diff == best_dist && curr_idxs.f < best_idxs.f) ||
        (diff == best_dist && curr_idxs.f == best_idxs.f && curr_idxs.s < best_idxs.s)) {
        best_dist = diff;
        best_idxs = curr_idxs;
    }
    return {dtl, dbr};
}

void brute_force(int nlo, int nhi, int mlo, int mhi) {
    calc_dist(nlo, mlo);
    calc_dist(nlo, mhi);
    calc_dist(nhi, mlo);
    calc_dist(nhi, mhi);
}

void solve_limits(int nlo, int nhi, int mlo, int mhi) {
    if (nlo > nhi || mlo > mhi) return;
    if (nhi - nlo <= 1 && mhi - mlo <= 1) { // small "square"
        brute_force(nlo, nhi, mlo, mhi);
        // cout << "BRUTE FORCE: " << nlo << " " << nhi << " " << mlo << " " << mhi << endl;
        return;
    }

    int med_n = (nlo + nhi) / 2;
    int med_m = (mlo + mhi) / 2;
    // cout << nlo << " " << med_n << " " << nhi << " " << mlo << " " << med_m << " " << mhi << " ";

    auto [dtl, dbr] = calc_dist(med_n, med_m);
    // cout << dtl << " " << dbr << endl;

    if (dbr > dtl) {
        // discard top left quadrant
        solve_limits(nlo, nhi, med_m + 1, mhi); // bottom
        solve_limits(med_n + 1, nhi, mlo, med_m); // top right
    }
    else if (dtl > dbr) {
        // discard bottom right quadrant
        solve_limits(nlo, nhi, mlo, med_m - 1); // top
        solve_limits(nlo, med_n - 1, med_m, mhi); // bottom left
    }
    else {
        // dtl == dbr
        // only look for lexicographically smaller solutions
        solve_limits(nlo, med_n - 1, med_m + 1, mhi); // bottom left
        solve_limits(med_n + 1, nhi, mlo, med_m - 1); // top right
    }
}

ii solve() {
    best_dist = INT_MAX;
    best_idxs = {INT_MAX, INT_MAX};
    solve_limits(0, n - 1, 0, m - 1);
    return best_idxs;
}


int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    int T;
    cin >> T;
    while (T--) {
        cin >> n >> m;
        x.resize(n);
        y.resize(m);

        for (int i = 0; i < n; i++) {
            cin >> x[i];
        }
        for (int j = 0; j < m; j++) {
            cin >> y[j];
        }

        ii ans = solve();
        if (ans.f == INT_MAX || ans.s == INT_MAX) {
            assert(0 == 1);
        }
        // cout << ans.f << " " << ans.s << '\n';
        cout << x.at(ans.f) << " " << y.at(ans.s) << '\n';
    }
    return 0;
}
