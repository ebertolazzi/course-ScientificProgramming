// more efficient if the compiler known
#pragma once

// double inclusion avoiding trick
#ifndef POWER_dot_H
#define POWER_dot_H

// define the prototype of power

extern double power( double a, int b );
extern float power( float a, int b );

extern int mult_count;

#endif
