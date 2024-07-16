#include <iostream>
#include <thread>
#include <string>
#include <conio.h>

#include <asio.hpp>
#include <include/net_io/asio_utility.h>


#define      end_   '\n'

using tcp = asio::ip::tcp;

bool bStop = false;

void LunchStopThread() {
	std::thread thrStop([] {
		while (true) {
			char c = _getch();
			if (c == 'q' || c == 'Q') {
				bStop = true;
				std::terminate();
				break;
			}
		}
		});

	thrStop.detach();
}

std::vector<char>  buffer(20 * 1024);

// Grab data from socket recurssively
void GrabSomeData(asio::ip::tcp::socket& socket, std::ostream& os) {
	auto ssocket = std::move(socket);
	ssocket.async_read_some(asio::buffer(buffer.data(), buffer.size()),
		[&](std::error_code ec, size_t size) {
			if (!ec) {
				os << "\n\nRead " << size << "\n\n";

				for (int i = 0; i < size; ++i)
					os << buffer[i];

				GrabSomeData(socket, os);
			}
			else {
				std::cout << "Error : " << ec.message() << end_;
			}
		});
}

int main() {
	std::cout << "Program Start\n";
	auto const address = asio::ip::make_address("127.0.0.1");
	auto const port = static_cast<unsigned short>(std::atoi("8083"));

	LunchStopThread();
	asio::io_context   context(1);

	tcp::acceptor acceptor(context, { address,port });

	std::cout << "Server : " << address.to_string() << end_;
	std::cout << "Port   : " << port << end_;

	while (true) {
		if (bStop) break;  // get out of loop
		tcp::socket  socket(context);
		std::cout << "Waiting for new connection" << end_;

		try
		{
			acceptor.accept(socket);
			std::cout << "socket accepted" << end_;
			std::cout << "locale adress   : " << socket.local_endpoint().address().to_string() << end_;
			std::cout << "remote adress   : " << socket.remote_endpoint().address().to_string() << end_;
		}
		catch (const std::error_code& ec)
		{
			std::cout << "Execption " << ec.message() << end_;
		}
		
		std::thread([q {std::move(socket)}]() mutable {

				while (q.is_open()) {
					try {
						std::vector<char>   buf(1024);

						size_t bytes = q.read_some(asio::buffer(buf));

						std::cout << "Get:" << bytes << " Byes:" << std::string(buf.data(), bytes) << end_;

					}
					catch (const asio::system_error& se) {
						if (se.code() != asio::socket_errc::not_found) {
							std::cout << "catch loop " << se.code().message() << end_;
							break;
						}
					}
				}

			}).detach();

	}

	//context.run();

	std::cout << "Program End\n";
	return 0;
}
