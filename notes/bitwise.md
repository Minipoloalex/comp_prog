For addition, count bits from $a \& b$ twice and bits from $a \oplus b$ once.
$$a+b=2\ (a\ \&\ b) + a \oplus b$$

First, exclude places where both bits are 1 $\lnot(a \& b)$. Then, we only include those bits that have at least one 1: $a | b$.
$$a \oplus b = \lnot(a\ \&\ b)\ \&\ (a\ |\ b)$$


## Builtin operations
- `__builtin_popcount()`: Gives the number of 1's in binary representation
