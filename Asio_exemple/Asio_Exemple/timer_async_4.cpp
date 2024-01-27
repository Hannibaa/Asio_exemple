#include <iostream>
#include <syncstream>
#include <chrono>
#include <thread>
#include <mutex>

// asio necessary libraries 
#include "asio/io_context.hpp"
#include "asio/steady_timer.hpp"

#include "MyLib/Console_Library/escape_code.h"

std::mutex mtxIO;
bool stop_context{ false };

// work
void some_work(asio::error_code ec, int x, int y) {

	//std::lock_guard<std::mutex> lock(mtxIO);
	esc::clear_line(x, y);
	printm_(x,y) << "hello ..." << end_ 
	             << "THREAD ( " << std::this_thread::get_id() << " ) " << end_;
}


void Clock_(asio::error_code ec, asio::steady_timer& timer) {

	std::chrono::sys_seconds time_ =
		std::chrono::floor<std::chrono::seconds>(std::chrono::system_clock::now());

	std::osyncstream(std::cout) << MOVETO(3, 6) << time_;
	timer.expires_after(std::chrono::seconds(1));
	timer.async_wait([&](auto...args) {Clock_(ec, timer); });
}

void stop_process() {

	char c = std::getchar();

	if (c == 's') stop_context = true; else stop_process();
}


int main()
{
	Print_(color::Green, "Hello Asio Timer and io_context ") << end_;
	print_ << "main process id : " << std::this_thread::get_id() << end_;

	// context :
	asio::io_context ctx;
	asio::steady_timer timer1{ ctx,std::chrono::seconds(3) };
	asio::steady_timer timer2{ ctx,std::chrono::seconds(1) };
	asio::steady_timer tClock{ ctx,std::chrono::seconds(5) };
	asio::error_code ec;

	timer1.async_wait([&](asio::error_code ec) {some_work(ec, 5, 2); });
	timer1.async_wait([&](asio::error_code ec) {some_work(ec, 5, 10); });
	Clock_(ec, tClock);


	std::thread thr3(stop_process);
	std::thread thrStopContext([&]() {

		while (true)
			if (stop_context) {
				ctx.stop();
				printm_(10, 10) << "context was stoped " << end_;
				break;
			}
		});

	ctx.run();

	thr3.join();
	thrStopContext.join();

	std::cin.get();
	return 0;
}