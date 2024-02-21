#include "DiningPhilosophers_impl.hh"

namespace DiningPhilosophers {

  DiningPhilosophers::DiningPhilosophers() {
    // create an instance of DiningPhilosophers_impl and store in the void pointer m_data
    m_data = new DiningPhilosophers_impl();
  }

  DiningPhilosophers::~DiningPhilosophers() {
    // destroyn the instance of DiningPhilosophers_impl stored in the void pointer m_data
    delete static_cast<DiningPhilosophers_impl*>(m_data);
  }

  void
  DiningPhilosophers::setup(
    integer         n_philosophers, // how many Philosophers in the simulation
    real_type const sleep_ms[2],    // [0] = min sleep time, [1] = max sleep time
    real_type const eat_time_ms[2]  // [0] = min eating time, [1] = max eating time
  ) {
    DiningPhilosophers_impl * THIS{static_cast<DiningPhilosophers_impl*>(m_data)};
    THIS->setup( n_philosophers, sleep_ms, eat_time_ms );
  }

  void
  DiningPhilosophers::reset() {
    DiningPhilosophers_impl * THIS{static_cast<DiningPhilosophers_impl*>(m_data)};
    THIS->reset();
  }

  void
  DiningPhilosophers::run( real_type time_simulation_ms ) {
    DiningPhilosophers_impl * THIS{static_cast<DiningPhilosophers_impl*>(m_data)};
    THIS->run(time_simulation_ms);
  }

  void
  DiningPhilosophers::statistic( std::basic_ostream<char> & s ) const {
    DiningPhilosophers_impl * THIS{static_cast<DiningPhilosophers_impl*>(m_data)};
    THIS->statistic(s);
  }
}
