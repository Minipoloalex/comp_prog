## LIS algorithms

Better explanation and comparison of DP algorithms 
at https://cp-algorithms.com/sequences/longest_increasing_subsequence.html.


### DP arrays

#### First solution
To accomplish this task, we define an array  $d[0 \dots n-1]$ , where  $d[i]$  is the length of the longest increasing subsequence that ends in the element at index  $i$ .

```cpp
int lis(vector<int> const& a) {
    int n = a.size();
    vector<int> d(n, 1);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (a[j] < a[i])
                d[i] = max(d[i], d[j] + 1);
        }
    }

    int ans = d[0];
    for (int i = 1; i < n; i++) {
        ans = max(ans, d[i]);
    }
    return ans;
}
```

#### O(N logN) binary search solution
We will use the dynamic programming array  $d[0 \dots n]$ . This time  $d[l]$  doesn't corresponds to the element  $a[i]$  or to an prefix of the array.  $d[l]$  will be the smallest element at which an increasing subsequence of length  $l$  ends.

##### Restoring subsequence
It is also possible to restore the subsequence using this approach. This time we have to maintain two auxiliary arrays. One that tells us the index of the elements in  $d[]$ . And again we have to create an array of "ancestors"  $p[i]$ .  $p[i]$  will be the index of the previous element for the optimal subsequence ending in element  $i$ .
structures¶

#### Solution in  $O(n \log n)$  with data structures
Let's go back to the first method. Remember that  $d[i]$  is the value  $d[j] + 1$  with  $j < i$  and  $a[j] < a[i]$ .
hus if we define an additional array  $t[]$  such that
 
$$t[a[i]] = d[i]$$ 

then the problem of computing the value  
$d[i]$  is equivalent to finding the maximum value in a prefix of the array  $t[]$ :
 
$$d[i] = \max\left(t[0 \dots a[i] - 1] + 1\right)$$ 

The problem of finding the maximum of a prefix of an array (which changes) is a standard problem that can be solved by many different data structures. For instance we can use a Segment tree or a Fenwick tree.

This method has obviously some shortcomings: in terms of length and complexity of the implementation this approach will be worse than the method using binary search. In addition if the input numbers  $a[i]$  are especially large, then we would have to use some tricks, like compressing the numbers (i.e. renumber them from  $0$  to  $n-1$ ), or use a dynamic segment tree (only generate the branches of the tree that are important). Otherwise the memory consumption will be too high.
