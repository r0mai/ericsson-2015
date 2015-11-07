
#include <boost/multi_array.hpp>

namespace bm {

struct State {
    using Fields = boost::multi_array<int, 2>;

    Fields fields;
};

} // namespace bm
