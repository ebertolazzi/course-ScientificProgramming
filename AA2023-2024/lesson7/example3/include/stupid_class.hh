#pragma once

#ifndef STUPID_CLASS_HH
#define STUPID_CLASS_HH

#include <string>

class stupid_class {
  std::string m_status{"zero"};
public:
  stupid_class() {}
  std::string print_status() const { return m_status; }
  void change_status( std::string const & new_status ) { m_status = new_status; }
};

#endif
