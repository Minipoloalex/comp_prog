#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> ii;
typedef vector<int> vi;

// Suffix Array data structure, allows long strings with 350K ASCII chars = 3.5e5
// Assumes the existence of a terminal character (smaller in ascii value than all of the others)
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
    // must have end special char (delimter) smaller than all of its chars
    const int n; // the length of T (including the last special char)
    vi SA;       // Suffix Array (size n, includes special char)
    vi LCP;      // LCP of adj sorted suffixes (size n, includes special char)
    // SA[0]: suffix of special (end) char
    // LCP = [N/A, 0 or N/A, ...]

    SuffixArray(const char *initialT, const int _n) : T(initialT), n(_n)
    {
        constructSA(); // O(n log n)
        computeLCP();  // O(n)
    }

    ii stringMatching(const char *P)
    {                           // in O(m log n)
        int m = (int)strlen(P); // usually, m < n
        int lo = 0, hi = n - 1; // range = [0..n-1]
        while (lo < hi)
        {                                         // find lower bound
            int mid = (lo + hi) / 2;              // this is round down
            int res = strncmp(T + SA[mid], P, m); // P in suffix SA[mid]?
            (res >= 0) ? hi = mid : lo = mid + 1; // notice the >= sign
        }
        if (strncmp(T + SA[lo], P, m) != 0)
            return {-1, -1}; // if not found
        ii ans;
        ans.first = lo;
        hi = n - 1; // range = [lo..n-1]
        while (lo < hi)
        { // now find upper bound
            int mid = (lo + hi) / 2;
            int res = strncmp(T + SA[mid], P, m);
            (res > 0) ? hi = mid : lo = mid + 1; // notice the > sign
        }
        if (strncmp(T + SA[hi], P, m) != 0)
            --hi; // special case
        ans.second = hi;
        return ans; // returns (lb, ub)
    } // where P is found

    ii LRS() // returns (LRS length, index)
    {
        int idx = 0, maxLCP = -1;
        for (int i = 1; i < n; ++i) // O(n), start from i = 1
            if (LCP[i] > maxLCP)
                maxLCP = LCP[i], idx = i;
        return {maxLCP, idx};
    }

    // returns (LCS length, index in SA), (0, _) if none exists
    // SA[idx], SA[idx - 1]: give the suffixes with LCS
    ii LCS(int split_idx)
    {
        int idx = 0, maxLCP = -1;
        for (int i = 1; i < n; ++i)
        { // O(n), start from i = 1
            // if suffix SA[i] and suffix SA[i-1] came from the same string, skip
            if ((SA[i] < split_idx) == (SA[i - 1] < split_idx))
                continue;
            if (LCP[i] > maxLCP)
                maxLCP = LCP[i], idx = i;
        }
        return {maxLCP, idx};
    }
    /**
     * @brief Implemented by _FM (Needs further tests)
     *
     * @return int Number of unique repeated substrings of the string given in the Suffix Array.
     */
    int unique_repeated_substrings()
    {
        int ans = 0;
        for (int i = 1; i < n; ++i)
        {
            if (LCP[i] > LCP[i - 1])
                ans += LCP[i] - LCP[i - 1];
        }
        return ans;
    }

    // Implemented by _FM
    // last char is not considered (special char)
    // @return int Number of unique substrings of the string given in the Suffix Array.
    int64_t count_unique_substrings()
    {
        // exclude last char
        int64_t ans = (int64_t) n * (n - 1) / 2;
        for (int i = 1; i < n; i++)
        {
            ans -= LCP[i];
        }
        return ans;
    }
};

void solve() {
    string s, t;
    cin >> s >> t;
    string both = s + '\1' + t + '\2';
    SuffixArray sa(both.c_str(), (int) both.size());
    int split_idx = int(s.size());
    auto [lcs_len, lcs_idx] = sa.LCS(split_idx);
    if (lcs_len == 0) {
        cout << "0 0 0 0\n";
    }
    else {
        int sfx1 = sa.SA[lcs_idx];  // we compared it with the previous idx
        int sfx2 = sa.SA[lcs_idx - 1];
        if (sfx2 < sfx1) {
            // sfx1: first string
            // sfx2: second string
            swap(sfx1, sfx2);
        }
        int a = sfx1, b = a + lcs_len; // [a, b)
        int c = sfx2, d = c + lcs_len; // [c, d)

        // make the indices relative to t, not the composed string
        c -= int(s.size() + 1);
        d -= int(s.size() + 1);
        cout << a << " " << b << " " << c << " " << d << '\n';      
    }
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    solve();
    return 0;
}
