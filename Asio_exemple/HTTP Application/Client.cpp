/*
			Make two programs communicate with each other using asio in C++
			2. Client
*/

#include <iostream>
#include <asio.hpp>
#include <string>

#define end_  '\n'



int main() {

	// Create an io_context
	asio::io_context  ctx;

	// Define the server IP address and port number
	std::string server_address = "127.0.0.1";
	unsigned short port = 8083;

	// Create a socket object
	asio::ip::tcp::socket    socket(ctx);

	// Connect to the server
	socket.connect(asio::ip::tcp::endpoint(asio::ip::address::from_string(server_address), port));

	std::cout << "Connected to server" << end_;

	// Message to send to the server
	std::string message = "Hello from the Client";

	// Send data to the server
	socket.write_some(asio::buffer(message));

	// Buffer for receive data from server
	std::array<char, 128> buffer;

	// Receive data from the server
	size_t bytes_received = socket.read_some(asio::buffer(buffer));

	// Process the received data (e.g. print it)
	std::cout << "Received data from server: " << std::string(buffer.data(), bytes_received) << end_;

	// Close the connection
	socket.close();

	return 0;
}