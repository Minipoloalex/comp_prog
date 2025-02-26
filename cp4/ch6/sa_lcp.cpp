#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> ii;
typedef vector<int> vi;

// Suffix Array data structure, allows long strings with ~ 3.5e5 ASCII chars
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

    // Usage: s += '\1'; SuffixArray sa(s.c_str(), (int) s.size());
    SuffixArray(const char *initialT, const int _n) : T(initialT), n(_n)
    {
        constructSA(); // O(n log n)
        computeLCP();  // O(n)
    }

    // returns [lb, ub] of sorted suffixes indices
    // otherwise (-1, -1) if not found
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

    // returns (LRS length, index in SA), (0, _) if none exists
    // Use s.substr(sa.SA[index], LRS length)
    ii LRS()
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

    ii most_repeated_substring()
    {
        int idx = -1, freq = 0;
        for (int i = 1; i < n; i++) {
            // TODO
            // find biggest segments with non-zero frequency
            // for example
            // 0 1 3 0 -> 1 is solution
            // Check CP4 book small exercises for formulation
        }
    }

    // Implemented by _FM
    // last char is not considered (special char)
    // @return Number of unique substrings of the string given in the Suffix Array.
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

const int MAX_N = 450010; // can go up to 450K chars

char T[MAX_N];
char P[MAX_N];
char LRS_ans[MAX_N];
char LCS_ans[MAX_N];

void test_unique_substrings() {
    string s = "azaza\1";
    SuffixArray sa(s.c_str(), (int) s.size());
    cout << sa.count_unique_substrings() << '\n';
}

int main()
{
    // freopen("sa_lcp_in.txt", "r", stdin);
    // scanf("%s", &T);        // read T
    // int n = (int)strlen(T); // count n
    // T[n++] = '$';           // add terminating symbol
    // SuffixArray S(T, n);    // construct SA+LCP

    // printf("T = '%s'\n", T);
    // printf(" i SA[i] LCP[i]   Suffix SA[i]\n");
    // for (int i = 0; i < n; ++i)
    //     printf("%2d    %2d    %2d    %s\n", i, S.SA[i], S.LCP[i], T + S.SA[i]);

    // // String Matching demo, we will try to find P in T
    // strcpy(P, "A");
    // auto [lb, ub] = S.stringMatching(P);
    // if ((lb != -1) && (ub != -1))
    // {
    //     printf("P = '%s' is found SA[%d..%d] of T = '%s'\n", P, lb, ub, T);
    //     printf("They are:\n");
    //     for (int i = lb; i <= ub; ++i)
    //         printf("  %s\n", T + S.SA[i]);
    // }
    // else
    //     printf("P = '%s' is not found in T = '%s'\n", P, T);

    // // LRS demo, find the LRS of T
    // auto [LRS_len, LRS_idx] = S.LRS();
    // strncpy(LRS_ans, T + S.SA[LRS_idx], LRS_len);
    // printf("The LRS is '%s' with length = %d\n", LRS_ans, LRS_len);

    // // LCS demo, find the LCS of (T, P)
    // strcpy(P, "CATA");
    // int m = (int)strlen(P);
    // strcat(T, P);       // append P to T
    // strcat(T, "#");     // add '#' at the back
    // n = (int)strlen(T); // update n

    // // reconstruct SA of the combined strings
    // SuffixArray S2(T, n); // reconstruct SA+LCP
    // int split_idx = n - m - 1;
    // printf("T+P = '%s'\n", T);
    // printf(" i SA[i] LCP[i] From  Suffix SA[i]\n");
    // for (int i = 0; i < n; ++i)
    //     printf("%2d    %2d    %2d    %2d    %s\n",
    //            i, S2.SA[i], S2.LCP[i], S2.SA[i] < split_idx ? 1 : 2, T + S2.SA[i]);

    // auto [LCS_len, LCS_idx] = S2.LCS(split_idx);
    // strncpy(LCS_ans, T + S2.SA[LCS_idx], LCS_len);
    // printf("The LCS is '%s' with length = %d\n", LCS_ans, LCS_len);

    test_unique_substrings();
    return 0;
}
