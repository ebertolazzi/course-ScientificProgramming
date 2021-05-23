// avoid double inclusion
#ifndef POLYNOMAS_HPP
#define POLYNOMAS_HPP

// C++ IO
#include <iostream>
// C++ IO on string
#include <sstream>

// for the exception
#include <exception>

// to activate g++ -DDEBUG ....
#ifdef DEBUG
  #define DEBUG_MESSAGE(A) cout << "DEBUG: " << A << '\n'
#else
  #define DEBUG_MESSAGE(A)
#endif

#ifndef ASSERT
  #define DO_ERROR(MSG) { \
    std::ostringstream ost; \
    ost << MSG << '\n'; \
    throw std::runtime_error(ost.str()); \
  }
  #define ASSERT(COND,MSG) if ( !(COND) ) DO_ERROR(MSG)
#endif

namespace Polynoms {

  // parameterize the integer and floating point types
  typedef int    int_type;
  typedef double real_type;

  using std::ostream; // use ostream from std namespace
  using std::cout;    // use cout from std namespace

  class Polynom {

    int_type    n_allocated;
    int_type    degree;
    real_type * coeffs;

    void
    allocate( int_type degree, int_type n ) {
      if ( this->n_allocated < n ) {
        this->free();
        this->n_allocated = n;
        this->coeffs      = new real_type[n];
      }
      this->degree = degree;
    }

    void
    resize( int_type n ) {
      if ( this->n_allocated != n ) {
        ASSERT( n > degree, "Polynom::resize( " << n << ") too few elements") ;
        real_type * saved = this->coeffs;
        this->n_allocated = n;
        this->coeffs      = new real_type[n];
        for ( int_type i = 0; i <= degree; ++i )
          this->coeffs[i] = saved[i];
        delete [] saved;
      }
    }

    void
    reserve( int_type n ) {
      if ( this->n_allocated < n ) {
        real_type * saved = this->coeffs;
        this->n_allocated = n;
        this->coeffs      = new real_type[n];
        for ( int_type i = 0; i <= degree; ++i )
          this->coeffs[i] = saved[i];
        delete [] saved;
      }
    }

    void
    free() {
      if ( this->coeffs != nullptr ) delete [] this->coeffs;
      this->coeffs      = nullptr; // useless
      this->n_allocated = 0;
      this->degree      = -1;
    }

    void
    adjustDegree() {
      while ( this->degree >= 0 && this->coeffs[this->degree] == 0 )
        --this->degree;
    }

    // friend operators
    // res(x) = a(x) + b(x)
    friend
    Polynom
    operator + ( Polynom const & a, Polynom const & b );

    // res(x) = a(x) - b(x)
    friend
    Polynom
    operator - ( Polynom const & a, Polynom const & b );

    // res(x) = a(x) * b(x)
    friend
    Polynom
    operator * ( Polynom const & a, Polynom const & b );

    // p(x) = m(x) * q(x) + r(x)
    friend
    void
    division( Polynom const & p,
              Polynom const & q,
              Polynom       & m,
              Polynom       & r );

    // now operator << can access private data
    friend
    ostream& operator << ( ostream & stream, Polynom const & p );

    // copy constructor block
    Polynom( Polynom const & p )
    : n_allocated(0)
    , degree(-1)
    , coeffs(nullptr)
    {
      DEBUG_MESSAGE("in copy constructor Polynom()");
      *this = p;
      DEBUG_MESSAGE("out copy constructor Polynom()");
    }

  public:

    // default constructor
    Polynom()
    : n_allocated(0)
    , degree(-1)
    , coeffs(nullptr)
    {
      DEBUG_MESSAGE("Polynom()");
    }

    // another constructor
    Polynom( int_type _degree )
    : n_allocated(0)
    , degree(_degree)
    , coeffs(nullptr)
    {
      DEBUG_MESSAGE("Polynom(" << _degree << ")");
      this->setup(_degree);
    }

    ~Polynom() {
      DEBUG_MESSAGE("~Polynom()");
      this->free();
    }

    Polynom &
    clear() {
      this->degree = -1;
      return *this;
    }

    void
    setup( int_type degree ) {
      this->allocate( degree, degree+1 );
      for ( int_type i = 0; i <= degree; ++i )
        this->coeffs[i] = 0;
    }

    // possible operator that can be defined
    // + * - / ^ % ~ > >= < <= == != () [] | & || && -> * << >> += -= /= *=

    Polynom &
    operator << ( real_type cf ) {
      if ( this->degree < 0 ) {
        reserve( 10 );
        this->degree = 0;
      } else {
        if ( this->degree+1 >= this->n_allocated ) reserve( degree+10 );
        ++this->degree;
      }
      this->coeffs[this->degree] = cf;
      return *this;
    }

    real_type normalize();

    Polynom & purge( real_type epsi );

    real_type &
    operator [] ( int_type i ) const
    { return coeffs[i]; }

    real_type &
    operator () ( int_type i ) const {
      ASSERT(
        i >= 0 && i <= degree,
        "Polynom::operator () ( " << i << " ), index out of bound\n"
      )
      return coeffs[i];
    }

    // p(x) = a(x)
    Polynom & operator = ( Polynom const & a ) {
      DEBUG_MESSAGE("in Polynom & operator = Polynom");
      this->allocate( a.degree, a.degree+1 );
      for ( int_type i = 0; i <= this->degree; ++i )
        this->coeffs[i] = a.coeffs[i];
        // (*this)[i] = a[i];
      DEBUG_MESSAGE("out Polynom & operator = Polynom");
      return *this;
    }

    // p(x) = a
    Polynom & operator = ( real_type a ) {
      DEBUG_MESSAGE("in Polynom & operator = scalar");
      this->allocate( 0, 1 );
      this->coeffs[0] = a;
      DEBUG_MESSAGE("out Polynom & operator = scalar");
      return *this;
    }

    // p *= 123; ==> p(x) <- p(x)*123
    Polynom & operator *= ( real_type a ) {
      for ( int_type i = 0; i <= this->degree; ++i )
        this->coeffs[i] *= a;
      return *this;
    }

    // p /= 123; ==> p(x) <- p(x)/123
    Polynom & operator /= ( real_type a ) {
      for ( int_type i = 0; i <= this->degree; ++i )
        this->coeffs[i] /= a;
      return *this;
    }

    // p *= q ; ==> p(x) <- p(x)*q(x)
    Polynom & operator *= ( Polynom const & q ) {
      DEBUG_MESSAGE( "in Polynom & operator *= q" );
      *this = *this * q;
      DEBUG_MESSAGE( "out Polynom & operator *= q" );
      return *this;
    }

    // p += q ; ==> p(x) <- p(x)+q(x)
    Polynom & operator += ( Polynom const & q ) {
      int_type i = 0;
      if ( degree < q.degree ) {
        this->reserve( q.degree + 1 );
        while ( i < degree   ) { coeffs[i] += q.coeffs[i]; ++i; }
        while ( i < q.degree ) { coeffs[i]  = q.coeffs[i]; ++i; }
      } else {
        while ( i < q.degree ) { coeffs[i] += q.coeffs[i]; ++i; }
      }
      return *this;
    }

    // p += q ; ==> p(x) <- p(x)+q(x)
    Polynom & operator -= ( Polynom const & q ) {
      int_type i = 0;
      if ( degree < q.degree ) {
        this->reserve( q.degree + 1 );
        while ( i < degree   ) { coeffs[i] -= q.coeffs[i]; ++i; }
        while ( i < q.degree ) { coeffs[i]  = -q.coeffs[i]; ++i; }
      } else {
        while ( i < q.degree ) { coeffs[i] -= q.coeffs[i]; ++i; }
      }
      return *this;
    }

    // p += q ; ==> p(x) <- p(x)+a
    Polynom & operator += ( real_type a ) {
      if ( degree >= 0 ) coeffs[0] += a;
      else               *this = a;
      return *this;
    }

    // p += q ; ==> p(x) <- p(x)+a
    Polynom & operator -= ( real_type a ) {
      if ( degree >= 0 ) coeffs[0] -= a;
      else               *this = -a;
      return *this;
    }

    // unary -p
    Polynom operator - () {
      Polynom tmp(*this);
      return (tmp *= -1);
    }

    real_type
    eval( real_type x ) const {
      if ( this->degree >= 0 ) {
        int_type  j   = this->degree;
        real_type res = this->coeffs[this->degree];
        while ( --j >= 0 ) res = x * res + this->coeffs[j];
        return res;
      } else {
        return 0;
      }
    }

    // dp(x) = p'(x) where p(x) is the "internal polynomial"
    Polynom
    derivative() const {
      Polynom dp;
      dp.setup( this->degree-1 );
      for ( int_type k = 1; k <= this->degree; ++k )
        dp.coeffs[k-1] = this->coeffs[k]*k;
      return dp;
    }

    friend class Sturm;
  };

  class Sturm {
    int_type  npoly;
    int_type  n_allocated;
    Polynom * sturm;

    void
    allocate( int_type n ) {
      if ( this->n_allocated < n ) {
        this->free();
        this->n_allocated = n;
        this->sturm       = new Polynom[n];
        this->npoly       = 0;
      }
    }

    void
    free() {
      if ( this->sturm != nullptr ) delete [] this->sturm;
      this->sturm       = nullptr; // useless
      this->n_allocated = 0;
      this->npoly       = 0;
    }

  public:

    Sturm()
    : npoly(0)
    , n_allocated(0)
    , sturm(nullptr)
    {}

    Sturm( Polynom const & P )
    : npoly(0)
    , n_allocated(0)
    , sturm(nullptr)
    { this->build(P); }

    ~Sturm()
    { free(); }

    void
    build( Polynom const & P );

    int_type
    sign_changes( real_type x ) const;

    // now operator << can access private data
    friend
    ostream& operator << ( ostream & stream, Sturm const & p );
  };
}

#endif
