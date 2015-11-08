#include "TestUtil.hpp"
#include "Util.hpp"

#include <cassert>

namespace bm {

FieldElement fieldElementFromChar(char ch) {
    switch (ch) {
        case 'W': return Wall{};
        case ' ': return {};
        case 'D': return Doc{};
        case 'L': return DeLorean{};
        case 'C': return Chest{};
        default: assert(false); return {};
    }
}

State stateFromString(const std::vector<std::string>& lines) {
    assert(lines.size() > 0 && lines[0].size() > 0);
    for (unsigned i = 1; i < lines.size(); ++i) {
        assert(lines[0].size() == lines[i].size());
    }

    State state;

    state.tick = 20;
    state.height = lines.size();
    state.width = lines[0].size();

    state.fields = createMatrixWithShape<Field>(state.width, state.height);

    for (unsigned y = 0; y < lines.size(); ++y) {
        for (unsigned x = 0; x < lines[y].size(); ++x) {
            state.fields[x][y].element = fieldElementFromChar(lines[y][x]);
        }
    }
    return state;
}

} // namespace bm
