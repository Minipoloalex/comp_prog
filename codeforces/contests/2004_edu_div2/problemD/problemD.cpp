#include <bits/stdc++.h>
using namespace std;

typedef pair<char, char> cc;
typedef vector<int> vi;

bool common(cc &a, cc &b) {
    return a.first == b.first || a.first == b.second || a.second == b.first || a.second == b.second;
}

vi bg, by, br, gr, gy, ry;
vector<cc> cities;
vi *arrays[4];

void get_arrays(cc &city) {
    auto &[a, b] = city;
    if (a == 'B' && b == 'G') {
        arrays[0] = &by;
        arrays[1] = &br;
        arrays[2] = &gr;
        arrays[3] = &gy;
        // return {by, br, gr, gy};
    }
    else if (a == 'B' && b == 'R') {
        arrays[0] = &bg;
        arrays[1] = &by;
        arrays[2] = &gr;
        arrays[3] = &ry;
        // return {bg, by, gr, ry};
    }
    else if (a == 'B' && b == 'Y') {
        arrays[0] = &bg;
        arrays[1] = &br;
        arrays[2] = &gy;
        arrays[3] = &ry;
        // return {bg, br, gy, ry};
    }
    else if (a == 'G' && b == 'R') {
        arrays[0] = &bg;
        arrays[1] = &br;
        arrays[2] = &gy;
        arrays[3] = &ry;
        // return {bg, br, gy, ry};
    }
    else if (a == 'G' && b == 'Y') {
        arrays[0] = &bg;
        arrays[1] = &by;
        arrays[2] = &gr;
        arrays[3] = &ry;
        // return {bg, by, gr, ry};
    }
    else {
        assert(a == 'R' && b == 'Y');
        arrays[0] = &by;
        arrays[1] = &br;
        arrays[2] = &gr;
        arrays[3] = &gy;
    }
    

    // return {by, br, gr, gy};
}

int solve_left(vi *arr, int l) {
    int lo = 0, hi = (int) arr->size() - 1;
    int ans = -1;
    while (lo <= hi) {
        int m = (lo + hi) / 2;
        if (arr->at(m) < l) {
            ans = arr->at(m);
            lo = m + 1;
        }
        else {
            hi = m - 1;
        }
    }
    return ans;
}

int solve_right(vi *arr, int r) {
    int lo = 0, hi = (int) arr->size() - 1;
    int ans = -1;
    while (lo <= hi) {
        int m = (lo + hi) / 2;
        if (arr->at(m) > r) {
            ans = arr->at(m);
            hi = m - 1;
        }
        else {
            lo = m + 1;
        }
    }
    return ans;
}

int solve_middle(vi *arr, int l, int r) {
    int lo = 0, hi = (int) arr->size() - 1;
    while (lo <= hi) {
        int m = (lo + hi) / 2;
        if (arr->at(m) <= l) {
            lo = m + 1;
        }
        else if (arr->at(m) >= r) {
            hi = m - 1;
        }
        else return m;
    }
    return -1;
}

int solve(cc &city, int l, int r) {
    // vvi arrays = get_arrays(city);
    get_arrays(city);
    int ans = INT_MAX;
    for (vi *arr: arrays) {
        int curr = solve_middle(arr, l, r);
        if (curr != -1) {
            // cout << l << " " << r << " " << r - l << endl;
            return r - l;
        }
        // cout << curr << " ";
    }
    // cout << endl;

    for (vi *arr: arrays) {
        int lr = solve_left(arr, l);
        int rr = solve_right(arr, r);
        // cout << lr << " " << rr << endl;

        if (lr == -1 && rr == -1) continue;

        // ... l ... r ...
        int leftAns = abs(l - lr) + abs(r - lr);
        int rightAns = abs(rr - l) + abs(rr - r);
        if (lr == -1) {
            // use right result
            ans = min(ans, rightAns);
        }
        else if (rr == -1) {
            // use left result
            ans = min(ans, leftAns);
        }
        else {
            // use best result
            ans = min(ans, min(leftAns, rightAns));
            // if (abs(rr - r) < abs(lr - l)) {
            //     // use right result
            //     ans = min(ans, abs(rr - l) + abs(rr - r));
            // }
            // else {  // use left result
            //     ans = min(ans, abs(l - lr) + abs(r - lr));
            // }
        }
    }
    if (ans == INT_MAX) ans = -1;
    return ans;
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    int t;
    cin >> t;
    while (t--) {
        int n, q;
        cin >> n >> q;
        bg.clear();by.clear();br.clear();gr.clear();gy.clear();ry.clear();
        cities.resize(n);
        for (int i = 0; i < n; i++) {
            char a, b;
            cin >> a >> b;
            cities[i] = make_pair(a, b);
            if (a == 'B') {
                if (b == 'G') bg.push_back(i);
                else if (b == 'R') br.push_back(i);
                else {
                    assert(b == 'Y');
                    by.push_back(i);
                }
            }
            else if (a == 'G') {
                if (b == 'R') gr.push_back(i);
                else {
                    assert(b == 'Y');
                    gy.push_back(i);
                }
            }
            else {
                assert(a == 'R' && b == 'Y');
                ry.push_back(i);
            }
        }
        while (q--) {
            int xi, yi;
            cin >> xi >> yi;
            xi--; yi--;
            int tmp1 = xi, tmp2 = yi;
            xi = min(tmp1, tmp2);
            yi = max(tmp1, tmp2);
            int ans = -1;
            if (common(cities.at(xi), cities.at(yi))) {
                ans = yi - xi;
            }
            else {
                ans = solve(cities[xi], xi, yi);
            }
            cout << ans << '\n';
        }
    }
    return 0;
}
