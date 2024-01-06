#include <bits/stdc++.h>
#include <ios>
using namespace std;

typedef vector<int> vi;
typedef vector<unsigned long long> vull;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int N, Q;
    cin >> N >> Q;
    vull A(N);  // will hold cummulative sum, which could be 10e9 * 2 * 10e5 = 2 * 10e14
    vi B(Q);
    for (int i = 0; i < N; i++) cin >> A[i];
    for (int i = 0; i < Q; i++) cin >> B[i];
    
    sort(A.begin(), A.end());
    for (int i = 1; i < N; i++) {
        A[i] += A[i - 1];   // cumulative sum -> rsq(1, i), 1 <= 1 <= 10e5
    }
    for (int j = 0; j < Q; j++) {
        cout << A.at(B[j] - 1) << endl;
    }
    return 0;
}
