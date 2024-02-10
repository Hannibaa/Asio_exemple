#include <iostream>
#include <syncstream>
#include <functional>
#include <vector>

#include <asio.hpp>

#include <MyLib/Console_Library/escape_code.h>

#define now_time         std::chrono::system_clock::now()
#define Seconds(n)       std::chrono::seconds(n)

void work(std::string worker) {
	print_ << worker << " id is " << std::this_thread::get_id() << end_;
	print_ << "time " << now_time << end_ ;

}

int main() {
		print_ << "main thread id : " << std::this_thread::get_id() << end_;
	
		asio::io_context context;
	
		asio::steady_timer timer1(context, Seconds(2));
		asio::steady_timer timer2(context, Seconds(5));

		std::vector<asio::steady_timer> vTimer;
	
		timer1.async_wait([&](auto...args) {
			print_ << "thread id timer 1 :" << std::this_thread::get_id() << end_;
			work("timer 1");
			});
	     
		timer2.async_wait([&](auto...args) {
			print_ << "thread id timer 2 :" << std::this_thread::get_id() << end_;
			work("timer 2");
	
			});
	
		std::thread thrContext([&] { context.run(); });
	
		thrContext.join();
	
		return 0;
	}


//int main() {
//	print_ << "main thread id : " << std::this_thread::get_id() << end_;
//
//	asio::io_context context;
//
//	asio::steady_timer timer1(context, Seconds(2));
//	asio::steady_timer timer2(context, Seconds(5));
//
//	timer1.async_wait([&](auto...args) {
//		print_ << "thread id timer 1" << std::this_thread::get_id() << end_;
//		print_ << "timer1 : wait by using timer 2 " << end_;
//		timer2.wait();
//		print_ << "timer1 : after wait from timer2 " << end_;
//		work("timer1");
//		});
//     
//	timer2.async_wait([&](auto...args) {
//		print_ << "thread id timer 2" << std::this_thread::get_id() << end_;
//		print_ << "timer2 : wait by using timer 1 " << end_;
//		timer1.wait();
//		print_ << "timer2 : after wait from timer1 " << end_;
//		work("timer2");
//
//		});
//
//	std::thread thrContext([&] { context.run(); });
//
//	thrContext.join();
//
//	return 0;
//}







//int main() {
//
//	print_ << "main thread id : " << std::this_thread::get_id() << end_;
//
//	asio::io_context ctx;
//	asio::steady_timer timer1(ctx,std::chrono::seconds(1));
//	asio::steady_timer timer2(ctx, std::chrono::seconds(5));
//
//	timer1.async_wait([](auto...args) {
//		std::osyncstream(print_) << "hello id :" << std::this_thread::get_id() << end_ ;
//		std::osyncstream(print_) << std::chrono::system_clock::now() << end_; });
//
//
//	timer2.async_wait([](auto...args) {
//		std::osyncstream(print_) << "this is me id " << std::this_thread::get_id() << end_;
//		std::osyncstream(print_) << std::chrono::system_clock::now() << end_; });
//
//
//	print_ << "time now : " << std::chrono::system_clock::now() << end_;
//
//	ctx.run();
//
//	print_ << "time at the end : " << std::chrono::system_clock::now() << end_;
//	return 0;
//}