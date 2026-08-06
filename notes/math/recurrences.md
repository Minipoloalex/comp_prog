## Recurrences
These can typically be proved by induction. Example problem with a proof in editorial: https://codeforces.com/problemset/problem/2232/D. Note how these proofs can be used for recurrences alone instead of applied to specific problems.


### Exponentital

- $t(n) = 2^{n}-1$

Reference: https://www.wolframalpha.com/input?i=t%28n%29+%3D+t%28n-1%29+%2B+t%28n-1%29+%2B+1%3B+t%281%29+%3D+1


$$
\begin{cases}
    t(1) = 1\\
    t(n) = t(n-1) + t(n-1) + 1
\end{cases}
$$

- $t(n) = 2^{n-1}$

Reference: https://www.wolframalpha.com/input?i=t%28n%29+%3D+t%28n-1%29+%2B+t%28n-1%29%3B+t%281%29+%3D+1

$$
\begin{cases}
    t(1) = 1\\
    t(n) = t(n-1) + t(n-1)
\end{cases}
$$



