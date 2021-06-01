#include <iostream>

using namespace std;

// templated function
template <unsigned N, typename T>
class Working2 {
public:
  static
  unsigned
  factorial()
  { return N * Working2<N-1,T>::factorial(); }
};

// specialized class function
template <typename T>
class Working2<0,T> {
public:
  static
  unsigned
  factorial()
  { return 1; }
};


int // this is the tye type of return value
main() {
  unsigned long F1 = Working2<1,unsigned long>::factorial();
  unsigned long F2 = Working2<2,unsigned long>::factorial();
  unsigned long F3 = Working2<3,unsigned long>::factorial();
  unsigned long F4 = Working2<4,unsigned long>::factorial();
  unsigned long F5 = Working2<5,unsigned long>::factorial();
  unsigned long F6 = Working2<6,unsigned long>::factorial();
  cout << F1 << '\n';
  cout << F2 << '\n';
  cout << F3 << '\n';
  cout << F4 << '\n';
  cout << F5 << '\n';
  cout << F6 << '\n';
  return 0;
}
