## Mo's Algorithm
- https://usaco.guide/plat/sqrt#mos-algorithm
- https://www.hackerearth.com/practice/notes/mos-algorithm/

Time complexity: $\mathcal{O}((N + Q) \cdot \sqrt{N} \cdot F)$, where $\mathcal{O}(F)$ is the cost of an operation (changing one index in our interval).

This technique is applicable when:
- The array is not changed by queries: **static array**
- All queries are known beforehand: **offline**
- If we know `Func([L, R])`, then we can compute `Func([L + 1, R])`, `Func([L - 1, R])`, `Func([L, R + 1])` and `Func([L, R - 1])`, each in $O(F)$ time.

### Algorithm outline
Check https://www.hackerearth.com/practice/notes/mos-algorithm/ for this explanation, and https://usaco.guide/plat/sqrt#mos-algorithm for an example implementation.

Denote: $\mathrm{BLOCK\_SIZE} = \sqrt{N}.$

Rearrange all queries into **Mo's order**, defined as follows: a query $[L_1, R_1]$ comes before $[L_2, R_2]$ if and only if:
1. The block (index) of the left endpoint is smaller: $$\big\lfloor \tfrac{L_1}{\mathrm{BLOCK\_SIZE}} \big\rfloor < \big\lfloor \tfrac{L_2}{\mathrm{BLOCK\_SIZE}} \big\rfloor,$$
2. Or the blocks are the same, but the right endpoint is smaller: $$\big\lfloor \tfrac{L_1}{\mathrm{BLOCK\_SIZE}} \big\rfloor = \big\lfloor \tfrac{L_2}{\mathrm{BLOCK\_SIZE}} \big\rfloor \quad\text{and}\quad R_1 < R_2.$$

Maintain a current segment $[\mathtt{mo\_left}, \mathtt{mo\_right}]$ **(inclusive)** for which you know $\mathrm{Func}([\mathtt{mo\_left}, \mathtt{mo\_right}])$. Initially, this segment is empty:  
$$
\mathtt{mo\_left} = 0,
\mathtt{mo\_right} = -1.
$$

**Answer all queries in Mo’s order**. To answer the next query $[L, R]$, perform:  
1. while $\mathtt{mo\_right} < R$, extend to $[\mathtt{mo\_left},\,\mathtt{mo\_right}+1]$;  
2. while $\mathtt{mo\_right} > R$, shrink to $[\mathtt{mo\_left},\,\mathtt{mo\_right}-1]$;  
3. while $\mathtt{mo\_left} > L$, extend to $[\mathtt{mo\_left}-1,\,\mathtt{mo\_right}]$;  
4. while $\mathtt{mo\_left} < L$, shrink to $[\mathtt{mo\_left}+1,\,\mathtt{mo\_right}]$.

Each extension or deletion takes $O(F)$ time, so moving from one query’s segment $[\mathtt{mo\_left}, \mathtt{mo\_right}]$ to $[L, R]$ costs:
$$
O\bigl((|\mathtt{mo\_left}-L| + |\mathtt{mo\_right}-R|)\times F\bigr).
$$

After these steps, you will have $\mathtt{mo\_left}=L$ and $\mathtt{mo\_right}=R$, thus computing $\mathrm{Func}([L,R])$.


### Usage and Applicability
Rare, but important to know if it appears (~unsolvable otherwise).

### Time Complexity and Intuition
Here, we assume $\mathcal{O}(N) = \mathcal{O}(Q)$.
This deduction comes from the division of the array in blocks, which have a size of $\mathcal{O}(\sqrt{N})$.

- There can be $n$ different endpoints, and each left endpoint will move at most $\mathcal{O}(\sqrt{N})$ (amortized, since there may be a few that move like $\mathcal{O}(N)$, but overall it's $\mathcal{O}(\sqrt{N})$). This means that **the left endpoint moves $\mathcal{O}(N \cdot \sqrt{N})$**.
- For each of the blocks, the right pointer may move up to $\mathcal{O}(N)$ times, since the right endpoints of the queries are sorted for a specific block. After each block it likely moves back, which is also just $\mathcal{O}(N)$. Since there are $\mathcal{O}(\sqrt{N})$ blocks, the right endpoint moves $\mathcal{O}(N \cdot \sqrt{N})$.

Each movement costs $\mathcal{O}(F)$, so the complexity is: $\mathcal{O}((N + Q) \cdot \sqrt{N} \cdot F)$.
