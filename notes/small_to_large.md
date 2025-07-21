## Proof of complexity
A value is only copied $\mathcal{O}(\log{N})$ times. Basically, we can ensure it because each time a value is copied, its data structure (e.g. map) doubles in size. In fact, assume a value $a$ is inside a data structure of size $x$ (or a data structure that refers to $x$ elements, meaning with an upper bound of size $x$). Then, if we need to copy it, it will be copied to a data structure of a larger size. This means that the final structure would have at least $2 \cdot x$ size, which grows exponentially.

In summary, a value $a$ that is copied $x$ times will be inside a data structure of size at least $2^x$ (or, in other words, a data structure that refers to at least $2^x$ elements).

See time complexity for common data structures here: https://usaco.guide/plat/merging#generalizing

## Usage
- Tree Offline Algorithms, since we swap the maps when merging for the parent, invalidating the children maps.

