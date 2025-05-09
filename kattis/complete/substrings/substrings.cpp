#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> ii;
typedef vector<int> vi;

class SuffixArray
{
private:
    vi RA; // rank array

    void countingSort(int k)
    {                                       // O(n)
        int maxi = max(300, n);             // up to 255 ASCII chars
        vi c(maxi, 0);                      // clear frequency table
        for (int i = 0; i < n; ++i)         // count the frequency
            ++c[i + k < n ? RA[i + k] : 0]; // of each integer rank
        for (int i = 0, sum = 0; i < maxi; ++i)
        {
            int t = c[i];
            c[i] = sum;
            sum += t;
        }
        vi tempSA(n);
        for (int i = 0; i < n; ++i) // sort SA
            tempSA[c[SA[i] + k < n ? RA[SA[i] + k] : 0]++] = SA[i];
        swap(SA, tempSA); // update SA
    }

    void constructSA()
    { // can go up to 400K chars
        SA.resize(n);
        iota(SA.begin(), SA.end(), 0); // the initial SA
        RA.resize(n);
        for (int i = 0; i < n; ++i)
            RA[i] = T[i]; // initial rankings
        for (int k = 1; k < n; k <<= 1)
        { // repeat log_2 n times
            // this is actually radix sort
            countingSort(k); // sort by 2nd item
            countingSort(0); // stable-sort by 1st item
            vi tempRA(n);
            int r = 0;
            tempRA[SA[0]] = r;          // re-ranking process
            for (int i = 1; i < n; ++i) // compare adj suffixes
                tempRA[SA[i]] =         // same pair => same rank r; otherwise, increase r
                    ((RA[SA[i]] == RA[SA[i - 1]]) && (RA[SA[i] + k] == RA[SA[i - 1] + k])) ? r : ++r;
            swap(RA, tempRA); // update RA
            if (RA[SA[n - 1]] == n - 1)
                break; // nice optimization
        }
    }

    void computeLCP()
    {
        vi Phi(n);
        vi PLCP(n);
        PLCP.resize(n);
        Phi[SA[0]] = -1;            // default value
        for (int i = 1; i < n; ++i) // compute Phi in O(n)
            Phi[SA[i]] = SA[i - 1]; // remember prev suffix
        for (int i = 0, L = 0; i < n; ++i)
        { // compute PLCP in O(n)
            if (Phi[i] == -1)
            {
                PLCP[i] = 0;
                continue;
            } // special case
            while ((i + L < n) && (Phi[i] + L < n) && (T[i + L] == T[Phi[i] + L]))
                ++L; // L incr max n times
            PLCP[i] = L;
            L = max(L - 1, 0); // L dec max n times
        }
        LCP.resize(n);
        for (int i = 0; i < n; ++i) // compute LCP in O(n)
            LCP[i] = PLCP[SA[i]];   // restore PLCP
    }
public:
    const char *T; // the input string
    const int n;   // the length of T
    vi SA;         // Suffix Array
    vi LCP;        // of adj sorted suffixes

    SuffixArray(const char *initialT, const int _n) : T(initialT), n(_n)
    {
        constructSA(); // O(n log n)
        computeLCP();  // O(n)
    }

    /**
     * @brief Implemented by _FM
     * 
     * @return int Number of unique substrings of the string given in the Suffix Array.
     * Assumes the existence of a terminal character (smaller in ascii valuethan all of the others)
     */
    int unique_substrings() {
        int res = 0;
        for (int i = 1; i < n; i++) {
            // (n - i) instead of (n - i + 1)
            // last character is not considered
            res += n - i - LCP[i];
        }
        return res;
    }
    int unique_repeated_substrings() {
        int ans = 0;
		for (int i = 1; i < n; ++i) {
			if (LCP[i] > LCP[i - 1])
				ans += LCP[i] - LCP[i - 1];
		}
        return ans;
    }
};

/*
aab		    0
aabaab		3
ab		    1
abaab		2
b		    0
baab		1
21 total substrings
14 unique substrings
7 repeated substrings (non-unique)

5 unique repeated substrings
*/
int main() {
    int t;
    cin >> t;
    while (t--) {
        string s;
        cin >> s;
        s += '\1';
        int n = (int) s.size();
        SuffixArray sa(s.c_str(), n);
        cout << sa.unique_repeated_substrings() << '\n';
    }
    return 0;
}
