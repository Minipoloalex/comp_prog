#include <bits/stdc++.h>
using namespace std;

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;


// Solution help on https://niteshim111.hashnode.dev/secret-data-structures-of-c-pbds-library

// template <typename T>
// using ordered_set = tree<T, null_type, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;

// allowing duplicates with less_equal is not a good practice, should use a pair
// can be represented as <value, index in array>
using ordered_set = tree<pair<int, int>, null_type, less<pair<int, int>>, rb_tree_tag, tree_order_statistics_node_update>;

class Solution
{
public:
    vector<int> resultArray(vector<int> &nums)
    {
        int n = (int)nums.size();
        vector<int> a1, a2;
        ordered_set os1, os2;
        a1.push_back(nums[0]);
        a2.push_back(nums[1]);
        os1.insert(make_pair(nums[0], 0));
        os2.insert(make_pair(nums[1], 1));

        for (int i = 2; i < (int)nums.size(); i++)
        {
            int value = nums[i];

            // for less_equal implementation (only int and not pair)
            // greater_than = arr.size() - os.order_of_key(value + 1)
            /*
            e.g.
            - If smallest (should be inserted in position 0) then greather_than = arr.size()
            - If 2nd smallest greater_than = arr.size() - 1
            (should be inserted in position 1, since it is bigger than 1 element)
            - If equal to smallest, should be inserted in position 0 as well.
            This would make greater_than = arr.size(), which is wrong
            If we add 1 to the value, it will still be inserted before every equal value,
            and arr.size() - insertion_index will only result in > and not >= values
            */

            // To search we use n as the index (for the same reason as the + 1 above)
            // Makes the second value of the pair the biggest, resulting in insertions after equal values (first)
            // When subtracting, we will get the values > and not >=.
            pair<int, int> valpair = make_pair(value, n);

            int greater_cnt_1 = (int)(a1.size() - os1.order_of_key(valpair));
            int greater_cnt_2 = (int)(a2.size() - os2.order_of_key(valpair));
            cout << value << " " << os1.order_of_key(valpair) << " " << os2.order_of_key(valpair) << " " << greater_cnt_1 << " " << greater_cnt_2 << '\n';

            valpair.second = i;
            if (greater_cnt_1 > greater_cnt_2)
            {
                a1.push_back(value);
                os1.insert(valpair);
            }
            else if (greater_cnt_1 < greater_cnt_2)
            {
                a2.push_back(value);
                os2.insert(valpair);
            }
            else
            {
                if (a1.size() <= a2.size())
                {
                    a1.push_back(value);
                    os1.insert(valpair);
                }
                else
                {
                    a2.push_back(value);
                    os2.insert(valpair);
                }
            }
        }

        for (int a : a2)
            a1.push_back(a);
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
