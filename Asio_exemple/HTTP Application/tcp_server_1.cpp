//    A synchronous TCP daytime server
// This tutorial program shows how to use asio to impliment a server application with tcp.
#include <ctime>
#include <iostream>
#include <string>
#include <asio.hpp>

#define   end_   '\n'
using tcp = asio::ip::tcp;

// create the string to be sent back to client 
std::string make_daytime_string() {
	time_t  now = time(0);
	char str[256];
	ctime_s(str, 256, &now);
	return str;
}






int main() {

	std::cout << "Start Program" << end_;
	std::cout << "Port : " << 13 << end_;
	std::cout << "tcp::v4().type()      : " << tcp::v4().type() << end_;
	std::cout << "tcp::v4().family()    : " << tcp::v4().family() << end_;
	std::cout << "tcp::v4().protocol()  : " << tcp::v4().protocol() << end_;
	std::cout << "tcp::v4().v6().type() : " << tcp::v4().v6().type() << end_;

	try {
		asio::io_context  ctx;

		// acceptor object needs to be listen for new connections. it is initialised to listen to tcp port
		// 13, IP version 4.
		tcp::acceptor acceptor(ctx, tcp::endpoint(tcp::v4(), 13));

		// this iterative server, which means that it will handle one connection at a time. Create a 
		// socket that will represent the connection to  the client, and then wait for a connection.
		for (;;) {
			tcp::socket socket(ctx);
			acceptor.accept(socket);

			// affich socket information
			std::cout << "IP Host : " << socket.local_endpoint().address().to_string() << end_;
			std::cout << "IP Remt : " << socket.remote_endpoint().address().to_string() << end_;

			// A client is accessing our service. Determine the current time
			// and transfer this information to the client.
			std::string message = make_daytime_string();
			std::error_code  ignored_error;
			asio::write(socket, asio::buffer(message), ignored_error);
			std::this_thread::sleep_for(std::chrono::seconds(10));
		}
	}
	catch (std::exception& e) {
		// handle any exception
		std::cerr << e.what() << '\n';
	}



	return 0;
}
