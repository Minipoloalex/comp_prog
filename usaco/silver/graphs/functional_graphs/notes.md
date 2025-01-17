**Functional Graphs** (aka **Successor Graphs**) are Directed graphs in which every vertex has exactly one outgoing edge.

You can think of every connected component of a functional graph as a rooted tree with all edges directed toward the root plus an additional edge going out of the root.

## Floyd's Cycle Finding Algorithm
- Algorithm: https://usaco.guide/CPH.pdf#page=166
- Example problem: https://codeforces.com/contest/1137/problem/D

> Floyd's algorithm walks forward in the graph using two pointers a and b.
Both pointers begin at a node x that is the starting node of the graph. Then,
on each turn, the pointer a walks one step forward and the pointer b walks two
steps forward. The process continues until the pointers meet each other:

- Slow pointer: walks k steps
- Fast pointer: walks 2k steps
The length of the cycle (C) divides k.
$$C\ |\ k$$

**Why?**
As an example, assume the pointers are at the first node of the cycle.
Then, by moving them, we can easily tell that it will take C iterations
for the pointers to finish. The fast pointer makes up 1 node at each step.

So, if we add some nodes before the cycle it can be interpreted as if the cycle's
behaviour is still happening (even if the pointers are still not inside it).
When the pointers get to the cycle, it will take some steps for them to meet.
These steps are basically adjustments to the cycle's length
(and depend on the size of the first non-cyclic nodes).

> The first node that belongs
to the cycle can be found by moving the pointer a to node x (starting node) and advancing the
pointers step by step until they meet again.

This also has to do with the way it adjusts to the cycle's length
(depending on the size of the non-cyclic nodes).
The meeting node will be B nodes from the starting node.

- C: cycle size
- B: above
- L: size of non-cyclic nodes
- Z: any constant (0, inf)

Total path size (slow pointer): $$k = L + Z * C + B$$

By advancing some steps until we are on the same node, we will
be doing $C - B + Z * C$ steps (the steps left), finishing in the starting node.

Z is just used if L is bigger than C (e.g. L = 8, C = 4)
