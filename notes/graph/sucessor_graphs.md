From https://usaco.guide/problems/cses-1160-planets-queries-ii/solution.

All functional/successor graphs are of this general form, possibly with multiple connected components with this shape. The loop can also contain just a single node (self-loop).

![alt text](images/image.png)

These successor graphs can be broken down into some "components", circled in red (see above link for explanation).

## Cycle Finding Code

```cpp
a = succ(x);
b = succ(succ(x));
while (a != b) {
    a = succ(a);
    b = succ(succ(b));
}

a = x;   // First overall node
while (a != b) {
    a = succ(a);
    b = succ(b);
}
first = a;  // First node of cycle


b = succ(a);
length = 1; // Length of cycle
while (a != b) {
    b = succ(b);
    length++;
}
```
