https://www.geeksforgeeks.org/ordered-set-gnu-c-pbds/

```cpp
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;

// multiset: tree<pair<int,int>, null_type,less<pair<int,int>>,rb_tree_tag,tree_order_statistics_node_update>
#define ordered_set tree<int, null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update>
```

- `find_by_order(k)`: returns an iterator to the kth element (counting from zero)
- `order_of_key(x)`: returns the number of items that are strictly smaller than our item x.
