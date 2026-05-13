#include "utils.h"
int factorial(int n) { return n <= 1 ? 1 : n * factorial(n-1); }
int fibonacci(int n) {
    if (n <= 1) return n;
    return fibonacci(n-1) + fibonacci(n-2);
}
