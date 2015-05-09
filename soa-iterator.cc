#include <iostream>
#include <vector>
#include <algorithm>

using std::cout;
using std::endl;
using std::vector;
using std::for_each;

// forward declare element and iterator types
class PointElement;
class PointIterator;

// define the container
class PointBuffer {

  friend class PointElement;
  friend class PointIterator;

 public:
  
  typedef vector<double>::size_type size_type;
  typedef PointIterator iterator;
  typedef PointElement value_type;
  
  size_type size() const { return x.size(); }
  void resize(size_type count) {
    x.resize(count);
    y.resize(count);
  }

  vector<double>& get_x() { return x; }
  vector<double>& get_y() { return y; }

  iterator begin();
  iterator end();
  
 private:
  vector<double> x;
  vector<double> y;
};

// define element type
class PointElement {
  friend class PointIterator;
 public:
  PointElement(PointBuffer& point_buffer, PointBuffer::size_type index)
      : point_buffer_(point_buffer), index_(index) {}
  double& x() { return point_buffer_.x[index_]; }
  double& y() { return point_buffer_.y[index_]; }
 private:
  PointBuffer& point_buffer_;
  PointBuffer::size_type index_;
};

// define the iterator type
class PointIterator {
 public:
  typedef PointIterator self_type;
  typedef PointElement value_type;
  typedef PointElement& reference;
  typedef PointElement* pointer;
  //typedef std::forward_iterator_tag iterator_category;
  typedef vector<double>::difference_type difference_type;
  PointIterator(PointBuffer& point_buffer, PointBuffer::size_type index) :
      point_element_(point_buffer,index) { }
  self_type operator++() {
    self_type i = *this;
    point_element_.index_++;
    return i;
  }
  self_type operator++(int junk) {
    point_element_.index_++;
    return *this;
  }
  reference operator*() { return point_element_; }
  //pointer operator->() { return this; }
  bool operator==(const self_type& rhs) {
    return point_element_.index_ == rhs.point_element_.index_;
  }
  bool operator!=(const self_type& rhs) {
    return point_element_.index_ != rhs.point_element_.index_;
  }
 private:
  PointElement point_element_;
};

PointBuffer::iterator PointBuffer::begin() {
  return PointBuffer::iterator(*this,0);
}

PointBuffer::iterator PointBuffer::end() {
  return PointBuffer::iterator(*this,size());
}

template <typename T>
void print(const T& x) {
  for ( auto& i : x ) {
    cout << i << " ";
  }
  cout << endl;
}

struct Printor {
  void operator()(PointBuffer::value_type p) {
    cout << "(" << p.x() << "," << p.y() << ")" << endl;
  }
};

int main() {

  PointBuffer p;
  p.resize(3);
  double c = 0.0;
  for ( auto& x : p.get_x() ) {
    x = c++;
  }
  for ( auto& y : p.get_y() ) {
    y = c++;
  }

  print(p.get_x());
  print(p.get_y());

  for ( auto& i : p ) {
    cout << "(" << i.x() << "," << i.y() << ") ";
  }
  cout << endl;

  for_each(p.begin(), p.end(), Printor());
  
  cout << "--- end of soa-iterator ---" << endl;
  
  return 0;
}
