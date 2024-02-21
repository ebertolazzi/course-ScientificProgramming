#pragma once

// avoid double inclusion
#ifndef LS_HH
#define LS_HH

#include <iostream>

namespace LS {

  using real_type = double;
  using integer   = int;

  // solve the least square problem using classical algorithm
  class LS {
    // stored problem
    void * m_opaque_solver{nullptr};
  public:
    LS() {}
    bool solve( integer N, real_type const x[], real_type const y[], real_type & a, real_type & b );
  };

  // solve the least square problem using QR decomposition
  class LS_QR {
    // stored problem
    void * m_opaque_solver{nullptr};
  public:
    LS_QR() {}
    bool solve( integer N, real_type const x[], real_type const y[], real_type & a, real_type & b );
  };

}

#endif