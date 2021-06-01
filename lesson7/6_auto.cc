/*

 Example using auto

*/

#include <iostream>
#include <vector>

using namespace std;

template <typename T1, typename T2>
auto
maxvalue( T1 a, T2 b ) -> decltype(a+b)
{ return a>b? a:b; } 

int
main(){
  double a = 1;
  double b = 2;

  auto c = a+b; // the compile infer auto = double

  /*
    typedef vector< double > vec;

	vector< double >::value_type --> double
	vector< double >::pointer --> double *

	vec::value_type --> double
	vec::pointer --> double *

  */

  vector< vector< double > > mat;

  mat.resize(3);
  mat[0].resize(2); mat[0][0] = 1; mat[0][1] = 2;
  mat[1].resize(2); mat[1][0] = 3; mat[1][1] = 4;
  mat[2].resize(2); mat[2][0] = 5; mat[2][1] = 6;

  for ( vector< vector< double > >::const_iterator irow = mat.begin();
        irow != mat.end(); ++irow ) {
    // irow = mat[0], mat[1], mat[2]
    for ( vector< double >::const_iterator icol = irow->begin();
        icol != irow->end(); ++icol ) {
      cout << "elem = " << *icol << '\n';
	}
  }

  // same code using auto

  for ( auto irow = mat.begin(); irow != mat.end(); ++irow ) {
    // irow = mat[0], mat[1], mat[2]
    for ( auto icol = irow->begin();
        icol != irow->end(); ++icol ) {
      cout << "elem = " << *icol << '\n';
	}
  }

  /*
    for ( auto & row : mat ) {

	}

	for ( auto irow = mat.begin(); irow != mat.end(); ++irow ) {
      auto & row = *irow;

	}

  */

  cout << "\n\n\n";

  for ( auto & row : mat ) {
    for ( auto & col : row ) {
      ++col;
	}
  }

  for ( auto & row : mat ) {
    for ( auto & col : row ) {
      cout << "elem = " << col << '\n';
	}
  }

  auto mm = maxvalue( 1, 2.5 );
  cout << "mm = " << mm << '\n';

  auto mm1 = maxvalue( 2.5, 1 );
  cout << "mm1 = " << mm1 << '\n';

  return 0;
}