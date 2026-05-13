#include "mylib/mylib.h"

namespace mylib {

std::string greet(const std::string& name) {
    return "Hello, " + name + "!";
}

int version_major() { return 1; }
int version_minor() { return 0; }

} // namespace mylib
