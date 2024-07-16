#include <iostream>
#include <thread>
#include <asio.hpp>


#include <include/console/escape_code.h>

using tcp = asio::ip::tcp;

class Listener :public std::enable_shared_from_this<Listener>
{

	asio::io_context&   _ctx;
	tcp::acceptor       _acceptor;
	std::vector<asio::ip::tcp::socket>   vsockets;

public:
	Listener(asio::io_context& context, unsigned short port)
		:_ctx(context)
		,_acceptor(context,{asio::ip::make_address("127.0.0.1"), port})
	{
	}

	void asyncAccept() {
		_acceptor.async_accept(_ctx, [&,self{shared_from_this()}](std::error_code ec, tcp::socket socket) {

			Print_(color::Green, "Connection accepted") << end_;

			vsockets.emplace_back(std::move(socket));

			Print_(color::Fuchsia, "Number os Socket add") << vsockets.size() << end_;
			
			self->asyncAccept();
			});
	}

	void asynRead() {
		std::string str;
		str.reserve(127);
		if (!vsockets.empty()) {
			vsockets[0].async_read_some(asio::buffer(str.data(), 125),
				[&](std::error_code ec, size_t size) {
					asynRead();
				});

			Print_(color::Red, "read : ");
			Print_(color::Aqua, str) << end_;
		}
	}
};



int main() {
	Print_(color::Red, "Server start") << end_;

	auto const port = 8085;
	Print_(color::Red, "Port : ") << port << end_;

	asio::io_context  ctx;

	auto listener = std::make_shared<Listener>(ctx, port);

	std::thread(&Listener::asynRead, listener).detach();

	listener->asyncAccept();


	ctx.run();

	Print_(color::Red, "Server End") << end_;
	return 0;
}