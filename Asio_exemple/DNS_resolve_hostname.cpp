/*
   using reverse to get hostname from ip adresses

*/

#include <iostream>
#include <string>
#include "asio.hpp"
#include <MyLib/Console_Library/escape_code.h>



int main() {
	
	asio::io_context        ctx;
	asio::ip::tcp::resolver resolver(ctx);

	std::string ip_address = "172.217.26.68";

	Print_(color::Blue, "give correct address ip : ");
	std::cin >> ip_address;

	asio::ip::address addr = asio::ip::address::from_string(ip_address);
	asio::ip::tcp::endpoint  endpoint(addr, 0); // Port 0 for reverse resolution.


	resolver.async_resolve(endpoint,
		[endpoint, &ctx](const std::error_code& ec,
			asio::ip::tcp::resolver::iterator iterator) {
				if (ec) {
					std::cerr << "Error resolving hostname : " << ec.message() << end_;
					return;
				}

				// Loop through resolution results
				while (iterator != asio::ip::tcp::resolver::iterator()) {
					std::cout << iterator->host_name() << end_;
					++iterator;
				}

				ctx.stop();
		}
	);

	ctx.run();

	Print_(color::Red, "End of Program") << end_;
	return 0;
}