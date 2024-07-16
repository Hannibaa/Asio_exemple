#include <iostream>
#include <deque>



#include <asio.hpp>


class chat_handler : public std::enable_shared_from_this<chat_handler>
{
public:
	chat_handler(asio::io_context& service)
		:_service{service}
		, _socket{service}
		, _write_strand{ service }
	{}

	asio::ip::tcp::socket& socket() {
		return _socket;
	}

	void start() {
		read_packet();
	}

	void read_packet() {
		asio::async_read_until(_socket, _in_packet, '\0',
			[me = shared_from_this()](std::error_code ec, size_t bytes_xfer) {
				me->read_packet_done(ec, bytes_xfer);
			});
	}

	void read_packet_done(std::error_code ec, size_t bytes_transferred) {
		if (ec) return;

		std::istream stream(&_in_packet);
		std::string packet_string;
		stream >> packet_string;

		// do something with it 

		read_packet();
	}

	void send(std::string msg) {
		_service.post(_write_strand.wrap([me = shared_from_this(),msg]() {
			me->queue_message(msg);
			}));

	}

private:
	void queue_message(std::string msg) {
		bool write_in_progress = !_send_packet_queue.empty();

		_send_packet_queue.push_back(std::move(msg));

		if (!write_in_progress) {
			start_packet_send();
		}
	}

	void start_packet_send() {
		_send_packet_queue.front() += "\0";
		asio::async_write(_socket
			, asio::buffer(_send_packet_queue.front())
			, _write_strand.wrap([me = shared_from_this()](std::error_code ec, size_t) {
				me->packet_send_done(ec);
				}));
	}

	void packet_send_done(std::error_code ec) {
		if (!ec) {
			_send_packet_queue.pop_front();
			if (!_send_packet_queue.empty()) {
				start_packet_send();
			}
		}
	}

private:
	asio::io_context&              _service;
	asio::ip::tcp::socket          _socket;
	asio::io_context::strand       _write_strand;
	asio::streambuf                _in_packet;
	std::deque<std::string>        _send_packet_queue;
};



int main() {


	asio::io_context    service;
	chat_handler    connection(service);

	connection.start();


	service.run();

	return 0;
}