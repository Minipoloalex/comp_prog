#include <bits/stdc++.h>
using namespace std;

#define LSB(i) ((i) & -(i))

class Solution {
private:
    int n, mask;
    vector<int> curr_solution;
    vector<vector<string>> solutions;

    void save_solution() {
        vector<string> solution(n);
        for (int r = 0; r < n; r++) {
            int col_to_power_of_2 = curr_solution[r];

            // we could also use __builtin_ctz which returns the count of trailing zeros
            // that would be faster since it avoids floating point calculations but it is g++ specific (not c++ in general)
            int col = int(log2(col_to_power_of_2));
            string s(col, '.'); // '.' until col
            s += 'Q';           // 'Q' in col
            s += string(n - col - 1, '.');  // from there, just '.'
            solution[r] = s;
        }
        solutions.push_back(solution);
    }

    void place_queen(int col_bits, int maj_diag_bits, int min_diag_bits) {
        // cout << curr_solution.size() << " "  << col_bits << endl;
        // base case (finished)
        if (col_bits == mask) { // could also check: curr_solution.size() == n
            // all columns are filled -> found a solution
            save_solution();
            return;
        }

        // An int has 32 bits, so many will be set to 1 (after the bitwise NOT)
        // The mask ensures that bits outside the range are avoided, using only the n bits that represent valid columns
        int possible_bits = ~(col_bits | maj_diag_bits | min_diag_bits) & mask;
        for (int bit; possible_bits > 0; ) {
            bit = LSB(possible_bits);
            possible_bits ^= bit;   // trying this bit (should remove it from possible bits)
            curr_solution.push_back(bit);
            place_queen(col_bits | bit, (maj_diag_bits | bit) << 1, (min_diag_bits | bit) >> 1);
            curr_solution.pop_back();
        }
    }
    void solve() {
        place_queen(0, 0, 0);
    }
public:
    vector<vector<string>> solveNQueens(int n) {
        this->n = n;
        mask = (1 << n) - 1;
        solve();
        return solutions;
    }
};
