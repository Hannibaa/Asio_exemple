#include <iostream>
#include <chrono>
#include <thread>
// asio necessary libraries 
#include "asio/io_context.hpp"
#include "asio/steady_timer.hpp"

#include "MyLib/Console_Library/escape_code.h"

// the 'error_code' paarameter for all handlers in asio is passed by value
// now instead of const reference. In  some example, you may still notice 
// the usage of const reference
void some_work(asio::error_code ec) {
	print_ << "process Id : " << std::this_thread::get_id() << end_;
	for (int i = 0; i != 10; ++i) {
		std::this_thread::sleep_for(std::chrono::milliseconds(70));
		print_ << "work " << i << end_;
	}
}


int main()
{
	Print_(color::Green, "Hello Asio Timer and io_context ") << end_;
	print_ << "main process id : " << std::this_thread::get_id() << end_;
	// context :
	asio::io_context ctx;
	asio::steady_timer timer{ ctx,std::chrono::seconds(3) };
	asio::error_code ec;

	// all Asio asynchronous APIs start with prefix async_
	// here we just call a synchronouse API  which will block untile the timer expires.

	timer.async_wait(&some_work);

	// ctx.run;
	size_t h_ = ctx.run();
	print_ << "Number of handler executed :" << h_ << end_;

	// after 3 seconds , print End of program.
	print_ << "End of program " << end_;

	// No need to call ctx.run() since we don't have any asynchronous operation to execute.

	std::cin.get();
	return 0;
}