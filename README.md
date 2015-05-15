# cpp-soa-iterator

Experiment with a c++ struct-of-array iterator.

## Motivation

The struct-of-array data pattern is commonly used in CUDA code to allow for
coalesced memory access. The `vector` container in C++ STL and `device_vector`
container in `thrust` may be easily used to implement an array-of-structs data
pattern. For example, consider a vector of 2D points. This could be implemented
with the struct:

```c++
struct Point {
  double x;
  double y;
};
```

and an STL `vector`:

```c++
std::vector<Point> p(10);
p[0].x = 1.0;
p[1].y = 1.0;
```

This data pattern does not allow for the most efficient coalesced memory access
if, say, only the `x` coordinate is desired. In practice, the data structures of
interest have many more fields (more than 10 fields for data needed in a
particle physics simulation).

We desire an efficient container to hold data in the struct-of-array format and
easily accessed in `thrust` algorithm calls (such as `thrust::for_each`). This
repository has a basic example that works with `std::for_each`.  The main
container is called `PointBuffer`, which has a `std::vector<double>` for the `x`
and `y` coordinates as private members.  We define a `PointElement` type that
holds a reference to the `PointBuffer` and an index. `PointElement` has member
functions to access the `x` and `y` data at the index. We also define a
`PointIterator` in order to pass a range to an algorithm.

Example `PointBuffer` usage:

```c++
PointBuffer p;
p.resize(10);

// perform some initialization on p

// get an iterator
PointIterator pi = p.begin();

// get a reference to an element
PointElement& pe = *pi;

// access the element
pe.x() = 5.0;
pe.y() = 6.0;

// print
std::cout << "(" << p.x() << "," << p.y() << ")" << std::endl;
```

## A request

We would appreciate any suggestions on implementing something like this for use
in `thrust` and any potential performance concerns.

## References

- https://gist.github.com/jeetsukumaran/307264
- http://www.cs.northwestern.edu/~riesbeck/programming/c++/stl-iterators.html
- http://www.cs.northwestern.edu/~riesbeck/programming/c++/stl-iterator-define.html
- http://stackoverflow.com/questions/4421706/operator-overloading
