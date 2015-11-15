#ifndef UTIL_HPP
#define UTIL_HPP

#include <iostream>
#include <vector>
#include <stdexcept>

#include <boost/preprocessor/stringize.hpp>

#define BM_ASSERT(p)                                                \
    do {                                                            \
        if (!(p)) {                                                 \
            const char* message =                                   \
                "ASSERTION FAILED on "                              \
                __FILE__ ":" BOOST_PP_STRINGIZE(__LINE__) " : " #p; \
            std::cerr << message << std::endl;                      \
            throw std::runtime_error(message);                      \
        }                                                           \
    } while (false)

namespace bm {

template<class T>
std::vector<std::vector<T>> createMatrixWithShape(
    size_t width, size_t height, const T& defValue = T{})
{
    return std::vector<std::vector<T>>(width, std::vector<T>(height, defValue));
}

template<class T, class U>
std::vector<std::vector<T>> createMatrixWithShape(
    const std::vector<std::vector<U>>& other, const T& defValue = T{})
{
    // Assume the shape is rectangular
    auto width = other.size();
    auto height = width > 0 ? other[0].size() : 0u;
    return createMatrixWithShape(width, height, defValue);
}

} // namespace bm

#endif
