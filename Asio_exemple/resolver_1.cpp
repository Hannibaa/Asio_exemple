#include <iostream>
#include <asio.hpp>


#include <asio.hpp>
#include <include/net_io/asio_utility.h>
#include <include/console/escape_code.h>



int main() {
	// 1. Include necessary headers
	// 2. Create Resolver object

	asio::io_context  context;
	asio::ip::tcp::resolver resolver(context);

	// 3. Construct a Query
	std::string hostname;
	std::string service_name = "http";                 // Or port number : 80
	Print_(color::Green, "Enter a location : ");
	std::cin >> hostname;

	// Query object specifies the hostname (domain name) to resolve and the service
	// name (e.g. http) or port number as a string.
	asio::ip::tcp::resolver::query query(hostname, service_name); 

	// 4. Synchronous Resolution (Blocking):
	asio::ip::tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);
	if (endpoint_iterator != resolver.end()) {
		// Use the endpoint (IP address and port) for connection
		asio::ip::tcp::endpoint endpoint = *endpoint_iterator;
		//...
	}
	else {
		// handle resolution error.
	}

	return 0;
}