#include <bits/stdc++.h>
using namespace std;

#define LSB(i) ((i) & -(i))

class QueensSolver {
private:
    int n;
    vector<int> curr_solution;
    vector<vector<string>> solutions;
    int solution_count;

    void save_solution() {
        vector<string> solution(n);
        for (int r = 0; r < n; r++) {
            int col = curr_solution[r];
            string s(col, '.'); // '.' until col
            s += 'Q';           // 'Q' in col
            s += string(n - col - 1, '.');  // from there, just '.'
            solution[r] = s;
        }
        solutions.push_back(solution);
    }

    // The only thing that matters in these two functions is
    // that a specific diagonal is always mapped to the same index
    // and that this index fits within the vector size given
    int get_maj_diag(int r, int c) {
        return c - r + (n - 1);     // + (n - 1) ensures that the diagonal has a valid index (>= 0)
    }
    int get_min_diag(int r, int c) {
        return r + c;   // the same min diagonals have the same coordinate sum
    }

    void place_queen(int r, vector<bool> &filled_cols, vector<bool> &filled_maj_diags, vector<bool> &filled_min_diags) {
        if (r == n) {    // row outside board
            // means that every queen is placed so we just found a solution
            save_solution();

            return;     // backtrack
        }
        for (int c = 0; c < n; c++) {   // go through all possible columns
            // check if column c is valid -> need to check diagonals and columns
            int maj_diag = get_maj_diag(r, c);
            int min_diag = get_min_diag(r, c);

            if (!filled_cols[c] && !filled_maj_diags[maj_diag] && !filled_min_diags[min_diag]) {
                curr_solution.push_back(c);
                filled_cols[c] = true;
                filled_maj_diags[maj_diag] = true;
                filled_min_diags[min_diag] = true;

                place_queen(r + 1, filled_cols, filled_maj_diags, filled_min_diags);

                curr_solution.pop_back();   // reset updates from this column and try another one
                filled_cols[c] = false;
                filled_maj_diags[maj_diag] = false;
                filled_min_diags[min_diag] = false;
            }
        }
    }

public:
    QueensSolver(int _n):
        n(_n) {
        solution_count = 0;
    }

    vector<vector<string>> solve() {
        int nr_of_diagonals = n * 2 - 1;    // total number of diagonals to one side
        vector<bool> filled_cols(n, false), filled_maj_diags(nr_of_diagonals, false), filled_min_diags(nr_of_diagonals, false);

        place_queen(0, filled_cols, filled_maj_diags, filled_min_diags);
        return solutions;
    }
};


class Solution {
public:
    vector<vector<string>> solveNQueens(int n) {
        QueensSolver qs = QueensSolver(n);
        return qs.solve();
    }
};
int main() {
    return 0;
}
