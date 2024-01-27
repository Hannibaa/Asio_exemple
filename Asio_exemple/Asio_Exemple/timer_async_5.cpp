/*
			Wait a timer asynchronously.
			Bind extra argument to a function so that it matches the signature of 
			The expected handler.
*/



#include <iostream>
#include <functional>
#include <chrono>

#include <asio/steady_timer.hpp>
#include <asio/io_context.hpp>

#include "MyLib/Console_Library/escape_code.h"

void Print(std::error_code ec, 
	       asio::steady_timer& timer,
	       int& count)
{
	if (count < 3) {
		std::cout << count << end_;
		++count;


		// Change the timer's expiry time.
		timer.expires_after(std::chrono::seconds(1));

		// Start a new asyncronous wait.
		timer.async_wait(std::bind(&Print, std::placeholders::_1, std::ref(timer),
			std::ref(count)));
	}
}

int main()
{
	asio::io_context ctx;

	asio::steady_timer timer(ctx, std::chrono::seconds(1));

	int count = 0;

	// async_wait() expects a handler function (or function object) with the 
	// signature |void(std::error_code)|
	// Binding the additional parameters converts your Print function into a 
	// function object that matches the signature correctly.

	timer.async_wait(std::bind(&Print, std::placeholders::_1, std::ref(timer),
		std::ref(count)));

	ctx.run();

	Print_(color::Fuchsia, "Final count is :") << count << end_;

	std::cin.get();
	return 0;
}