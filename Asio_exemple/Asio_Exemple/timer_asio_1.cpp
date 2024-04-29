#include <iostream>
#include <syncstream>
#include <conio.h>

#include <asio.hpp>
#include "MyLib/Console_Library/escape_code.h"
#include "asio_utillity.h"
#pragma warning(disable : 4996)

/*
      exemple 1
	  exemple 2
*/

#define exemple_2

bool  b_stop = false;

void _clock(const std::error_code& ec, asio::steady_timer& timer, std::chrono::milliseconds duration) {
	if (ec || b_stop) {
		print_ << ec.message() << end_;
		return;
	}

	std::time_t  now = std::time(nullptr);
	printm_(10, 10) << "time now : " << std::ctime(&now);

	timer.expires_after(duration);
	timer.async_wait([&](auto...arg) { _clock(ec, timer, duration); });
}


void Editor(std::vector<std::string>& vstr) {
	std::string str;
	while (!b_stop) {
		char c = _getch();

		if (std::isprint(c)) {
			str.push_back(c);
		}
		else if (c == ESCAPE) {
			b_stop = true;
			if (!str.empty())
				vstr.push_back(str);
			str.clear();
		}
		else if (c == CR) {
			if (!str.empty())
				vstr.push_back(str);
			str.clear();
			std::osyncstream(print_) << ERASELINE;
		}

		std::osyncstream(print_) << MOVETO(1, 13) << str;
		
	}

	Print_(color::Red, "Exit Editor thread") << end_;
}



int main() {

	Print_(color::Green, "Small editor Kaditor") << end_;

	asio::io_context context;
	asio::steady_timer timer1(context, Seconds(1));
	std::error_code ec;

	std::vector<std::string> vstr;
	std::thread thrEditor(Editor, std::ref(vstr));
	std::thread thrContext([&] {context.run(); });

	_clock(ec, timer1, Seconds(1));

	while (!b_stop) {
		for (auto& s : vstr)
			std::osyncstream(print_) << MOVETO(1, 15 + vstr.size())<< "Size : " << vstr.size() << end_;
	}

	thrContext.join();
	thrEditor.detach();

	Print_(color::Yellow, "End of program") << end_;
	wait_;
	return 0;
}





#ifdef exemple_1

int main() {
	Print_(color::Green, "This thread id : ") << COLOR(color::Red, ThreadId) << end_;

	asio::io_context   ctx;
	std::error_code    ec;
	std::thread  thrStop([] {
		while (!b_stop) {
			char c = _getch();
			if (c == ESCAPE) b_stop = true;
		}
		});

	asio::steady_timer   timer1(ctx);


	_clock(ec, timer1, Seconds(3));

	std::thread thr([&] {ctx.run(); });

	thr.join();
	thrStop.detach();
	wait_;
	return 0;
}

#endif 