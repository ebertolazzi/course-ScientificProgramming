#include <iostream>

using namespace std ;

/*
  The Barton Nackman permit to use "virtual"
  function without the overhead of the virtual table
  dispatch.
  The trick is based on the "derivation" of the base class
  from its derived class by the use of template.
  This circular definition is perfectly regular due to the
  characteristic of C++ compiler which produce instance 
  of the code only when necessary.
  In particular the base class is instaced only when the derived 
  class is (partially) defined.

 */

/*
 *  Classical method with VIRTUAL method
 *
 *  A base class with some virtual methods
 */

class Base {

public:
  Base() {}
  virtual ~Base() {}
  
  virtual void a_method() = 0;

};

class Derived : public Base {

public:
  Derived() : Base() {}
  virtual ~Derived() {}
  
  virtual void a_method() {
    cout << "a_method, Derived\n";
  }

};

/*
  The Barton Nackman trick
*/

/* define the base class parametrizing it with the 
   derived class */

template <typename DERIVED>
class BaseBN {

public:
  BaseBN() {}
  ~BaseBN() {}
  
  void
  a_method() {
    /*
     * At this point the instruction 
     *   static_cast<DERIVED*>(this)
     * reinterpret the pointer this as a pointer to class DERIVED.
     * This function is defined only when DERIVED is known 
     * and the call of the method a_method() is expanded inline
     * so that a good compiler with a minimum of optimization
     * produce a code without overhead.
     *
     */
    return static_cast<DERIVED*>(this) -> a_method() ;
  }
} ;

/* the derived class inherith from the base class
   which is parametrized with the deribed class.
   It seems a loop, but the compiler can solve it */

class DerivedBN : public BaseBN<DerivedBN> {

public:
  DerivedBN() : BaseBN<DerivedBN>() {}
  ~DerivedBN() {}
  
  void
  a_method() {
    cout << "a_method, DerivedBN\n" ;
  }

} ;

/*
 * In usingBaseClass1 the class Base has a_method virtual so that
 * the a_method() is the one of the derived class.
 */

void
usingBaseClass1( Base & derived ) {
  derived . a_method() ;
} 

/*
 * In usingBaseClass2 the class BaseBN has a_method NON virtual but
 * the a_method() in base class use the template DERIVED to perform
 * the dispatch call to the derived class method.
 */

template <typename DERIVED>
void
usingBaseClass2( BaseBN<DERIVED> & derived ) {
  derived . a_method() ;
} 


int 
main() {
  DerivedBN derived2 ;
  Derived   derived1 ;

  cout << "VIRTUAL CLASS\n" ;
  derived1 . a_method() ;
  usingBaseClass1( derived1 ) ;

  cout << "NON VIRTUAL CLASS, STATIC POLIMORPHIS\n" ;
  derived2 . a_method() ;
  usingBaseClass2( derived2 ) ;
  
}


