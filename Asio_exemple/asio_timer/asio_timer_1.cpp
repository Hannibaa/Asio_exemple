#include <iostream>
#include "asio.hpp"

#include <cctype>
#include <chrono>
#include <stdexcept>
#include <thread>
#include <conio.h>
#pragma warning(disable : 4996)   //  desable this error to run program 

#define end_  '\n'

void process(const std::string& str) {

	for (const auto& c : str) {
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		std::cout << c << " ";
	}
	std::cout << '\n';
}



int main() {

	std::cout << "thread Id : " << std::this_thread::get_id() << end_;

	asio::io_context  ctx;

	asio::steady_timer timer(ctx, asio::chrono::seconds(2));


	timer.async_wait([](const std::error_code& ec) {std::cout << "Active....|";
	auto tp = std::chrono::system_clock::now();
	std::cout << tp << " |" << std::this_thread::get_id() << end_;
	process("hello"); });

	timer.expires_after(std::chrono::seconds(2));

	timer.async_wait([](const std::error_code& ec) {std::cout << "timer 2 Active...|";
	auto tp = std::chrono::system_clock::now();
	std::cout << tp << " |" << std::this_thread::get_id() << end_;
	process("world"); });

	std::cout << "start |" << std::chrono::system_clock::now() << end_;

	ctx.run();

	std::cout << "end   |" << std::chrono::system_clock::now() << end_;

	std::cin.get();
	return 0;
}