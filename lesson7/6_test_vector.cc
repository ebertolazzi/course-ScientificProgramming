#include <iostream>
#include <iomanip> // include objects for manipulators

#include <vector> // include objects for manipulators


using namespace std ; // "include" all the items of namespace std

template <typename T>
void
print( char const name[], vector<T> const & v ) {
  typename vector<T>::const_iterator ip = v.begin();
  for ( int i = 0; ip != v.end(); ++ip, ++i )
    cout << name << "[ " << i << "] = " << *ip << '\n';
}

int // this is the tye type of return value
main() {

  vector<double> a, b;

  a.push_back(2);
  a.push_back(1.0);
  a.push_back(4);
  a.push_back(5);
  b = a;
  a.back() = 7;
  a.push_back(1);
  a.push_back(3);
  a.push_back(3);

  a.swap(b);

  vector<double>::iterator ip = a.begin();
  for ( int i = 0; ip != a.end(); ++ip, ++i )
    cout << "a[ " << i << "] = " << *ip << '\n';
  cout << "\n\n";

  print("b",b);

  a[10] = 1;
  a.at(3) = 1;

  cout << a.size() << '\n';

  return 0;
}
