#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long ull;

int main() {
    int T;
    cin >> T;
    while (T--) {
        int ncs, ne;
        cin >> ncs >> ne;

        vector<ull> cs(ncs);
        ull total_cs = 0;
        for (int i = 0; i < ncs; i++) {
            cin >> cs[i];
            total_cs += cs[i];
        }
        double avg_cs = (double) total_cs / (double) ncs;

        ull total_e = 0;
        for (int i = 0; i < ne; i++) {
            ull ei;
            cin >> ei;
            total_e += ei;
        }
        double avg_e = (double) total_e / (double) ne;
        // cout << "avg_cs = " << avg_cs << ", avg_e: " << avg_e << endl;
        
        int count = 0;
        for (int i = 0; i < ncs; i++) {
            if ((double) cs[i] < avg_cs && (double)cs[i] > avg_e) count++;
        }
        cout << count << endl;
    }
    return 0;
}
