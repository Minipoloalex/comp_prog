#include <bits/stdc++.h>
using namespace std;

#define LSO(n) ((n) & (-(n)))

class FT {
public:
    vector<int> ft;
    int size;

    FT(int sz) {
        size = sz + 1;
        ft.assign(size, 0);
    }

    void update(int i, int value) {
        for (; i < size; i += LSO(i)) ft.at(i) += value;
    }

    int get(int i) {
        int sum = 0;
        for (; i; i -= LSO(i)) sum += ft.at(i);
        return sum;
    }
};

class Solution
{
public:
    vector<int> resultArray(const vector<int> &nums)
    {
        int n = (int) nums.size();
        set<int> sorted(nums.begin(), nums.end());
        int m = (int) sorted.size();

        map<int, int> mp;
        int rank = 1;
        for (int num: sorted) mp[num] = rank++;

        vector<int> a1, a2;
        FT ft1(m), ft2(m);  // number of values <= than the value given (i)

        int v1 = nums[0], v2 = nums[1];

        a1.push_back(v1); ft1.update(mp[v1], 1);
        a2.push_back(v2); ft2.update(mp[v2], 1);

        for (int i = 2; i < n; i++) {
            int value = nums.at(i);
            rank = mp.at(value);
            int g1 = (int) a1.size() - ft1.get(rank);
            int g2 = (int) a2.size() - ft2.get(rank);
            if (g1 > g2) {
                a1.push_back(value); ft1.update(rank, 1);
            }
            else if (g1 < g2) {
                a2.push_back(value); ft2.update(rank, 1);
            }
            else {
                if (a1.size() <= a2.size()) {
                    a1.push_back(value); ft1.update(rank, 1);
                }
                else {
                    a2.push_back(value); ft2.update(rank, 1);
                }
            }
        }
        a1.insert(a1.end(), a2.begin(), a2.end());
        return a1;
    }
};

int main()
{
    Solution s;
    vector<int> nums, ans;
    // nums = {2, 1, 3, 3};
    // ans = s.resultArray(nums);
    // for (int a: ans) cout << a << " ";
    // cout << '\n';
    nums = {2, 47, 3, 3, 65, 7, 97, 4};
    ans = s.resultArray(nums);
    for (int a : ans)
        cout << a << " ";
    cout << '\n';

    return 0;
}
