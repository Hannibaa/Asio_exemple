// Wait a timer asynchronously.
// Use member function as Handler.

#include <chrono>
#include <functional>
#include <iostream>
#include <asio/steady_timer.hpp>
#include <asio/io_context.hpp>

#include "MyLib/Console_Library/escape_code.h"


class Printer {
public:
	explicit Printer(asio::io_context& context)
		:timer_(context, std::chrono::seconds(1))
		,count_(0)
	{
		// For member function handlers, always bind |this| as the first argument.
		// Unlike global function, '&' is mandatory for referrin to member
		// function pointers.

		timer_.async_wait(std::bind(&Printer::Print, this, std::placeholders::_1));
	}

	~Printer() {
		std::cout << "Final count is " << count_ << end_;
	}

private:
	void Print(std::error_code ec) {
		if (count_ < 3) {
			std::cout << count_ << end_;
			++count_;

			timer_.expires_after(std::chrono::seconds(1));

			timer_.async_wait(std::bind(&Printer::Print, this,
				std::placeholders::_1));

		}
	}

	asio::steady_timer timer_;
	int count_;
};


int main() {
	asio::io_context ctx;

	Printer printer{ ctx };

	ctx.run();

	wait_;
	return 0;
}