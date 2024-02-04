#include <iostream>	
#include <asio.hpp>

#include "MyLib/Console_Library/escape_code.h"




// now i want to read some data from net:

int main() {
	std::vector<char> vBuffer(1 * 1024);


	asio::io_context ctx;

	asio::error_code ec;

	std::thread thrContext{ [&]() { ctx.run(); } };

	asio::io_context::work fkWork(ctx);

	asio::ip::tcp::socket socket(ctx);

	asio::ip::tcp::endpoint epPoint(asio::ip::make_address("142.251.37.46",ec), 80);

	socket.async_connect(epPoint, [](asio::error_code ec) {
		if (!ec) {
			std::cout << "connection succeded\n";
		}
		});

	print_ << "1. first error : " << ec.message() << end_;

	if (socket.is_open()) {
		print_ << "socket is open " << end_;
		std::string _get =
			"GET / HTTP1.1/\r\n"
			"Connection: close\r\n\r\n";

		socket.write_some(asio::buffer(_get.data(), _get.size()), ec);

		socket.read_some(asio::buffer(vBuffer.data(), vBuffer.size()));

		std::this_thread::sleep_for(std::chrono::milliseconds(450));
		ctx.stop();
		thrContext.join();
	}

	Print_(color::Green, "DATA Collected :") << end_;
	print_ << vBuffer.data() << end_;

	return 0;
}

