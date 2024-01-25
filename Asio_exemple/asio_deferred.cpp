#include <iostream>
#include <chrono>
#include <asio.hpp>
#include "MyLib/Console_Library/escape_code.h"

void Time_now(asio::steady_timer& timer, std::string id, int x = 4, int y = 10) {

	std::chrono::sys_seconds _timing = std::chrono::floor<std::chrono::seconds>( std::chrono::system_clock::now());

	printm_(x, y) << "Time now is : " <<  _timing 
		                      <<  " thread Id [" << id << "] " << std::this_thread::get_id();

	timer.expires_after(std::chrono::seconds(1));
	timer.async_wait([&](auto...args) {Time_now(timer, id, x , y); });
}

int main()
{
	asio::io_context ctx;
	asio::io_context ctx2;
	asio::steady_timer timer1(ctx);
	asio::steady_timer timer2(ctx2);

	print_ << "get id of main thread : " << std::this_thread::get_id() << end_;

	Time_now(timer1, "timer1");

	Time_now(timer2, "timer2", 4, 12);

	ctx2.run();

	std::thread thrContext{ [&]() {ctx.run(); } };

	thrContext.detach();
	std::cin.get();
	return 0;
}