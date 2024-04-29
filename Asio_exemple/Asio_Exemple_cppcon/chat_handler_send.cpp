#include <asio.hpp>


class chat_handler : public std::enable_shared_from_this<chat_handler> {

public:
	void send(std::string msg) {
		service_.post;
	}
};