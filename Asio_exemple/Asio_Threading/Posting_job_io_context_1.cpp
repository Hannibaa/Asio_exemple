#include <iostream>
#include <conio.h>
#include <array>
#include <vector>
#include <string>

#include <asio.hpp>
#include <MyLib/Console_Library/escape_code.h>

//      this program show how to post program in threads pool with context
//      also will using timer

bool bStop = false;

void ThreadStop() {
	std::thread thr([] {
		while (true) {
			if (_getch() == ESCAPE) {
				bStop = true;
				break;
			}
		}
		});

	thr.detach();
}

void _timer(asio::steady_timer& timer, std::string_view comment = "counting") {
	static int count{};
	
	print_ << std::this_thread::get_id() << "| " << comment << " : " << ++count << end_;

	if (bStop) return;

	timer.expires_after(std::chrono::seconds(1));
	
	timer.async_wait([&timer](auto...arg) {
		_timer(timer);
		});
}

int main() {
	// Posting Job to context exemple.
	asio::io_context  context;

	// Starting thread to stop process of counting in timer
	ThreadStop();

	asio::steady_timer     timer(context, std::chrono::seconds(1));

	_timer(timer);

	// get main id thread
	print_ << "main thread id : " << std::this_thread::get_id() << end_;

	asio::post(context, [] {
		Print_(color::Green, "Start program ") << std::this_thread::get_id() << end_;
		});

	asio::post(context, [] {
		Print_(color::Red, "End of Program ") << std::this_thread::get_id() << end_;
		});

	asio::post(context, [] {
		Print_(color::Fuchsia, "Between of Program ") << std::this_thread::get_id() << end_;
		});

	asio::post(context, [] {
		Print_(color::Yellow, "Another of Program ") << std::this_thread::get_id() << end_;
		});


	std::thread thr1([&context] {context.run(); });
	std::thread thr2([&context] {context.run(); });


	thr1.join();
	thr2.join();

	return 0;
}