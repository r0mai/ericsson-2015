#include <iostream>

#include "Game.hpp"
#include "responseHelper.hpp"
#include "stream.hpp"

namespace bm {

void Game::run() {
    protocol::Global global;
    while (readProtoFromStream(global, std::cin)) {
        protocol::Response response = calculateResponse(fromProto(global));

        if (!writeProtoOnStream(response, std::cout)) {
            std::cerr << "write error" << std::endl;
            break;
        }
    }
    std::cerr << "Game over, std::cin.eof(): " << std::cin.eof() << std::endl;
}

protocol::Response Game::calculateResponse(const State& state) {
    ResponseHelper helper;

    std::cerr << "Logging that we do not do anything in " << state.tick << " tick" << std::endl;

    std::cerr << toString(state.fields) << std::endl;
    helper.nothing();

    return helper.getResponse();
}

} // namespace bm
