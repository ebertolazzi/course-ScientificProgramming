#include <iostream>

using namespace std;

// templated function
template <unsigned N, typename T>
T
dot( T const a[], T const b[] ) {
  cout << "Expand Generic N = " << N << '\n';
  T res(0);
  for ( unsigned i = 0; i < N; ++i )
    res += a[i]*b[i];
  return res;
}

// templated function
template <unsigned N, typename T>
class Working {
public:
  static
  T
  dot( T const a[], T const b[] ) {
    cout << "Working::dot N = " << N << '\n';
    T res(0);
    for ( unsigned i = 0; i < N; ++i )
      res += a[i]*b[i];
    return res;
  }
};

// specialized class function
template <typename T>
class Working<1,T> {
public:
  static
  T
  dot( T const a[], T const b[] ) {
    cout << "Working::dot N = 1 specialized\n";
    return a[0]*b[0];
  }
};

// specialized class function
template <typename T>
class Working<2,T> {
public:
  static
  T
  dot( T const a[], T const b[] ) {
    cout << "Working::dot N = 2 specialized\n";
    return a[0]*b[0]+a[1]*b[1];
  }
};

// templated function
template <unsigned N, typename T>
class Working2 {
public:
  static
  T
  dot( T const a[], T const b[] ) {
    cout << "Working2::dot N = " << N << '\n';
    return a[0]*b[0]+Working2<N-1,T>::dot(a+1,b+1);
  }

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
  T
  dot( T const a[], T const b[] ) {
    cout << "Working2::dot N = 0 specialized\n";
    return 0;
  }

  static
  unsigned
  factorial()
  { return 1; }
};


int // this is the tye type of return value
main() {
  double a[4] = {1,2,3,4};
  double b[4] = {4,3,2,1};

  double res = dot<4>(a,b);
  cout << "dot<4> = " << res << '\n';

  double res1 = Working<1,double>::dot(a,b);
  cout << "W::<1>::dot = " << res1 << '\n';

  double res2 = Working<2,double>::dot(a,b);
  cout << "W::<2>::dot = " << res2 << '\n';

  double res4 = Working<4,double>::dot(a,b);
  cout << "W::<4>::dot = " << res4 << '\n';

  double res4b = Working2<4,double>::dot(a,b);
  cout << "W2::<4>::dot = " << res4b << '\n';

  unsigned long F = Working2<10,unsigned long>::factorial();

  cout << "FACT 10 = " << F << '\n';
  return 0; // return is a statement for returning value to the caller
}
