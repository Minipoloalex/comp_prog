## Common Edge Cases
### Points
- Collinear points
- Coincident points

### Segments
For example, in segment intersection.
- Parallel segments
- Collinear segments (intersection may be segment)
- Intersection in one of the points
- Intersection between more than 2 segments

### Circles
- Circle completely inside another
- Circles same center

### Sweep Line
- Events in same point (same and/or different events)

### Angular Sweep Line
- https://dmoj.ca/problem/ioi03p6

- Entrance angle larger than the exit angle: we can handle it manually or by doubling the array to handle wrap-around

### Anti-podal points
- Edges with collinear points: likely should remove the collinear points
- Concave polygons: just make a convex polygon with CH
- Consider edge-vertex and edge-edge
