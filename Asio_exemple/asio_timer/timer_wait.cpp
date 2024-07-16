/* 
				Testing wait() function of timer
				steady_timer

*/

#include <iostream>

#include <asio.hpp>
#include <include/console/escape_code.h>

// using




// using timer asynchronously
void print(std::error_code ec) {
	Print_(color::Fuchsia, "Hello Kadda") << end_;
	Print_(color::Fuchsia, "Error Code : ") << COLOR(color::Red, ec.message()) << end_;
	if (ec) print_ << "true there are error" << end_;
	else    print_ << "false no error" << end_;
}

int main() {
	set_escape_mode();
	Print_(color::Green, "Program Start") << end_;

	asio::io_context context;
	asio::steady_timer timer(context, std::chrono::seconds(4));

	timer.async_wait(&print);

	context.run();
	print_ << "time expiry() = " <<
		std::chrono::time_point_cast<std::chrono::seconds>( timer.expiry()).time_since_epoch().count() << end_;
	Print_(color::Green, "Program End") << end_;
	return 0;
}



// using timer synchronously
int main1() {
	Print_(color::Red, "Program Start") << end_;

	asio::io_context context;
	asio::steady_timer timer(context, std::chrono::seconds(5));
	Print_(color::Green, "before timer wait") << end_;
	timer.wait();

	Print_(color::Green, "after timer 5 sec wait") << end_;

	timer.wait();

	Print_(color::Red, "End Program") << end_;

	return 0;
}