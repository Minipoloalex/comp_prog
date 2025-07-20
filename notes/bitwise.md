## Some bitwise tricks
### Kind of useless
#### Addition with bitwise ops
For addition, count bits from $a \& b$ twice and bits from $a \oplus b$ once.
$$a+b=2\ (a\ \&\ b) + a \oplus b$$

First, exclude places where both bits are 1 $\lnot(a \& b)$. Then, we only include those bits that have at least one 1: $a | b$.
$$a \oplus b = \lnot(a\ \&\ b)\ \&\ (a\ |\ b)$$

### Useful
#### 1. Mod of 2^X
`R % 2^X = R & ((1 << X) - 1)`

## Builtin operations
- `__builtin_popcount()`: Gives the number of 1's in binary representation.
    - e.g. $x = 5 = 101_2 \implies 2$
- `int __builtin_clz()`: Returns the number of leading 0-bits in $X$, starting at the most significant bit position. If $X$ is 0, the result is undefined.
    - e.g. $x = 16 = 000 \dots 01000_2 \implies 27 \text{ (32 bits)}$
    - e.g. $x = 16 = 000 \dots 01000_2 \implies 59 \text{ (64 bits)}$
- `__builtin_ctz()`: returns the count of trailing zeros
    - e.g. $x = 16 = 10000_2 \implies 4$

