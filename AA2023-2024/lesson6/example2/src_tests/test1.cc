
#include "DiningPhilosophers.hh"

int
main() {

  DiningPhilosophers::DiningPhilosophers DP;
  DiningPhilosophers::integer   n_philosophers{5};
  DiningPhilosophers::real_type sleep_ms[2]{1,5};
  DiningPhilosophers::real_type eat_time_ms[2]{1,5};
  DiningPhilosophers::real_type time_simulation_ms{5000};

  DP.setup( n_philosophers, sleep_ms, eat_time_ms );
  //eset();
  DP.run( time_simulation_ms );
  DP.statistic( std::cout );
  return 0;
}
