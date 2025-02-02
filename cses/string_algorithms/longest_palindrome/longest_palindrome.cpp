#include <bits/stdc++.h>
using namespace std;

// Gets the longest palindromic substring of the given string
// Computes dp[i] that represents the diameter of the palindrome centered at i
// For example:
// "aybabtu": "# a # y # b # a # b # t # u #"
// dp       :  1,3,1,3,1,3,1,7,1,3,1,3,1,3,1
string menacher(const string &s) {
	// Preprocess the input so it can handle even length palindromes
	string arr;
	for (int i = 0; i < (int) s.size(); i++) {
		arr.push_back('#');
		arr.push_back(s[i]);
	}
	arr.push_back('#');

	// dp[i] = palindrome's maximum diameter centered at i
	vector<int> dp((int) arr.size());
	int left = 0, right = 0;
	int lg_max = 0, lg_max_idx = 0;
	for (int i = 0; i < (int) arr.size(); ) {
		// Expand the palindrome around i
		while (left > 0 && right < (int) arr.size() - 1 && arr[left - 1] == arr[right + 1]) {
			left--;
			right++;
		}

		// Update the diameter
		dp[i] = right - left + 1;

		if (lg_max < dp[i]) {
			lg_max = dp[i];
			lg_max_idx = i;
		}

		/*
		 * We've already computed the values for [left, i] interval.
		 * The values on the right side of the palindrome [i+1, right] will
		 * be the same as the ones on the left side except when some palindromes
		 * go beyond the current [left, right] palindrome.
		 */
		int new_center = right + (i % 2 == 0 ? 1 : 0);  // i % 2 == 0 <=> s[i] == '#' (delimiter)
		for (int j = i + 1; j <= right; j++) {
			/*
			 * i - (j - i) represents the mirror of j on the left side of the
			 * palindrome. It's possible that the left mirror of j might go
			 * beyond the current palindrome - it crosses the left border. To
			 * avoid taking the wrong answer, take the minimum of the left
			 * mirror of j and the diameter of palindrome centered at j ending
			 * at right.
			 */
			dp[j] = min(dp[i - (j - i)], 2 * (right - j) + 1);

			// Update the max diameter
			if (lg_max < dp[i]) {
				lg_max = dp[i];
				lg_max_idx = i;
			}

			/*
			 * If the palindrome centered at j reaches the right border of the
			 * current palindrome it might go even beyond.
			 * Considering this make the new_center = j.
			 */
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

    // Given the length of the longest palindromic substring and its index
    // Get the corresponding original string characters
	string ans;
    int idx = lg_max_idx;
	for (int j = idx - dp[idx] / 2; j <= idx + dp[idx] / 2; j++) {
		if (arr[j] != '#') { ans.push_back(arr[j]); }
	}
	return ans;
}

void solve() {
	string s;
	cin >> s;
	cout << menacher(s) << '\n';
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    solve();
    return 0;
}
