#include <iostream>
#include <syncstream>
#include <functional>
#include <vector>

#include <asio.hpp>

#include <MyLib/Console_Library/escape_code.h>
#include "..\\include\Asio_utility.h"



int main() {

	asio::io_context ctx;
	std::vector<asio::steady_timer> vTimer;

	for (int i = 0; i < 10; ++i) {
		vTimer.push_back(asio::steady_timer(ctx, Seconds(i + 1)));
		vTimer[i].async_wait([=](auto...args) {
			print_ << "timer number : " << i << end_;
			print_ << "time is      : " << time_now << end_;
			print_ << "id thread    : " << std::this_thread::get_id();
			print_ << "----------------------------------------\n";
			});
	}

	int ii{};
	esc::cls();
	for (auto& timer : vTimer) timer.async_wait([&](auto...args) {
		print_ << "hello " << ++ii;
		});

	print_ << "run context\n";
	ctx.run();

	print_ << "end of program...\n";
	return 0;
}