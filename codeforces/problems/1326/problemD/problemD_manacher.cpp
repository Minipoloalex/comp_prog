#include <bits/stdc++.h>
using namespace std;

// Gets the longest palindromic substring of the given string
// Computes dp[i] that represents the diameter of the palindrome centered at i
// For example:
// "aybabtu": "# a # y # b # a # b # t # u #"
// dp       :  1,3,1,3,1,3,1,7,1,3,1,3,1,3,1
// "aybaabtu":"# a # y # b # a # a # b # t # u #"
// dp        : 1,3,1,3,1,3,1,3,9,3,1,3,1,3,1,3,1
vector<int> manacher_dp;
string manacher_arr;

void manacher(const string &s) {
    string &arr = manacher_arr;
    arr.clear();
    vector<int> &dp = manacher_dp;

	// Preprocess the input so it can handle even length palindromes
	for (int i = 0; i < (int) s.size(); i++) {
		arr.push_back('#');
		arr.push_back(s[i]);
	}
	arr.push_back('#');

	// dp[i] = palindrome's maximum diameter centered at i
	dp.assign(arr.size(), 0);
	int left = 0, right = 0;
	for (int i = 0; i < (int) arr.size(); ) {
		// Expand the palindrome around i
		while (left > 0 && right < (int) arr.size() - 1 && arr[left - 1] == arr[right + 1]) {
			left--;
			right++;
		}

		// Update the diameter
		dp[i] = right - left + 1;


        // We've already computed the values for [left, i] interval.
		// The values on the right side of the palindrome [i+1, right] will
		// be the same as the ones on the left side except when some palindromes
		// go beyond the current [left, right] palindrome.
		int new_center = right + (i % 2 == 0 ? 1 : 0);  // i % 2 == 0 <=> s[i] == '#' (delimiter)
		for (int j = i + 1; j <= right; j++) {
			// i - (j - i) represents the mirror of j on the left side of the
			// palindrome. It's possible that the left mirror of j might go
			// beyond the current palindrome - it crosses the left border. To
			// avoid taking the wrong answer, take the minimum of the left
			// mirror of j and the diameter of palindrome centered at j ending
			// at right.
			dp[j] = min(dp[i - (j - i)], 2 * (right - j) + 1);

			// If the palindrome centered at j reaches the right border of the
			// current palindrome it might go even beyond.
			// Considering this make the new_center = j.
			if (j + dp[i - (j - i)] / 2 == right) {
				new_center = j;
				break;
			}
		}

		// Move to the new_center and update the left and right borders.
		i = new_center;
		right = i + dp[i] / 2;
		left = i - dp[i] / 2;
	}
}

void solve() {
    string s;
    cin >> s;
    manacher(s);
    int n = (int) manacher_arr.size();

    auto get_ans = [&](pair<int,int> &ans, pair<int,int> cur) {
        int ans_sz = ans.first / 2 + ans.second / 2;
        int ans_cur = cur.first / 2 + cur.second / 2;
        if (ans_sz < ans_cur) {
            ans = cur;
        }
    };
    pair<int,int> ans = {0, 0};

    // this could be better implemented: editorial at: https://codeforces.com/blog/entry/74961
    for (int i = 0; i < n; i++) {
        // if can get to left, or right
        int lp_radius = manacher_dp[i] / 2;
        if (i - lp_radius == 0) {
            // cout << i << " " << lp_radius << " " << manacher_dp[i] << " " << 0 << '\n';
            get_ans(ans, {manacher_dp[i], 0});
        }
        else if (i + lp_radius == n - 1) {
            // cout << i << " " << lp_radius << " " << 0 << " " << manacher_dp[i] << '\n';
            get_ans(ans, {0, manacher_dp[i]});
        }
    }
    int mxl = -1, mxr = -1;
    for (int i = 0; i < n / 2; i++) {
        if (manacher_arr[i] != manacher_arr[n - i - 1]) {
            break;
        }
        mxl = i;
        mxr = n - i - 1;
    }
    if (mxl != -1 && mxr != -1) {
        for (int i = mxl + 1; i < mxr; i++) {
            int lp_radius = manacher_dp[i] / 2;
            if (i - lp_radius <= mxl) {
                lp_radius = i - (mxl + 1);  // difference to (mxl + 1)
            }
            if (i + lp_radius >= mxr) {
                lp_radius = (mxr - 1) - i;  // difference to (mxr - 1)
            }
            
            // the indices given by i + lp_radius and i - lp_radius are inclusive
            if (i - lp_radius == mxl + 1) {
                get_ans(ans, {i + lp_radius + 1, n - mxr});
            }
            if (i + lp_radius == mxr - 1) {
                get_ans(ans, {mxl + 1, n - (i - lp_radius)});
            }
        }
    }

    string t;
    // cout << ans.first << " " << ans.second << " ";
    for (int i = 0; i < ans.first; i++) {
        if (manacher_arr[i] == '#') continue;
        t += manacher_arr[i];
    }
    for (int i = n - ans.second; i < n; i++) {
        if (manacher_arr[i] == '#') continue;
        t += manacher_arr[i];
    }
    cout << t << '\n';
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
