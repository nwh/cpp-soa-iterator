#include <iostream>
#include <vector>
#include <algorithm>

using std::cout;
using std::endl;
using std::vector;
using std::for_each;

class Points {
 public:

  typedef vector<double>::size_type size_type;

  class iterator {
   public:
    typedef iterator self_type;
    typedef iterator value_type;
    typedef iterator& reference;
    typedef iterator* pointer;
    //typedef std::forward_iterator_tag iterator_category;
    typedef vector<double>::difference_type difference_type;
    iterator(Points& points, Points::size_type index) :
        points_(points), index_(index) { }
    self_type operator++() { self_type i = *this; index_++; return i; }
    self_type operator++(int junk) { index_++; return *this; }
    iterator& operator*() { return *this; }
    iterator* operator->() { return this; }
    bool operator==(const self_type& rhs) { return index_ == rhs.index_; }
    bool operator!=(const self_type& rhs) { return index_ != rhs.index_; }
    double& x() { return points_.get_x()[index_]; }
    double& y() { return points_.get_y()[index_]; }
   private:
    Points& points_;
    Points::size_type index_;
  };

  size_type size() const { return x.size(); }
  void resize(size_type count) {
    x.resize(count);
    y.resize(count);
  }

  vector<double>& get_x() { return x; }
  vector<double>& get_y() { return y; }

  iterator begin() {
    return iterator(*this,0);
  }

  iterator end() {
    return iterator(*this,size());
  }
  
 private:
  vector<double> x;
  vector<double> y;
};

template <typename T>
void print(const T& x) {
  for ( auto& i : x ) {
    cout << i << " ";
  }
  cout << endl;
}

struct Printor {
  void operator()(Points::iterator p) {
    cout << "(" << p.x() << "," << p.y() << ")" << endl;
  }
};

int main() {

  Points p;
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
