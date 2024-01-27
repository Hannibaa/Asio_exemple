#include <iostream>
#include <asio.hpp>


int main() {
	// 0. Create error code
	asio::error_code ec;
	// 1. create context io
	asio::io_context context;
	// 2. Create fake work for context
	asio::io_context::work fkWork(context);
	// 3. Create thread to run context in separate thread
	std::thread thr([&]() {context.run(); });
	// 4. Create End point to connect to address from string value of integer ipv4 
	asio::ip::tcp::endpoint endpoint(asio::ip::make_address("142.251.37.46", ec), 80);
	// 5. Create socket, the context will deliver the implimentation
	asio::ip::tcp::socket socket(context);
	
	// operation : 
	// 6. tell socket to try to connect :
	socket.connect(endpoint, ec);

	std::cout << "read error message : " << ec.message() << "\n";

	if (socket.is_open()) {

		// 7. Create string to send it by method GET
		std::string sRequest =
			"GET / HTTP/1.1\r\n"
			// Host: google.com\r\n  // for exemple we should change also ipv4.
			"Connection: close\r\n\r\n";

		// 8. write_some is for sending data to endpoint 
		socket.write_some(asio::buffer(sRequest.data(), sRequest.size()), ec);
		std::cout << "read last error : " << ec.message() << '\n';

		std::this_thread::sleep_for(std::chrono::milliseconds(300));

		size_t bytes = socket.available();

		if (bytes > 0) {
			std::cout << "byte available to read is : " << bytes;
		}
		else std::cout << "no bytes : error : " << ec.message() << '\n';

		// 9. because we add fake work so we should stoped it .
		context.stop();
	}

	thr.join();
	return 0;
}
