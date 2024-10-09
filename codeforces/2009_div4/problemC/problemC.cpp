#include <bits/stdc++.h>
using namespace std;

int main() {
    int t;
    cin >> t;
    while (t--) {
        double x, y, k;
        cin >> x >> y >> k;
        int64_t hor_jumps = (int64_t) ceil(x / k);
        int64_t vert_jumps = (int64_t) ceil(y / k);
        int64_t ans;
        if (hor_jumps == vert_jumps || (hor_jumps == vert_jumps + 1)) ans = hor_jumps + vert_jumps;
        else if (vert_jumps > hor_jumps) {  // x, x + ...
            ans = vert_jumps + hor_jumps + (vert_jumps - hor_jumps);
        }
        else {  // y + ..., y
            assert(hor_jumps > vert_jumps);
            ans = hor_jumps + vert_jumps + (hor_jumps - vert_jumps - 1);
        }
        cout << ans << '\n';
    }
    return 0;
}
