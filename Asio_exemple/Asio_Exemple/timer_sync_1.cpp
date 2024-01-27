#include <iostream>
#include <chrono>
#include <thread>
// asio necessary libraries 
#include "asio/io_context.hpp"
#include "asio/steady_timer.hpp"

#include "MyLib/Console_Library/escape_code.h"


void some_work() {
	for (int i = 0; i != 10; ++i) {
		std::this_thread::sleep_for(std::chrono::milliseconds(70));
		print_ << "work " << i << end_;
	}
}


int main()
{
	Print_(color::Green, "Hello Asio Timer and io_context ") << end_;

	// context :
	asio::io_context ctx;
	asio::steady_timer timer{ ctx,std::chrono::seconds(3) };
	asio::error_code ec;

    // all Asio asynchronous APIs start with prefix async_
	// here we just call a synchronouse API  which will block untile the timer expires.

	timer.wait(ec);

	// after 3 seconds , print End of program.

	print_ << "show error message : " << ec.message() << end_;
	print_ << "error message value: " << ec.value() << end_;
	if (ec) print_ << "error ... : true" << end_;
	else    print_ << "there are no error : false" << end_;
	
	print_ << "End of program " << end_;

	// No need to call ctx.run() since we don't have any asynchronous operation to execute.

	std::cin.get();
	return 0;
}