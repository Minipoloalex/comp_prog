Visualise geometry stuff:
https://geogebra.org/calculator

## Comparing doubles
$$ |a − b| < \epsilon$$

## Point distance from a line
Taken from https://usaco.guide/CPH.pdf#page=275

![alt text](image.png)

## Area - Shoelace formula
Root at point (0, 0) and calculate cross product of every pair of verticies: $\sum_{i=0}^{N-1} (p_{i}\times p_{(i + 1) \% N})$.


## Pick's Theorem
$$ A = a + \frac{b}{2} - 1$$
where:
- $a$ is the number of integer points inside the polygon
- $b$ is the number of integer points on the boundary of the polygon

$b$ can be calculated using GCD of each segments X and Y length. For example:

![alt text](image-1.png)

Segment length (6, 2): GCD = 2, so there are 2 smaller segments with points on integer coordinates.

## Distances
![alt text](image-2.png)

### Maximum manhattan distance
$$(x', y') = (x + y, y - x)$$
$$|x_1 - x_2| + |y_1 - y_2| = max(|x'_1 - x'_2|, |y'_1 - y'_2|)

