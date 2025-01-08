## Sorting & Searching
### Operations on Sorted Sets
```cpp
set<int> s;
...
s.upper_bound(7);                   // log N
upper_bound(s.begin(), s.end(), 7); // N
```

#### Sorted sets vs Ordered statistics tree
One limitation of sorted sets is that we can't efficiently access the  $k^{th}$ largest element in the set, or find the number of elements in the set greater than some arbitrary  $x$. Order statistics tree handles this (or Fenwick Tree).


