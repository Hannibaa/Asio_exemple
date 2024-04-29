#include <iostream>
#include "asio.hpp"
#include <MyLib/Console_Library/escape_code.h>


int main() {
	try {
		asio::io_context ctx;

		// Choose well-known external server (e.g. Google DNS)
		asio::ip::udp::endpoint endpoint(
			asio::ip::address::from_string("8.8.8.8"), 53); // Port 53 for DNS

		// Create UDP socket
		asio::ip::udp::socket  socket(ctx);

		// Connect to the external server  (dummy connection)
		socket.connect(endpoint);

		// Local endpoint holds your machine's IP address
		asio::ip::udp::endpoint local_endpoint = socket.local_endpoint();

		std::string ip_address = local_endpoint.address().to_string();

		Print_(color::Green, "IP : ") << ip_address << end_;
	} 
	catch (const std::exception& e) {
		std::cerr << "Error getting local IP address : " << e.what() << end_;
	}


	Print_(color::Red, "End program ") << end_;
	return 0;
}