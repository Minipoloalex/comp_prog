#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n = 7, k = 3;
    vector<int> taken(n, 0);
    // initially none taken
    for (int i = n - k; i < n; ++i)
        taken[i] = 1;
    // last k are taken (sorted)
    do
    {
        // iterate C(7, 3) = 35x
        for (int i = 0; i < n; ++i)
            if (taken[i])
                printf("%d ", i);
        printf("\n");
    } while (next_permutation(taken.begin(), taken.end()));
}
