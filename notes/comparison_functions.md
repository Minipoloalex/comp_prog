## Comparators

In C++, its comparators must obey a set of behaviors. Let's call this comparator compare, and the objects it compares x and y.

- If $x < y$, return true.
- If $x \ge y$, return false.
- **Antisymmetry**: If compare(x, y) is true, then compare(y, x) must be false.
- **Transitivity**: If compare(x, y) is true and compare(y, z) is true, then compare(x, z) must be true.
