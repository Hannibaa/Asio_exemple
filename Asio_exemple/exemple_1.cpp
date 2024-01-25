#include <iostream>

#include <asio.hpp>
#include <asio/ts/buffer.hpp>
#include <asio/ts/internet.hpp>

#define  print_      std::cout
#define  end_      '\n'

std::vector<char> vBuffer(1 * 1024);

void GrabSomeData(asio::ip::tcp::socket& socket) {
	socket.async_read_some(asio::buffer(vBuffer.data(), vBuffer.size()),
		[&](std::error_code ec, std::size_t length)
		{
			if (!ec) {
				std::cout << "\n\nRead " << length << " bytes\n\n";

				//for (int i = 0; i < length; i++)
					//std::cout << vBuffer[i];

				GrabSomeData(socket);
			}
		});
}


int main() {

	asio::error_code ec;

	// Create a "context" - essentially the plateform specific interface
	asio::io_context context;

	// Give some fake tasks to asio so the context doesnt finish
	asio::io_context::work idleWork(context);

	// start the context
	std::thread thrContext = std::thread([&]() { context.run(); });

	// Get the address of somewhere we wish to connect to 
	asio::ip::tcp::endpoint endpoint(asio::ip::make_address("127.0.0.1", ec), 80);

	// Create a socket, the context will deliver the implementation
	asio::ip::tcp::socket socket(context);

	// Tell socket to try and connect
	socket.connect(endpoint, ec);

	// error code 
	if (!ec) {
		std::cout << "Connected!" << end_;
	}
	else
	{
		std::cout << "Failed to connect to address:\n" << ec.message() << end_;
	}


	if (socket.is_open()) {
		GrabSomeData(socket);

		std::string sRequest =
			"GET / HTTP/1.1\r\n"
			"Host: localhost\r\n"
			"Connection: close\r\n\r\n";

		socket.write_some(asio::buffer(sRequest.data(), sRequest.size()), ec);

		// Program does something else, while asio handles data transfer in background
		std::this_thread::sleep_for(std::chrono::milliseconds(2000));

		context.stop();
		if (thrContext.joinable()) thrContext.join();
	}

	std::string pagehttp;
	pagehttp.resize(1024);

	std::copy(vBuffer.begin(), vBuffer.end(), pagehttp.begin());



	std::cin.get();
	print_ << "SHOW ME THE STRING --------------------> " << pagehttp.substr(10) << end_;


	std::cin.get();
	return 0;
}