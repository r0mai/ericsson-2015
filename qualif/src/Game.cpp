#include <iostream>

#include "Game.hpp"
#include "responseHelper.hpp"
#include "stream.hpp"

namespace bm {

void Game::run() {
	protocol::Global global;
	while(readProtoFromStream(global, std::cin)) {
		ResponseHelper helper;

		std::cerr << "Logging that we do not do anything in " << global.tick() << " tick" << std::endl;
		helper.nothing();

		protocol::Response response = helper.getResponse();

		if (!writeProtoOnStream(response, std::cout)) {
			std::cerr << "write error" << std::endl;
			break;
		}
	}
	std::cerr << "Game over, std::cin.eof(): " << std::cin.eof() << std::endl;
}

} // namespace bm
