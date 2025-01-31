## Code

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
