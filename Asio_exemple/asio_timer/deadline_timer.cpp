#include <iostream>
#include "asio.hpp"

#include <cctype>
#include <chrono>
#include <stdexcept>
#include <thread>
#include <conio.h>
//#pragma warning(disable : 4996)   //  desable this error to run program 

#define end_ '\n'

int main()
{
	asio::io_service service;

	asio::steady_timer  timer(service, std::chrono::seconds(5));

	timer.async_wait([](auto...vn) {
		std::cout << std::chrono::system_clock::now()
			<< " : timer expired." << end_;
		});

	std::cout << std::chrono::system_clock::now() << " : calling run" << end_;

	service.run();

	std::cout << std::chrono::system_clock::now() << " : done." << end_;

	std::cin.get();
	return 0;
}