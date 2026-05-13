#ifndef MYLIB_H
#define MYLIB_H

#include <string>

namespace mylib {

std::string greet(const std::string& name);
int version_major();
int version_minor();

} // namespace mylib

#endif
