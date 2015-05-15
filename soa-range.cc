#include <iostream>
#include <vector>
#include <algorithm>

#include <thrust/iterator/zip_iterator.h>

// Printer helpers for library types

std::ostream& operator<<(std::ostream& s, const thrust::tuple<double,double>& p) {
  std::cout << "(" << thrust::get<0>(p) << ", " << thrust::get<1>(p) << ")";
}

// define the container
class PointBuffer {

 public:

  typedef thrust::tuple<double,double> value_type;
  typedef std::vector<double>::size_type size_type;

  typedef typename std::vector<double>::iterator c_iterator;
  typedef thrust::tuple<c_iterator, c_iterator> iter_pair;
  typedef thrust::zip_iterator<iter_pair> iterator;

  size_type size() const { return x.size(); }

  void resize(size_type count) {
    x.resize(count);
    y.resize(count);
  }

  iterator begin() { return iterator(iter_pair(x.begin(), y.begin())); }
  iterator end()   { return iterator(iter_pair(x.end(),   y.end()  )); }

  c_iterator x_begin() { return x.begin(); }
  c_iterator x_end() { return x.end(); }

  c_iterator y_begin() { return y.begin(); }
  c_iterator y_end() { return y.end(); }

 private:
  std::vector<double> x;
  std::vector<double> y;
};

// Range access

struct xrange {
  xrange(PointBuffer& _pb) : pb(_pb) {}
  typename PointBuffer::c_iterator begin() { return pb.x_begin(); }
  typename PointBuffer::c_iterator end()   { return pb.x_end();   }
  PointBuffer& pb;
};

struct yrange {
  yrange(PointBuffer& _pb) : pb(_pb) {}
  typename PointBuffer::c_iterator begin() { return pb.y_begin(); }
  typename PointBuffer::c_iterator end()   { return pb.y_end();   }
  PointBuffer& pb;
};

// Printers

struct Printor {
  template <typename T>
  void operator()(const T& p) {
    std::cout << p << std::endl;
  }
};

template <typename Range>
void print(Range&& r) {
  for (const auto& i : r)
    std::cout << i << std::endl;
}

int main() {
  PointBuffer p;
  p.resize(3);
  double c = 0.0;

  for (auto& x : xrange(p))
    x = c++;
  for (auto& y : yrange(p))
    y = c++;

  print(xrange(p));
  print(yrange(p));
  print(p);
  std::cout << std::endl;

  std::for_each(p.begin(), p.end(), Printor());

  std::cout << "--- end of soa-iterator ---" << std::endl;

  return 0;
}
