/*--------------------------------------------------------------------------*\
 |                                                                          |
 |  Copyright (C) 2010                                                      |
 |                                                                          |
 |         , __                 , __                                        |
 |        /|/  \               /|/  \                                       |
 |         | __/ _   ,_         | __/ _   ,_                                | 
 |         |   \|/  /  |  |   | |   \|/  /  |  |   |                        |
 |         |(__/|__/   |_/ \_/|/|(__/|__/   |_/ \_/|/                       |
 |                           /|                   /|                        |
 |                           \|                   \|                        |
 |                                                                          |
 |      Enrico Bertolazzi                                                   |
 |      Dipartimento di Ingegneria Meccanica e Strutturale                  |
 |      Universita` degli Studi di Trento                                   |
 |      Via Mesiano 77, I-38050 Trento, Italy                               |
 |      email: enrico.bertolazzi@unitn.it                                   |
 |                                                                          |
 |      version: 0.1 04-01-2010                                             |
 |                                                                          |
 \*--------------------------------------------------------------------------*/

#ifndef TIME_METER_HH
#define TIME_METER_HH

bool getTime( long & sec, long & usec ) ;

class TimeMeter {
  
  long sec, usec ;
  
  TimeMeter( TimeMeter const & ) ;
  TimeMeter const & operator = ( TimeMeter const & ) const ;
  
public:
  
  TimeMeter() { start() ; }
  ~TimeMeter() {}

  void   start();
  double seconds();
  double milliseconds();

} ;

#endif
