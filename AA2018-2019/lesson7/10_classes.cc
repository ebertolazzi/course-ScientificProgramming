/*
  example of use exception
*/

#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>

#include <string>
#include <exception>

using namespace std;

class BaseClass {
protected:
  string _name;
  double data1;
  double data2;
  double data3;

public:

  BaseClass( string const & n )
  : _name(n)
  , data1(1)
  , data2(2)
  , data3(3)
  { cout << "BaseClass( name = " << _name << " )\n"; }

  BaseClass( string const & n, double v )
  : _name(n)
  , data1(v)
  , data2(v)
  , data3(v)
  { cout << "BaseClass( name = " << _name << " v = " << v << " )\n"; }

  ~BaseClass()
  { cout << "~BaseClass, name = " << _name << "\n"; }

  double
  I_am_a_method() {
    cout << "BaseClass::I_am_a_method()\n";
    return data1;
  }

  virtual
  double
  I_am_a_method2() {
    cout << "BaseClass::I_am_a_method2()\n";
    return data1;
  }

};

class DerivedClass : public BaseClass {
public:

  DerivedClass( string const & n )
  : BaseClass(n)
  { cout << "DerivedClass( name = " << _name << " )\n"; }

  DerivedClass( string const & n, double v )
  : BaseClass(n,v)
  { cout << "DerivedClass( name = " << _name << " v = " << v << " )\n"; }

  double
  I_am_a_method() {
    cout << "DerivedClass::I_am_a_method()\n";
    return data1;
  }

  virtual
  double
  I_am_a_method2() {
    cout << "DerivedClass::I_am_a_method2()\n";
    return data1;
  }

};

int
main() {
  cout << "Enter in MAIN\n";
  BaseClass    BC1("BC1"), BC2("BC2",3);
  DerivedClass DC1("DC1");

  BaseClass & TMP = DC1;

  double tmp1 = BC1.I_am_a_method() ;
  cout << "BC1.I_am_a_method() = " << tmp1 << '\n';
  double tmp2 = DC1.I_am_a_method() ;
  cout << "DC1.I_am_a_method() = " << tmp2 << '\n';
  double tmp2b = DC1.I_am_a_method2() ;
  cout << "DC1.I_am_a_method2() = " << tmp2b << '\n';
  double tmp3 = TMP.I_am_a_method() ;
  cout << "TMP.I_am_a_method() = " << tmp3 << '\n';
  double tmp3b = TMP.I_am_a_method2() ;
  cout << "TMP.I_am_a_method2() = " << tmp3b << '\n';

  cout << "Exit from MAIN\n";
  return 0;
}

