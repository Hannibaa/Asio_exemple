/*
        Get IP address from hostname using asio resolver 
		Author : KADDA Aoues.
		Date   : 26 / 4 / 2024
*/

#include <iostream>
#include "asio.hpp"
#include <MyLib/Console_Library/escape_code.h>

void handle_resolve_query(const std::error_code& ec, asio::ip::tcp::resolver::iterator iter) {

	if (ec) return;

	asio::ip::tcp::resolver::iterator end;
	
	for (; iter != end; ++iter) {
		asio::ip::tcp::endpoint endpoint = *iter;
		Print_(color::Green, endpoint) << end_;
	}
}


int main() {

	std::string site_name = "www.google.com";

	std::cout << "give me url name : ";
	std::cin >> site_name;

	asio::io_context ctx;

	asio::ip::tcp::resolver  resolver(ctx);

	resolver.async_resolve(asio::ip::tcp::resolver::query(site_name, "http"), handle_resolve_query);

	ctx.run();



	Print_(color::Red, "End of program...") << end_;

	return 0;
}