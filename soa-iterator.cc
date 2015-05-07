#include <iostream>
#include <vector>
#include <algorithm>

using std::cout;
using std::endl;
using std::vector;
using std::for_each;

struct element {
    //TODO: add all the relevant constructors.
    double& x() { return points_.get_x()[index_]; }
    double& y() { return points_.get_y()[index_]; }
    Points* points_ = nullptr;
    //TODO: perhaps make this private and give iterator friendship relations
    std::size_t index_ = 0; 
}; //end struct element

class Points {
 typedef std::vector< double> Vector;
 public:

  typedef typename Vector::size_type size_type;

  class iterator {
   public:
    //This can be a bit messy, strongly suggest using the boost::iterator_facade interface
    //operator* returning the iterator is akward imho. Its not natural to write ********x in code and 
    //have it do what your code did..
    typedef element value_type;
    typedef element& reference;
    typedef element* pointer;

    //typedef std::forward_iterator_tag iterator_category;
    typedef vector<double>::difference_type difference_type;
    iterator(Points& points, Points::size_type index) : elt_(points, index){ }
    //good
    value_type operator++() { self_type i = *this; index_++; return i; }
    reference operator++(int junk) { index_++; return *this; }
    //operator--?
    iterator& operator*() { return elt; }
    //This should not be necessary, the language implements this for you..
    //iterator* operator->() { return this; }
    bool operator==(const self_type& rhs) { return elt == rhs.elt; }
    bool operator!=(const self_type& rhs) { return elt != rhs.elt; }
   private:
    element elt;
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
