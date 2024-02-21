#include "DiningPhilosophers_impl.hh"

namespace DiningPhilosophers {

  DiningPhilosophers_impl::DiningPhilosophers_impl() {
    std::cerr << "PASS DiningPhilosophers_impl constructor\n";
  }

  DiningPhilosophers_impl::~DiningPhilosophers_impl() {
    std::cerr << "PASS DiningPhilosophers_impl destructor\n";
  }

  void
  DiningPhilosophers_impl::setup(
    integer         n_philosophers, // how many Philosophers in the simulation
    real_type const sleep_ms[2],    // [0] = min sleep time, [1] = max sleep time
    real_type const eat_time_ms[2]  // [0] = min eating time, [1] = max eating time
  ) {
    m_DiningPhilosophers.resize(n_philosophers);
    m_min_sleep_ms    = sleep_ms[0];
    m_max_sleep_ms    = sleep_ms[1];
    m_min_eat_time_ms = eat_time_ms[0];
    m_max_eat_time_ms = eat_time_ms[1];
    integer id{0};
    for ( auto & e : m_DiningPhilosophers ) {
      e.id                        = id++;
      e.n_eat_task                = 0;
      e.n_sleep_task              = 0;
      e.accumulated_eat_time_ms   = 0;
      e.accumulated_sleep_time_ms = 0;
      e.accumulated_idle_time_ms  = 0;
    }
    std::cerr << "PASS DiningPhilosophers_impl setup\n";
  }

  void
  DiningPhilosophers_impl::reset() {
    std::cerr << "PASS DiningPhilosophers_impl reset\n";
  }

  void
  DiningPhilosophers_impl::run( real_type time_simulation ) {
    std::cerr << "PASS DiningPhilosophers_impl run\n";
  }

  void
  DiningPhilosophers_impl::statistic( std::basic_ostream<char> & s ) const {
    for ( auto const & e : m_DiningPhilosophers ) {
      s << "\nid                        = " << e.id
        << "\nn_eat_task                = " << e.n_eat_task
        << "\nn_sleep_task              = " << e.n_sleep_task
        << "\naccumulated_eat_time_ms   = " << e.accumulated_eat_time_ms
        << "\naccumulated_sleep_time_ms = " << e.accumulated_sleep_time_ms
        << "\naccumulated_idle_time_ms  = " << e.accumulated_idle_time_ms
        << "\n";
    }
  }
}
