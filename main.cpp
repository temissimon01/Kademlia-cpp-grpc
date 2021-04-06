#include <iostream>

#ifdef _WIN32
#pragma comment(lib, "Ws2_32.lib")
#endif

#include <vector>
#include <boost/algorithm/string.hpp>
#include <boost/convert.hpp>

#include <API/Node/Server.h>


int main(int argc, char* argv[]) {
	
	

	std::vector<Server*> nodes;

	std::string cmd;
	do {

		std::getline(std::cin, cmd);

		boost::to_upper(cmd);
		boost::trim(cmd);

		if (cmd.compare("ADD") == 0) {
			Server* instance = new Server(Identifier(nodes.size()));

			instance->start("127.0.0.1", 44973 + nodes.size());

			nodes.push_back(instance);

			std::cout << "CREATED NODE: " << std::endl;
			std::cout << "ID: " << (std::string)instance->address().id() << std::endl;
			std::cout << "IP: " << instance->address().ip() << std::endl;
			std::cout << "PORT: " << instance->address().port() << std::endl;
			std::cout << std::endl;

			if (nodes.size() > 1) {
				instance->bootstrap(nodes[nodes.size() - 2]->address());
			}
		}
		else if (cmd.compare("STATE") == 0) {
			for (int i = 0; i < nodes.size(); i++) {
				std::cout << "NODE " << (std::string)nodes[i]->id() << " ROUTING TABLE: " << std::endl;
				std::cout << nodes[i]->routingTable().toString() << std::endl << std::endl;
			}
		}
		else if (boost::starts_with(cmd, "FIND ")) {

			std::vector<std::string> args;
			boost::split(args, cmd, boost::is_any_of(" "));

			if (args.size() == 2) {
				Identifier::numeric_type node = boost::lexical_cast<Identifier::numeric_type>(args[1]);


				FindNodeAnswer findResult = nodes[0]->findNode(nodes[0]->address(), nodes[0]->address(), node);

				if (findResult.found()) {
					std::cout << "FOUND NODE: " << std::endl;
					std::cout << "ID: " << (std::string)findResult.begin()->id() << std::endl;
					std::cout << "IP: " << findResult.begin()->ip() << std::endl;
					std::cout << "PORT: " << findResult.begin()->port() << std::endl;
					std::cout << std::endl;
				}
				else {
					std::cout << "NOT FOUND" << std::endl;
				}
			}

		}
		else if (boost::starts_with(cmd, "STORE ")) {
			std::vector<std::string> args;
			boost::split(args, cmd, boost::is_any_of(" "));

			if (args.size() == 3) {
				std::string key = (args[1]);
				std::string value = (args[2]);

				if (nodes[0]->store(key, value)) {
					std::cout << "Key stored!" << std::endl;
				}
				else {
					std::cout << "Unable to store" << std::endl;
				}
			}
		}
		else if (boost::starts_with(cmd, "GET ")) {
			std::vector<std::string> args;
			boost::split(args, cmd, boost::is_any_of(" "));

			if (args.size() == 2) {
				std::string key = (args[1]);
				
				try {
					std::cout << key << ": " << nodes[0]->get(key) << std::endl;
				}
				catch (...) {
					std::cout << "Key not found" << std::endl;
				}
			}
		}

	} while (cmd.compare("EXIT") != 0);

	for (int i = 0; i < nodes.size(); i++) {
		nodes[i]->stop();
		delete nodes[i];
	}

	system("pause");

	return 0;
}