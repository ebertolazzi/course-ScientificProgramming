#pragma once

#ifndef DINING_PHILOSOPHERS_IMPL_HH
#define DINING_PHILOSOPHERS_IMPL_HH

#include "DiningPhilosophers.hh"
#include <vector>
#include <iostream>

namespace DiningPhilosophers {

  class DiningPhilosophers_impl {
    typedef struct {
      integer   id;
      integer   n_eat_task;
      integer   n_sleep_task;
      real_type accumulated_eat_time_ms;
      real_type accumulated_sleep_time_ms;
      real_type accumulated_idle_time_ms;
    } DiningPhilosophers_data;

    std::vector<DiningPhilosophers_data> m_DiningPhilosophers;

    real_type m_min_sleep_ms,    m_max_sleep_ms;
    real_type m_min_eat_time_ms, m_max_eat_time_ms;

  public:
    DiningPhilosophers_impl();
    ~DiningPhilosophers_impl();

    void
    setup(
      int             n_philosophers, // how many Philosophers in the simulation
      real_type const sleep_ms[2],    // [0] = min sleep time, [1] = max sleep time
      real_type const eat_time_ms[2]  // [0] = min eating time, [1] = max eating time
    );

    void reset();

    void run( real_type time_simulation );

    void statistic( std::basic_ostream<char> & s ) const;

  };
}

#endif
