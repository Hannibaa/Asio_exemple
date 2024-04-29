#include <iostream>
#include <conio.h>
#include <array>
#include <vector>
#include <string>

#include <asio.hpp>
#include <MyLib/Console_Library/escape_code.h>
#include <MyLib/stringfunctionhelper.h>

//      this seconds Program for posting 
//      this program show how to post program in threads pool with context
//      also will using timer

bool bStop = false;

#define THREAD_NUMBER          3

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

void _timer(asio::steady_timer& timer, const std::string& comment ) {
	static int count{};

	print_ << std::this_thread::get_id() << "| " << comment << " : " << ++count << end_;

	if (bStop) return;

	timer.expires_after(std::chrono::seconds(2));

	timer.async_wait([&timer,&comment](auto...arg) {
		_timer(timer, comment);
		});
}

int main() {
	// Posting Job to context exemple.
	asio::io_context  context;

	// vector of threads
	std::vector<std::thread>  vThreads;

	// vector of timers
	std::vector<asio::steady_timer> vtimers;

	// vector of random string 
	std::vector<std::string>  vstr;

	// associat timer to context and make random vector of strings
	for (int i = 0; i < THREAD_NUMBER; ++i) {
		vtimers.emplace_back(context, std::chrono::seconds(1));
		vstr.push_back(std::to_string(i) + "__" + Str::getRandomString(5));
	}

	// Starting thread to stop process of counting in timer
	ThreadStop();
    
	// starting function of timer
	int k{};
	for (auto& t :vtimers) _timer(t, vstr[k++]);

	// get main id thread
	print_ << "main thread id : " << std::this_thread::get_id() << end_;

	asio::post(context, [] {
		Print_(color::Green, "Start program ") << std::this_thread::get_id() << end_;
		});

	

	// put context in thread
	for (int i = 0; i < THREAD_NUMBER; ++i) {
		vThreads.push_back(std::thread([&context] {context.run(); }));
	}

	for (auto& e : vThreads) e.join();


	return 0;
}