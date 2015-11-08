#ifndef TEST_UTIL_HPP
#define TEST_UTIL_HPP

#include "State.hpp"

#include <vector>
#include <string>

namespace bm {

State stateFromString(const std::vector<std::string>& lines);

} // namespace bm

#endif
