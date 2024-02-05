/*
example of ineheritance in C++11

*/

#include <iostream>
#include <string>

using namespace std;

class stupid_base {
  string const m_name; // name must be initialized with a constructor
  int m_a{1}; // define and initialize using {}
public:
  stupid_base( string const & name )
  : m_name( name )
  {}

  // const --> the class is not modified by the call of the method
  virtual int stupid_method() const { return m_a; }
  virtual int another_stupid_method() const { return m_a; }
};

class stupid_derived : public stupid_base {
  int m_b{2}; // define and initialize using {}
  int m_c;
public:
  stupid_derived( string const & name )
  : stupid_base( name )
  , m_c(3)
  {}

  // const --> the class is not modified by the call of the method
  int stupid_method() const override { return m_b; }
  // override tell the compiler you are overriding a virtual method
  int another_stupid_method() const final { return m_c; }
  // if uncommented --> error
  // int another_stupid_method2() const override { return m_c; }
};

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wall"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wall"

class stupid_derived2 : public stupid_derived {
  int m_d{4}; // define and initialize using {}
  int m_e;
public:
  stupid_derived2( string const & name )
  : stupid_derived( name )
  , m_e(1)
  {}

  // const --> the class is not modified by the call of the method
  int stupid_method() const override { return m_d; }
  // override tell the compiler you are overriding a virtual method
  // int another_stupid_method() const override { return m_e; }
  // if uncommented --> error
  // int another_stupid_method2() const override { return m_c; }
};

#pragma GCC diagnostic pop
#pragma clang diagnostic pop

int
main(){
  stupid_base     a("a");
  stupid_derived  b("b");
  stupid_derived2 c("c");

  stupid_base * p_class = &a;
  cout << "[a] stupid method: " << p_class->stupid_method() << "\n";
  cout << "[a] another stupid method: " << p_class->another_stupid_method() << "\n";

  p_class = &b;
  cout << "[b] stupid method: " << p_class->stupid_method() << "\n";
  cout << "[b] another stupid method: " << p_class->another_stupid_method() << "\n";

  p_class = &c;
  cout << "[c] stupid method: " << p_class->stupid_method() << "\n";
  cout << "[c] another stupid method: " << p_class->another_stupid_method() << "\n";

  cout << "All done Folks!!\n";

  return 0;
}

