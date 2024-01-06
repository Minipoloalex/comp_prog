#include <bits/stdc++.h>
using namespace std;

typedef vector<unsigned long long> vull;
vull customers;

int main() {
    // wood piece sizes: [1, 1000]
    int T;
    cin >> T;
    while (T--) {   // T test cases
        int N; cin >> N;
        customers.clear();
        for (int i = 0; i < N; i++) {   // N clients
            int Wi; cin >> Wi;
            unsigned long long sum = 0;
            for (int j = 0; j < Wi; j++) {  // 1 client, Wi wood pieces
                unsigned long long val;
                cin >> val;
                sum += val;
            }
            customers.push_back(sum);
        }
        sort(customers.begin(), customers.end());
        
        // at each iteration -> know how many customers are left to be able to multiply value * n_customers_waiting
        unsigned long long total_wait = 0;
        unsigned long long sum = 0;
        for (int i = 0; i < N; i++) {
            sum += customers[i];
            
            total_wait += sum;
            // cout << sum << endl;
            // cout << total_wait << endl;
            // cout << "--" << endl;
            // total_wait += (N - i) * customers[i];
        }
        // cout << total_wait << endl;
        double res = total_wait / ((double)customers.size());
        cout << fixed << setprecision(10) << res << endl;

    }
    return 0;
}
