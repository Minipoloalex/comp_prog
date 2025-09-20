#include <bits/stdc++.h>
using namespace std;

// Setup for random number generation
/*
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
uniform_int_distribution<int> gen(0, INT_MAX);
int random_value = gen(rng);
*/

int main(int argc, char *argv[]) {
    cin.tie(0)->ios::sync_with_stdio(0);

    // Likely that we want receive the loop iteration in the testing script as a seed
    int seed = atoi(argv[1]);
    mt19937 rng(seed);

    int n = uniform_int_distribution<int>(2, 10)(rng);
    int q = uniform_int_distribution<int>(1, 200)(rng);
    set<pair<int,int>> qs;
    int iters = 0, MX_ITERS = 100;
    while (int(qs.size()) <= q && iters < MX_ITERS) {
        int a = uniform_int_distribution<int>(1,n)(rng);
        int b = uniform_int_distribution<int>(1,n)(rng);
        if (a == b) {
            iters++;
            continue;
        }

        int mn = min(a, b);
        int mx = max(a, b);

        auto [_, inserted] = qs.emplace(mn, mx);
        if (inserted) iters = 0;
        else iters++;
    }
    vector<pair<int,int>> queries(qs.begin(), qs.end());
    shuffle(queries.begin(), queries.end(), rng);

    cout << n << " " << int(qs.size()) << '\n';
    for (auto &[a, b]: queries) {
        cout << a << " " << b << '\n';
    }
    return 0;
}
