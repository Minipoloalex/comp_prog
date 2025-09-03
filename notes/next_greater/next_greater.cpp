#include <bits/stdc++.h>
using namespace std;

// These are both implicit monotonic stack-based approaches (assume a valid comparator cmp: transitivity)
/**
 * For each position, gives the 0-based index of the closest element on the left of it for which cmp is true
 * Gives -1 if there's none
 * Formally, for each index i, gives the first index on the left j < i, s.t. cmp(a[j], a[i]) is true
 * Usage:
 *  auto pg = closest_left(a, greater<int>());   // for previous (strictly) greater
 */
template<typename T, typename Pred>
vector<int> closest_left(const vector<T> &a, Pred cmp) {
    int n = int(a.size()); vector<int> closest(n); iota(closest.begin(), closest.end(), -1);
    for (int i = 0; i < n; i++) {
        auto &j = closest[i];
        while(j >= 0 && !cmp(a[j], a[i])) j = closest[j];
    }
    return closest;
}

/**
 * For each position, gives the 0-based index of the closest element on the right of it for which cmp is true
 * Gives a.size() if there's none
 * Formally, for each index i, gives the first index on the right j > i, s.t. cmp(a[j], a[i]) is true
 * Usage:
 *  auto ng = closest_right(a, greater<int>());   // for next (strictly) greater
 */
template<typename T, typename Pred>
vector<int> closest_right(const vector<T> &a, Pred cmp) {
    int n = int(a.size()); vector<int> closest(n); iota(closest.begin(), closest.end(), 1);
    for (int i = n - 1; i >= 0; i--) {
        auto &j = closest[i];
        while(j < n && !cmp(a[j], a[i])) j = closest[j];
    }
    return closest;
}
