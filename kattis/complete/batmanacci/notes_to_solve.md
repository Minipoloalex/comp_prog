fib: 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, ...
diff:-, 0, 1, 1, 2, 3, 5,  8,  13, 21, 34, ...
N: index on fib, check numbers before to see if k is in `n - 1` or `n - 2`
do that recursively: O(N)

0, 1, _2,  _3,     4,  _     5,       _     6,
N, A, NA, ANA, NAANA, ANANAANA, NAANAANANAANA,
