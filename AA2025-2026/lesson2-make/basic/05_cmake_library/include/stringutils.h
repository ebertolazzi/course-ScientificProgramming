#ifndef STRINGUTILS_H
#define STRINGUTILS_H

#include <string>
#include <vector>

namespace stringutils {

std::string to_upper(const std::string& s);
std::string to_lower(const std::string& s);
std::vector<std::string> split(const std::string& s, char delimiter);
bool starts_with(const std::string& s, const std::string& prefix);

} // namespace stringutils

#endif
