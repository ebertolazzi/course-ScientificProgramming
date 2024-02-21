#pragma once

#ifndef DINING_PHILOSOPHERS_HH
#define DINING_PHILOSOPHERS_HH

#include <iostream>

namespace DiningPhilosophers {

  using integer   = int;
  using real_type = double;

  // opaque class hiding the implementation
  class DiningPhilosophers {
    void * m_data{nullptr}; // implementation is stored in the "true" class
  public:
    DiningPhilosophers();
    ~DiningPhilosophers();

    void
    setup(
      integer         n_philosophers, // how many Philosophers in the simulation
      real_type const sleep_ms[2],    // [0] = min sleep time, [1] = max sleep time
      real_type const eat_time_ms[2]  // [0] = min eating time, [1] = max eating time
    );

    // reset counters for statistics
    void reset();

    // run a simulation
    void run( real_type time_simulation_ms );

    // write statistic on the last execution
    void statistic( std::basic_ostream<char> & s ) const;

  };
}

#endif
