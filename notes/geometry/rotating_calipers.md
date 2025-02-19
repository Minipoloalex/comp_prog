## Resources
- 1.1: https://codeforces.com/blog/entry/133763
- 1.2: https://codeforces.com/blog/entry/134034
- 2: https://en.wikipedia.org/wiki/Antipodal_point
## Anti-podal points

**From 2**:
"Two points of a sphere (or n dimensional sphere) are called antipodal or diametrically opposite if they are the endpoints of a diameter, a straight line segment between two points on a sphere and passing through its center."

**From 1.1**:
"In an algorithm that calculates all anti-podal pairs, it would be sufficient to check for every edge its parallel line of support."

## Applications

### Diameter of a convex polygon (aka farthest pair distance)

If the polygon is not convex, just calculate the convex hull first.

#### Complexity
- Find CH: $\mathcal{O}(n\log n)$
- Find anti-podal points and diameter: $ \mathcal{O}(n) $

#### Algorithm
**Observation**: Assuming answer is $dist(p_1, p_2)$, we can prove that $p_1$ and $p_2$ are vertices of the polygon. We can also prove that $(p_1, p_2)$ is an anti-podal pair.

- Calculate all possible anti-podal pairs
- Return the maximum possible distance of all anti-podal pairs

### Minimum width of a polygon
- Find CH
- Handle cases: (edge, vertex), (edge, edge) - similar

Problem (K): https://codeforces.com/gym/101175/attachments

The maximum number of anti-podal pairs is $2 * n$ (tighter bounds can be proven but this is enough).
## Code
Assumption: no three points of the polygon are collinear, meaning that the angle at each vertex of the polygon is smaller than $180 \degree$.

Check [antipodal.cpp](antipodal.cpp).
