// Asynchronous TCP server daytime

#include <iostream>
#include <functional>
#include <asio.hpp>

#define  end_    '\n'

using tcp = asio::ip::tcp;

// create the string to be sent back to client 
std::string make_daytime_string() {
	time_t  now = time(0);
	char str[256];
	ctime_s(str, 256, &now);
	return str;
}


// connection class
class tcp_connection : std::enable_shared_from_this<tcp_connection>
{
public:
	typedef  std::shared_ptr<tcp_connection>  pointer;

	static pointer create(asio::io_context& context) {
		return pointer(new tcp_connection(context));
	}

	tcp::socket& socket() {
		return m_socket;
	}

	void start() {
		m_message = make_daytime_string();

		asio::async_write(m_socket, asio::buffer(m_message), [](auto...arg) {

			});
			
	}

private:
	tcp_connection(asio::io_context& context)
		:m_socket(context)
	{}

	void handle_write(const asio::error_code& ec, size_t size_trf) {

	}

	tcp::socket    m_socket;
	std::string    m_message;
};


// We need to create a server object to accept incoming client connections.
// io_context object provides I/O services, such as sockets, that the 
// server object will use.
class tcp_server {
public:
	// The constructor initialise an acceptor to listen on TCP port 13
	tcp_server(asio::io_context& context)
		: m_context(context),
		  m_acceptor(context, tcp::endpoint(tcp::v4(),13))
	{
		start_accept();
	}



private:
	// function start_accept() creates a socket and initiates an asynchronous accept operation to wait
	// for a new connection.
	void start_accept() {
		tcp_connection::pointer new_connection = tcp_connection::create(m_context);

		m_acceptor.async_accept(new_connection->socket(), 
			std::bind(&tcp_server::handle_accept, this,
			new_connection,
			std::placeholders::_1));
	}

	void handle_accept(tcp_connection::pointer new_connection, const asio::error_code& error) {
		if (!error) {
			new_connection->start();
		}

		start_accept();
	}

	asio::io_context&        m_context;
	asio::ip::tcp::acceptor  m_acceptor;

};


int main() {

	try {
		asio::io_context   ctx;
		tcp_server server(ctx);
		ctx.run();
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << end_;
	}

	return 0;
}