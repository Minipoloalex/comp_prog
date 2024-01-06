#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;

void set_to_i(vi &indices) {
    for (int i = 0; i < (int) indices.size(); i++) {
        indices[i] = i;
    }
}


void collatz(int x, vi &x_nums) {
    x_nums.push_back(x);
    if (x == 1) return;
    if (x % 2 == 0) {
        x /= 2;
        collatz(x, x_nums);
    }
    else {
        x = 3 * x + 1;
        collatz(x, x_nums);
    }
}

int main() {
    int a, b;   // [1, 1e6]
    while (cin >> a >> b) {
        if (a == 0 && b == 0) break;
        vi a_nums;
        vi b_nums;
        collatz(a, a_nums);
        vi indices_a(a_nums.size());
        set_to_i(indices_a);

        collatz(b, b_nums);
        vi indices_b(b_nums.size());
        set_to_i(indices_b);

        sort(indices_a.begin(), indices_a.end(), [&a_nums](int i1, int i2) {
            return a_nums[i1] > a_nums[i2];
        });
        sort(indices_b.begin(), indices_b.end(), [&b_nums](int i1, int i2) {
            return b_nums[i1] > b_nums[i2];
        });

        int steps_a = 1e9, steps_b = 1e9, number = -1;
        long unsigned int i = 0, j = 0;
        while (i < a_nums.size() && j < b_nums.size()) {
            int A = a_nums[indices_a[i]];
            int B = b_nums[indices_b[j]];
            if (A == B) {
                if (indices_a[i] < steps_a) {
                    steps_a = indices_a[i];
                    steps_b = indices_b[j];
                    number = A;
                }
                i++;
                j++;
            }
            else if (A > B) i++;   // descending order -> decrease A to get closer to B
            else j++;  // B > A -> decrease B to get closer to A
        }
        cout << a << " needs " << steps_a << " steps, " << b << " needs " 
        << steps_b << " steps, they meet at " << number << endl;

    }
    return 0;
}
