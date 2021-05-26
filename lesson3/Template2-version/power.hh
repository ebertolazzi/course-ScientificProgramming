// more efficient if the compiler known
#pragma once

// double inclusion avoiding trick
#ifndef POWER_dot_H
#define POWER_dot_H

#include <iostream>       // std::cerr
#include <typeinfo>       // typeid

// define the prototype of power
template <typename TYPE>
TYPE // generic type
power( TYPE a, int b );

#endif
