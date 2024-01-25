#include <iostream>
#include "asio.hpp"
#include <MyLib/Console_Library/escape_code.h>

bool _stop = false;

void timer_expired(std::string id) {
	Print_(color::Red, std::chrono::system_clock::now()) << " " << id << " enter.\n";
	std::this_thread::sleep_for(std::chrono::milliseconds(3000));
	Print_(color::Red, std::chrono::system_clock::now()) << " " << id << " leave.\n";
}

void affich_time(asio::steady_timer& timer) {

	esc::clear_line(1, 1);
	printm_(40, 1) << std::chrono::system_clock::now() << end_;
	timer.expires_after(std::chrono::seconds(1));
	timer.async_wait([&](auto...vn) {affich_time(timer); });
}

int main() {

	print_ << end_;
	print_ << UNDERLINE << "   hello Asio    " << RESETMODE << end_;
	asio::io_service service;

	asio::steady_timer timer1(service, std::chrono::seconds(5));
	asio::steady_timer timer2(service, std::chrono::seconds(5));

	timer1.async_wait([](auto...vn) {timer_expired("timer1"); });
	timer2.async_wait([](auto...vn) {timer_expired("timer2"); });

	std::thread thr1([&]() {service.run(); });
	std::thread thr2([&]() {service.run(); });

	thr1.join();
	thr2.join();


	Print_(color::Green, "End...");
	wait_;
	return 0;
}