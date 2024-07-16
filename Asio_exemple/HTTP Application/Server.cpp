/*
			Make two programs communicate with each other using asio in C++
			1. Server
*/

#include <iostream>
#include <asio.hpp>
#include <string>

#define end_  '\n'


int main() {

	// Create io_service or context
	asio::io_context   ctx;

	// Define the port number for communication
	unsigned short port = 8083;

	// Create an acceptor object
	asio::ip::tcp::acceptor acceptor(ctx,
		asio::ip::tcp::endpoint(asio::ip::address::from_string("127.0.0.1"), port));
	
	std::cout << "Server Listening an Port: " << port << end_;

	// Wait for a connection from a client
	asio::ip::tcp::socket  socket(ctx);
	acceptor.accept(socket);

	std::cout << "Client connected" << end_;

	// Buffer for receiving data
	std::array<char, 128> buffer;

	// Receive data from the client
	size_t bytes_received = socket.read_some(asio::buffer(buffer));

	// Process the received data (e.g.,  print it)
	std::cout << "Received from client : " << std::string(buffer.data(), bytes_received) << end_;

	// Send a response back to the client (optional)
	std::string message = "Hello from a server";
	socket.write_some(asio::buffer(message));

	// Close the connection
	socket.close();

	return 0;
}

