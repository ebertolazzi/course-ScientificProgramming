/*--------------------------------------------------------------------------*\
 |                                                                          |
 |  Copyright (C) 2021                                                      |
 |                                                                          |
 |         , __                 , __                                        |
 |        /|/  \               /|/  \                                       |
 |         | __/ _   ,_         | __/ _   ,_                                |
 |         |   \|/  /  |  |   | |   \|/  /  |  |   |                        |
 |         |(__/|__/   |_/ \_/|/|(__/|__/   |_/ \_/|/                       |
 |                           /|                   /|                        |
 |                           \|                   \|                        |
 |                                                                          |
 |      E.Bertolazzi, F.Biral, P.Bosetti                                    |
 |      Dipartimento di Ingegneria Industriale                              |
 |      Universita` degli Studi di Trento                                   |
 |      email: enrico.bertolazzi@unitn.it                                   |
 |                                                                          |
\*--------------------------------------------------------------------------*/

/* System includes */

#ifdef __clang__
#pragma clang diagnostic ignored "-Wexit-time-destructors"
#pragma clang diagnostic ignored "-Wc++11-extensions"
#pragma clang diagnostic ignored "-Wunused-parameter"
#pragma clang diagnostic ignored "-Wcovered-switch-default"
#pragma clang diagnostic ignored "-Wglobal-constructors"
#endif

#include <iostream>
#include <fstream>
#include <string>

#include "CLI11.hpp"

int
main( int argc, const char * argv[] ) {

    CLI::App app("pins");

    // add a group of options
    auto grp1 = app.add_option_group("GROUP 1");

    // add a flag
    bool do_activate{false};
    grp1->add_flag("-a,--activate", do_activate,  "ACTIVATE something");
    grp1->add_flag("-b,--activate1", do_activate,  "ACTIVATE something1");
    grp1->add_flag("-c,--activate2", do_activate,  "ACTIVATE something2");
    grp1->add_flag("-d,--activate3", do_activate,  "ACTIVATE something3");
    grp1->add_flag("-e,--activate4", do_activate,  "ACTIVATE something4");

    auto grp2 = app.add_option_group("GROUP 2");

    std::string file{""}, file2{""};
    app.add_option("file", file, "get a file name");
    app.add_option("file2", file2, "get a file name");

    CLI11_PARSE(app, argc, argv);

  return 0;
}

// EOF: test3.cc
