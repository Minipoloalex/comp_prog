#include <bits/stdc++.h>
using namespace std;

// Setup for random number generation
/*
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
uniform_int_distribution<int> gen(0, INT_MAX);
*/

// Copy starting from here:

typedef uniform_int_distribution<int> uni;
typedef uniform_int_distribution<int64_t> unll;

int main(int argc, char *argv[]) {
    cin.tie(0)->ios::sync_with_stdio(0);

    // Likely that we want receive the loop iteration in the testing script as a seed
    // int seed = atoi(argv[1]);
    // mt19937 rng(seed);
    int n = 5;
    cout << n << '\n';

    return 0;
}
