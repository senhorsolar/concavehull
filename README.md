# concavehull
Finds the concave hull around a set of 2D points by leveraging the Delaunay triangulation.

This is a very fast implementation based on a paper from M. Duckham, et al [1], and uses the Delaunay triangulation implementation from [https://github.com/delfrrr/delaunator-cpp](https://github.com/delfrrr/delaunator-cpp).

The algorithm begins by finding the Delaunay triagulation of a set of 2D points, initializes the hull to the convex hull, then iteratively adds points to the hull until some stopping condition is met. The iterative process looks at the largest triangle edges on the outside hull, and if the other triangle point is not also on the hull, proceeds to remove this edge and add the two other edges connected to this point.

# References
[1] M. Duckham, L. Kulik, M. F. Worboys, and A. Galton. Efficient generation of simple polygons for characterizing the shape of a set of points in the plane. Pattern Recognition, 41:3224–3236, 2008. 
